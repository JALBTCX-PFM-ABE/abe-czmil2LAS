
/*********************************************************************************************

    This is public domain software that was developed by or for the U.S. Naval Oceanographic
    Office and/or the U.S. Army Corps of Engineers.

    This is a work of the U.S. Government. In accordance with 17 USC 105, copyright protection
    is not available for any work of the U.S. Government.

    Neither the United States Government, nor any employees of the United States Government,
    nor the author, makes any warranty, express or implied, without even the implied warranty
    of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, or assumes any liability or
    responsibility for the accuracy, completeness, or usefulness of any information,
    apparatus, product, or process disclosed, or represents that its use would not infringe
    privately-owned rights. Reference herein to any specific commercial products, process,
    or service by trade name, trademark, manufacturer, or otherwise, does not necessarily
    constitute or imply its endorsement, recommendation, or favoring by the United States
    Government. The views and opinions of authors expressed herein do not necessarily state
    or reflect those of the United States Government, and shall not be used for advertising
    or product endorsement purposes.
*********************************************************************************************/


/****************************************  IMPORTANT NOTE  **********************************

    Comments in this file that start with / * ! or / / ! are being used by Doxygen to
    document the software.  Dashes in these comment blocks are used to create bullet lists.
    The lack of blank lines after a block of dash preceeded comments means that the next
    block of dash preceeded comments is a new, indented bullet list.  I've tried to keep the
    Doxygen formatting to a minimum but there are some other items (like <br> and <pre>)
    that need to be left alone.  If you see a comment that starts with / * ! or / / ! and
    there is something that looks a bit weird it is probably due to some arcane Doxygen
    syntax.  Be very careful modifying blocks of Doxygen comments.

*****************************************  IMPORTANT NOTE  **********************************/



#include "czmil2LAS.hpp"


double settings_version = 2.0;


czmil2LAS::czmil2LAS (QWidget *parent)
  : QWizard (parent)
{
  QResource::registerResource ("/icons.rcc");


  //  Set the main icon

  setWindowIcon (QIcon (":/icons/czmil2LASWatermark.png"));


  envin ();


  // Set the application font

  QApplication::setFont (options.font);


  area_file_name.clear ();
  poly_count = 0;


  setWizardStyle (QWizard::ClassicStyle);


  setOption (HaveHelpButton, true);
  setOption (ExtendedWatermarkPixmap, false);


  connect (this, SIGNAL (helpRequested ()), this, SLOT (slotHelpClicked ()));


  //  Set the window size and location from the defaults

  this->resize (options.window_width, options.window_height);
  this->move (options.window_x, options.window_y);

  setPage (0, new startPage (this, &options));
  setPage (1, optionPg = new optionPage (this, &options));
  setPage (2, new fileInputPage (this, &inputFiles, options.input_dir));
  setPage (3, new runPage (this, &progress, &options));


  setButtonText (QWizard::CustomButton1, tr ("&Run"));
  setOption (QWizard::HaveCustomButton1, true);
  button (QWizard::CustomButton1)->setToolTip (tr ("Start the conversion process"));
  connect (this, SIGNAL (customButtonClicked (int)), this, SLOT (slotCustomButtonClicked (int)));


  setStartId (0);
}



czmil2LAS::~czmil2LAS ()
{
}



void czmil2LAS::initializePage (int id)
{
  button (QWizard::HelpButton)->setIcon (QIcon (":/icons/contextHelp.png"));
  button (QWizard::CustomButton1)->setEnabled (false);

  switch (id)
    {
    case 0:
      input_files.clear ();
      break;

    case 1:
      break;

    case 2:
      break;

    case 3:

      button (QWizard::CustomButton1)->setEnabled (true);

      options.las_v14 = field ("las_v14").toBool ();
      options.las_rgb = field ("las_rgb").toBool ();
      options.invalid = field ("invalid").toBool ();
      options.reference = field ("reference").toBool ();
      options.water = field ("water").toBool ();
      options.ellipsoid = field ("ellipsoid").toBool ();
      options.compress = field ("compress").toBool ();
      options.czmil_chan[CZMIL_SHALLOW_CHANNEL_1] = field ("czmilChan1").toBool ();
      options.czmil_chan[CZMIL_SHALLOW_CHANNEL_2] = field ("czmilChan2").toBool ();
      options.czmil_chan[CZMIL_SHALLOW_CHANNEL_3] = field ("czmilChan3").toBool ();
      options.czmil_chan[CZMIL_SHALLOW_CHANNEL_4] = field ("czmilChan4").toBool ();
      options.czmil_chan[CZMIL_SHALLOW_CHANNEL_5] = field ("czmilChan5").toBool ();
      options.czmil_chan[CZMIL_SHALLOW_CHANNEL_6] = field ("czmilChan6").toBool ();
      options.czmil_chan[CZMIL_SHALLOW_CHANNEL_7] = field ("czmilChan7").toBool ();
      options.czmil_chan[CZMIL_IR_CHANNEL] = field ("czmilIRChan").toBool ();
      options.czmil_chan[CZMIL_DEEP_CHANNEL] = field ("czmilDeepChan").toBool ();
      options.upper_intensity = (float) field ("upper").toDouble ();
      area_file_name = field ("area_file_edit").toString ();


      //  Use frame geometry to get the absolute x and y.

      QRect tmp = this->frameGeometry ();
      options.window_x = tmp.x ();
      options.window_y = tmp.y ();


      //  Use geometry to get the width and height.

      tmp = this->geometry ();
      options.window_width = tmp.width ();
      options.window_height = tmp.height ();


      envout ();


      break;
    }
}



void czmil2LAS::cleanupPage (int id)
{
  switch (id)
    {
    case 0:
      break;

    case 1:
      break;

    case 2:
      break;
    }
}



//  This is where the fun stuff happens.

void 
czmil2LAS::slotCustomButtonClicked (int id __attribute__ ((unused)))
{
  QApplication::setOverrideCursor (Qt::WaitCursor);


  button (QWizard::FinishButton)->setEnabled (false);
  button (QWizard::BackButton)->setEnabled (false);
  button (QWizard::CustomButton1)->setEnabled (false);


  //  Get the files from the QTextEdit box on the fileInputPage.

  QTextCursor inputCursor = inputFiles->textCursor ();

  inputCursor.setPosition (0);


  QStringList isort_files;

  isort_files.clear ();

  do
    {
      isort_files << inputCursor.block ().text ();
    } while (inputCursor.movePosition (QTextCursor::NextBlock));


  //  Sort so we can remove dupes.

  isort_files.sort ();


  //  Remove dupes and place into input_files.

  QString name, prev_name = "";
  input_files.clear ();

  for (int32_t i = 0 ; i < isort_files.size () ; i++)
    {
      name = isort_files.at (i);

      if (name != prev_name)
        {
          input_files.append (name);
          prev_name = name;
        }
    }


  input_file_count = input_files.size ();


  //  Main processing loop

  CZMIL_CPF_Header                cpf_header;
  CZMIL_CPF_Data                  cpf;
  int32_t                         cpf_hnd;
  char                            string[1024], area_file[512];
  int32_t                         year, month, jday, hour, minute, mday;
  float                           second;
  double                          min_x[9], max_x[9], min_y[9], max_y[9], min_z[9], max_z[9], time_offset = 0.0;
  time_t                          gps_tv_sec;
  long                            gps_tv_nsec;
  int64_t                         gps_start_time; // start_sec;
  int16_t                         point_source;
  char                            las_name[9][1024];
  LASpoint                        laspoint[9][31];
  LASwriteOpener                  laswriteopener[9];
  LASwriter                       *laswriter[9];
  LASheader                       lasheader[9];
  LASvlr_key_entry                geo_keys[4];


  progress.obar->setRange (0, input_file_count * 100);


  //  Set the GPS start time (00:00:00 on 6 January 1980) in POSIX form.

  inv_cvtime (80, 6, 0, 0, 0.0, &gps_tv_sec, &gps_tv_nsec);
  gps_start_time = (int64_t) gps_tv_sec * 1000000;


  poly_count = 0;

  NV_F64_XYMBR mbr;
  if (!area_file_name.isEmpty ())
    {
      strcpy (area_file, area_file_name.toLatin1 ());

      if (!get_area_mbr (area_file, &poly_count, poly_x, poly_y, &mbr))
        {
          QString qstring = QString (tr ("Error reading area file %1\nReason : %2")).arg (area_file_name).arg (QString (strerror (errno)));
          QMessageBox::critical (this, "czmil2LAS", qstring);
          exit (-1);
        }
    }


  //  Loop through each input file.

  for (int32_t i = 0 ; i < input_file_count ; i++)
    {
      name = input_files.at (i);


      //  Get the point source ID from the file name.

      QString psid = name;
      psid.remove (".cpf");
      point_source = (int16_t) (psid.right (5).toInt ());


      //  Check to see if we want to use a different output directory.

      QString dir = QFileInfo (name).absoluteDir ().absolutePath ();
      
      if (options.output_dir != "") dir = options.output_dir;


      //  Set up the output file names.

      for (int32_t j = 0 ; j < 9 ; j++)
        {
          QString fName = QFileInfo (name).fileName ();
          fName.remove (".cpf");


          //  Append _ and the channel number to the output LAS file name.

          QString chan, lasName;
          chan.setNum (j + 1);


	  QString extension = ".las";
	  if (options.compress) extension = ".laz";


          //  If we are limiting to an area we need to add _area_ to the name.

          if (poly_count)
            {
              lasName = dir + SEPARATOR + fName + "_area_" + chan + extension;
              strcpy (las_name[j], lasName.toLatin1 ());
            }
          else
            {
              lasName = dir + SEPARATOR + fName + "_" + chan + extension;
              strcpy (las_name[j], lasName.toLatin1 ());
            }
        }


      strcpy (string, name.toLatin1 ());


      QString status = tr ("Processing file %1 of %2 : %3").arg (i + 1).arg (input_file_count).arg (QFileInfo (name).fileName ());

      QListWidgetItem *stat = new QListWidgetItem (status);

      progress.list->addItem (stat);
      progress.list->setCurrentItem (stat);
      progress.list->scrollToItem (stat);


      //  Try to open the input file.

      if ((cpf_hnd = czmil_open_cpf_file (string, &cpf_header, CZMIL_READONLY_SEQUENTIAL)) < 0)
        {
          QMessageBox::critical (this, tr ("czmil2LAS Open input files"), tr ("The file %1 could not be opened.\nThe error message returned was:\n\n%2").arg 
                                 (name).arg (czmil_strerror ()));
        }
      else
        {
          //  **************  We ain't gonna make no leap second changes, no mo!  JCD 10/18/18  **************

	  //  Note, GPS time is ahead of UTC time by some number of leap seconds depending on the date of the survey.
	  //  The leap seconds that are relevant for CHARTS and/or CZMIL data are as follows
	  //
	  //  December 31 2005 23:59:59 - 1136073599 - 14 seconds ahead
	  //  December 31 2008 23:59:59 - 1230767999 - 15 seconds ahead
	  //  June 30 2012 23:59:59     - 1341100799 - 16 seconds ahead
	  //  June 30 2015 23:59:59     - 1435708799 - 17 seconds ahead

	  time_offset = 1000000000.0; // - 13.0;

          /*
          start_sec = cpf_header.flight_start_timestamp / 1000000;
          if (start_sec > 1136073599) time_offset -= 1.0;
          if (start_sec > 1230767999) time_offset -= 1.0;
          if (start_sec > 1341100799) time_offset -= 1.0;
          if (start_sec > 1435708799) time_offset -= 1.0;
          */


          progress.fbar->reset ();

          progress.fbox->setTitle (QFileInfo (name).fileName ());

          progress.fbar->setRange (0, cpf_header.number_of_records);

          for (int32_t j = 0 ; j < 9 ; j++)
            {
              if (options.czmil_chan[j])
                {
		  lasheader[j].clean ();


                  //  Fill the required header fields.

		  memset (lasheader[j].system_identifier, 0, 32);
		  memset (lasheader[j].generating_software, 0, 32);


                  sprintf (lasheader[j].system_identifier, "CZMIL - system %02d", cpf_header.system_number);

		  QString version = QString (VERSION).section ('-', 1, 2).simplified ();
		  char ver[31];
		  strcpy (ver, version.toLatin1 ());
                  sprintf (lasheader[j].generating_software, "%s", ver);


                  czmil_cvtime (cpf_header.flight_start_timestamp, &year, &jday, &hour, &minute, &second);
                  czmil_jday2mday (year, jday, &month, &mday);
                  month++;


#ifdef _WIN32
  #if defined (__MINGW64__) || defined (__MINGW32__)
                  putenv ((char *) "TZ=GMT");
                  tzset ();
  #else
                  _putenv ((char *) "TZ=GMT");
                  _tzset ();
  #endif
#else
                  putenv ((char *) "TZ=GMT");
                  tzset ();
#endif


                  lasheader[j].file_creation_day = jday;
                  lasheader[j].file_creation_year = year + 1900;


		  //  Header size for 1.2 is 227 (1.3 is 235 and 1.4 is 375).

                  if (options.las_v14)
                    {
                      lasheader[j].version_major = 1;
                      lasheader[j].version_minor = 4;
                      lasheader[j].header_size = 375;
                      lasheader[j].offset_to_point_data = 375;


                      //  If we're writing LAS 1.4 we have to use Well-known Text (WKT) since we're using point data format 6 or 7.

                      lasheader[j].number_of_variable_length_records = 1;

                      strcpy (cpf_header.wkt, cpf_header.wkt);
                      lasheader[j].set_geo_wkt_ogc_math (strlen (cpf_header.wkt), cpf_header.wkt);
                    }
                  else
                    {
                      lasheader[j].version_major = 1;
                      lasheader[j].version_minor = 2;
                      lasheader[j].header_size = 227;
                      lasheader[j].offset_to_point_data = 227;


                      //  For LAS 1.2 we use the old GeoKeyDirectoryTag

                      lasheader[j].number_of_variable_length_records = 1;


                      //  You can look these up in the GeoTIFF spec (appendices) basically they mean...


                      //  Key 1

                      //  GTModelTypeGeoKey (1024)

                      geo_keys[0].key_id = 1024;


                      //  Empty (in other words, no offset, we're putting the value here).

                      geo_keys[0].tiff_tag_location = 0;
                      geo_keys[0].count = 1;


                      //  ModelTypeGeographic (2 - Geographic latitude-longitude System)

                      geo_keys[0].value_offset = 2;



                      //  Key 2

                      //  GeographicTypeGeoKey (2048)

                      geo_keys[1].key_id = 2048;
                      geo_keys[1].tiff_tag_location = 0;
                      geo_keys[1].count = 1;


                      //  If one of the orthometric corrections was chosen then this is probably an Army Corps survey and 
                      //  the horizontal datum is GCS_NAD83.  Otherwise, it's GCS_WGS_84.

                      switch (options.ortho)
                        {
                        case 0:
                          geo_keys[1].value_offset = 4326;
                          break;

                        case 1:
                        case 2:
                        case 3:
                          geo_keys[1].value_offset = 4269;
                          break;
                        }



                      //  Key 3

                      //  VerticalCSTypeGeoKey (4096)

                      geo_keys[2].key_id = 4096;
                      geo_keys[2].tiff_tag_location = 0;
                      geo_keys[2].count = 1;


                      //  VertCS_WGS_84_ellipsoid (5030) or VertCS_North_American_Vertical_Datum_1988 (5103)

                      switch (options.ortho)
                        {
                        case 0:
                          geo_keys[2].value_offset = 5030;
                          break;

                        case 1:
                        case 2:
                        case 3:
                          geo_keys[2].value_offset = 5103;
                          break;
                        }


                      //  Key 4

                      //  VerticalUnitsGeoKey (4099)

                      geo_keys[3].key_id = 4099;
                      geo_keys[3].tiff_tag_location = 0;
                      geo_keys[3].count = 1;


                      //  Linear_Meter (9001)

                      geo_keys[3].value_offset = 9001;



                      //  Set the LASF_Projection

                      lasheader[j].set_geo_keys (4, geo_keys);
                    }


                  //  Check for local vertical datum offset 

                  char ud[256], desc[32];
                  U8 *udata;
                  int32_t len = 0;
                  memset (desc, 0, 32);

                  if (!options.ellipsoid && cpf_header.local_vertical_datum != 0)
                    {
                      sprintf (desc, "Vertical Datum and User Data");

                      char datum_string[128];

                      czmil_get_local_vertical_datum_string (cpf_header.local_vertical_datum, datum_string);

                      sprintf (ud, "Elevations have been adjusted relative to %s.\nCZMIL channel = %d\nUser Data = Actual return number", datum_string, j + 1);

                      len = strlen (ud) + 1;

                      udata = new U8[len];

                      memcpy (udata, ud, len);
                    }
                  else
                    {
                      //  Add description of the User Data field.

                      sprintf (desc, "User Data definition");

                      sprintf (ud, "CZMIL channel = %d\nUser Data = Actual return number", j + 1);

                      len = strlen (ud) + 1;

                      udata = new U8[len];

                      memcpy (udata, ud, len);
                    }


                  //  Important note - unlike set_geo_keys, add_vlr increments the count of VLRs for you so don't add one to the count.

                  lasheader[j].add_vlr ("LASF_Spec", 3, len, udata, FALSE, desc);


                  //  Check for RGB inclusion

                  if (options.las_rgb)
                    {
                      if (options.las_v14)
                        {
                          lasheader[j].point_data_format = 7;
                          lasheader[j].point_data_record_length = 36;
                        }
                      else
                        {
                          lasheader[j].point_data_format = 3;
                          lasheader[j].point_data_record_length = 34;
                        }
                    }
                  else
                    {
                      if (options.las_v14)
                        {
                          lasheader[j].point_data_format = 6;
                          lasheader[j].point_data_record_length = 30;
                        }
                      else
                        {
                          lasheader[j].point_data_format = 1;
                          lasheader[j].point_data_record_length = 28;
                        }
                    }


                  if (options.las_v14)
                    {
                      for (int32_t pbr = 0 ; pbr < 15 ; pbr++) lasheader[j].extended_number_of_points_by_return[pbr] = 0;
                    }
                  else
                    {
                      for (int32_t pbr = 0 ; pbr < 5 ; pbr++) lasheader[j].number_of_points_by_return[pbr] = 0;
                    }

                  lasheader[j].x_scale_factor = 0.0000001;
                  lasheader[j].y_scale_factor = 0.0000001;
                  lasheader[j].z_scale_factor = 0.001;

                  lasheader[j].x_offset = 0.0;
                  lasheader[j].y_offset = 0.0;
                  lasheader[j].z_offset = 0.0;


                  //  Set the global encoding slot in the header to 1 to store time as GPS time.

                  lasheader[j].global_encoding = 1;


                  //  If we're doing LAS v1.4 we want to set the bit in global encoding to say that the return numbers are synthetic.
                  //  They won't all be synthetic but, since LAS v1.4 can only handle 15 returns per shot we'll probably have some that
                  //  are faked.  We also have to use WKT since we're using point format 6 or 7.

                  if (options.las_v14) lasheader[j].global_encoding = 25;  //  binary 11001


		  //  Start out with bounds set to the same as CPF header so LASlib won't bitch.

		  lasheader[j].min_x = cpf_header.min_lon;
		  lasheader[j].max_x = cpf_header.max_lon;
		  lasheader[j].min_y = cpf_header.min_lat;
		  lasheader[j].max_y = cpf_header.max_lat;


                  //  This is wrong because v1.2 won't handle the number of points that v1.4 will but if we don't set both the
                  //  number_of_point_records and extended_number_of_point_records then we'll get a warning when we close the file.

                  lasheader[j].number_of_point_records = 0;
                  if (options.las_v14) lasheader[j].extended_number_of_point_records = 0;


		  laswriteopener[j].set_file_name (las_name[j]);


		  laswriter[j] = laswriteopener[j].open (&lasheader[j]);

		  if (!laswriter[j])
		    {
                      QMessageBox::critical (this, "czmil2LAS", tr ("Could not create LAS file %1\n").arg (QString (las_name[j])));
		      exit (-1);
		    }


		  for (int32_t k = 0 ; k < 31 ; k++)
		    {
		      if (!laspoint[j][k].init (&lasheader[j], lasheader[j].point_data_format, lasheader[j].point_data_record_length, &lasheader[j]))
			{
			  QMessageBox::critical (this, "czmil2LAS", tr ("Could not initialize LASPoint records for LAS file %1\n").arg (QString (las_name[j])));
			  exit (-1);
			}
		    }


		  //  Set mins and maxes to stupid values so they'll be replaced when we load the points.

		  max_x[j] = max_y[j] = max_z[j] = -99999999999999.0;
		  min_x[j] = min_y[j] = min_z[j] = 99999999999999.0;
                }
            }



          //  Zero the counters.

          int32_t prog_count = 0;


          //  Loop through the entire file reading each record.

          for (int32_t rec = 0 ; rec < cpf_header.number_of_records ; rec++)
            {
              if (czmil_read_cpf_record (cpf_hnd, rec, &cpf) != CZMIL_SUCCESS)
                {
                  QMessageBox::critical (this, tr ("czmil2LAS Read CPF record"), tr ("Record %1 in file %2 could not be read.\nThe error message returned was:\n\n%3").arg
                                         (rec).arg (name).arg (czmil_strerror ()));
                  exit (-1);
                }


              //  Check to see if we are limiting based on user_data ranges.

              uint8_t use_it = NVTrue;

              for (int32_t rng = 0 ; rng < options.userDataCount ; rng++)
                {
                  if (cpf.user_data > options.userDataMax[rng] || cpf.user_data < options.userDataMin[rng])
                    {
                      use_it = NVFalse;
                      break;
                    }
                }

              if (use_it)
                {
                  for (int32_t j = 0 ; j < 9 ; j++)
                    {
                      //  Check to see if we are going to use the specific channel.

                      if (options.czmil_chan[j])
                        {
                          int32_t n = 0;
                          for (int32_t m = 0 ; m < cpf.returns[j] ; m++)
                            {
                              //  Never output filter invalid data (only Optech sets filter invalid).  Never output CZMIL_REPROCESSING_BUFFER.  These should
                              //  have been set to filter invalid but some early ones slipped through.

                              if (!(cpf.channel[j][m].status & CZMIL_RETURN_FILTER_INVAL) && cpf.channel[j][m].filter_reason != CZMIL_REPROCESSING_BUFFER)
                                {
                                  //  Output invalid data?

                                  if (options.invalid || !(cpf.channel[j][m].status & CZMIL_RETURN_MANUALLY_INVAL))
                                    {
                                      //  Output reference data?

                                      if (options.reference || !(cpf.channel[j][m].status & CZMIL_RETURN_REFERENCE))
                                        {
                                          //  Output water surface data?

                                          if (options.water || cpf.optech_classification[j] < CZMIL_OPTECH_CLASS_HYBRID ||
                                              (cpf.channel[j][m].classification != 9 && cpf.channel[j][m].classification != 41 &&
                                               cpf.channel[j][m].classification != 42))
                                            {
                                              uint8_t inside = NVFalse;


                                              //  Check for area?

                                              if (poly_count)
                                                {
                                                  //  First check for inside the MBR.

                                                  if (cpf.channel[j][m].latitude >= mbr.min_y && cpf.channel[j][m].latitude <= mbr.max_y &&
                                                      cpf.channel[j][m].longitude >= mbr.min_x && cpf.channel[j][m].longitude <= mbr.max_x)
                                                    {
                                                      //  Now check for inside the polygon.

                                                      if (inside_polygon2 (poly_x, poly_y, poly_count, cpf.channel[j][m].longitude,
                                                                           cpf.channel[j][m].latitude))
                                                        {
                                                          inside = NVTrue;
                                                        }
                                                    }
                                                }
                                              else
                                                {
                                                  inside = NVTrue;
                                                }


                                              //  If we're not using an area or if the point is inside the requested area, output the point.

                                              if (inside)
                                                {
                                                  double lat, lon, z;


                                                  //  Build the LAS record


                                                  //  We're blowing off the edge_of_flightline 'cause we really don't care ;-)

                                                  laspoint[j][n].edge_of_flight_line = 0;


                                                  laspoint[j][n].scan_direction_flag = 1;
                                                  if (cpf.off_nadir_angle > 180.0) laspoint[j][n].scan_direction_flag = 0;


                                                  lat = cpf.channel[j][m].latitude;
                                                  lon = cpf.channel[j][m].longitude;
                                                  z = cpf.channel[j][m].elevation;


                                                  //  Because LAS thinks intensity should be a 16 bit unsigned integer and our intensity is from
                                                  //  0.0 to 1.0000 we're going to store the intensity times 65535.0.  Also, zero out fliers.

                                                  if (cpf.channel[j][m].reflectance > options.upper_intensity)
                                                    {
                                                      laspoint[j][n].intensity = 0;
                                                    }
                                                  else
                                                    {
                                                      laspoint[j][n].intensity = (uint16_t) (NINT (cpf.channel[j][m].reflectance * 65535.0));
                                                    }


                                                  /*

                                                    If using LASv1.2

                                                      Classification is not exactly per the LAS spec but it's pretty close.  We're having to use
                                                      one of the "reserved for ASPRS" values since there is no classification for bathy data.
                                                      Using libslas I don't have to manually stuff the withheld, key point, and synthetic bit
                                                      into the classification field but this is what the classification field will look like
                                                      in the LAS record.


                                                      Withheld bit      Key Point bit     Synthetic bit    Classification values
                                                           |                 |                 |                    |
                                                           0                 0                 0                  00000

                                                      Valid topo                       = 1     =  0 0 0   00001
                                                      Invalid topo                     = 129   =  1 0 0   00001
                                                      Reference topo                   = 33    =  0 0 1   00001
                                                      Invalid reference topo           = 161   =  1 0 1   00001

                                                      Valid ground                     = 2     =  0 0 0   00010
                                                      Invalid ground                   = 130   =  1 0 0   00010
                                                      Reference ground                 = 34    =  0 0 1   00010
                                                      Invalid reference ground         = 162   =  1 0 1   00010

                                                      Valid water surface              = 9     =  0 0 0   01001
                                                      Invalid water surface            = 137   =  1 0 0   01001
                                                      Reference water surface          = 41    =  0 0 1   01001
                                                      Invalid reference water surface  = 169   =  1 0 1   01001

                                                      Valid bathy                      = 29    =  0 0 0   11101
                                                      Invalid bathy                    = 157   =  1 0 0   11101
                                                      Reference bathy                  = 61    =  0 0 1   11101
                                                      Invalid reference bathy          = 189   =  1 0 1   11101


                                                    If using LASv1.4 (8 bits for classification, validity bits are stored in a separate field)

                                                      Valid topo                       = 1     =  000000001
                                                      Valid ground                     = 2     =  000000010
                                                      Valid water surface              = 41    =  000001001
                                                      Valid bathy                      = 40    =  000101000



                                                    In addition to the above we will use the "Key Point" bit to indicate a CZMIL_RETURN_SELECTED_FEATURE.
                                                    In other words, there are actually 8 possible values for each classification - topo, ground, water
                                                    surface, or bathy.

                                                  */


                                                  if (options.las_v14)
                                                    {
                                                      laspoint[j][n].extended_classification = 0;


                                                      //  If the classification has already been set to a value other than 0 we want use use that
                                                      //  value, as is...

                                                      if (cpf.channel[j][m].classification)
                                                        {
                                                          laspoint[j][n].extended_classification = cpf.channel[j][m].classification;
                                                        }


                                                      //  If it hasn't been set we want to try to interpret the processing mode (optech_classification)
                                                      //  to set the point classification.

                                                      else
                                                        {
                                                          //  Topo - set to 1.  Note that this should never be equal to CZMIL_OPTECH_CLASS_HYBRID because Optech
                                                          //  sets the classification for hybrid processed data (which should be caught above)

                                                          if (cpf.optech_classification[j] <= CZMIL_OPTECH_CLASS_HYBRID)
                                                            {
                                                              laspoint[j][n].extended_classification = 1;
                                                            }


                                                          //  Bathy - set to 40.

                                                          else
                                                            {
                                                              laspoint[j][n].extended_classification = 40;
                                                            }
                                                        }
                                                    }
                                                  else
                                                    {
                                                      laspoint[j][n].classification = 0;


                                                      //  If the classification has already been set to a value other than 0 we want use use that
                                                      //  value, as is (unless, of course, it's a LAS 1.4 value)...

                                                      if (cpf.channel[j][m].classification)
                                                        {
                                                          //  Only put LAS v1.2 classifications into the 4 bits used for LAS v1.2 classification.

                                                          if (cpf.channel[j][m].classification < 32) 
                                                            laspoint[j][n].classification = cpf.channel[j][m].classification;


                                                          //  These are LAS 1.4 classifications so we need to translate them to (almost) LAS 1.2 values

                                                          if (cpf.channel[j][m].classification == 40) laspoint[j][n].classification = 29;
                                                          if (cpf.channel[j][m].classification == 41) laspoint[j][n].classification = 9;
                                                          if (cpf.channel[j][m].classification == 42) laspoint[j][n].classification = 9;
                                                          if (cpf.channel[j][m].classification > 42) laspoint[j][n].classification = 1;
                                                        }


                                                      //  If it hasn't been set we want to try to interpret the processing mode (optech_classification)
                                                      //  to set the point classification.

                                                      else
                                                        {
                                                          //  Topo - set to 1.  Note that this should never be equal to CZMIL_OPTECH_CLASS_HYBRID because Optech
                                                          //  sets the classification for hybrid processed data (which should be caught above)

                                                          if (cpf.optech_classification[j] <= CZMIL_OPTECH_CLASS_HYBRID)
                                                            {
                                                              laspoint[j][n].classification = 1;
                                                            }


                                                          //  Bathy - set to 29.

                                                          else
                                                            {
                                                              laspoint[j][n].classification = 29;
                                                            }
                                                        }
                                                    }


                                                  //  Invalid - set the "Withheld" bit in the classification.

                                                  laspoint[j][n].withheld_flag = 0;
                                                  if (cpf.channel[j][m].status & CZMIL_RETURN_INVAL) laspoint[j][n].withheld_flag = 1;


                                                  //  Selected feature - set the "Key Point" bit in the classification.

                                                  laspoint[j][n].keypoint_flag = 0;
                                                  if (cpf.channel[j][m].status & CZMIL_RETURN_SELECTED_FEATURE) laspoint[j][n].keypoint_flag = 1;


                                                  //  Reference - set the "Synthetic" bit in the classification.

                                                  laspoint[j][n].synthetic_flag = 0;
                                                  if (cpf.channel[j][m].status & CZMIL_RETURN_REFERENCE) laspoint[j][n].synthetic_flag = 1;


                                                  if (options.las_v14)
                                                    {
                                                      laspoint[j][n].extended_scan_angle = NINT (cpf.off_nadir_angle);
                                                    }
                                                  else
                                                    {
                                                      laspoint[j][n].scan_angle_rank = NINT (cpf.off_nadir_angle);
                                                    }


                                                  //  Converting UTC time to GPS time.

                                                  laspoint[j][n].gps_time = ((double) (cpf.timestamp - gps_start_time) / 1000000.0) - time_offset;


                                                  //  If we are correcting to orthometric height... 

                                                  float value = -999.0;
                                                  switch (options.ortho)
                                                    {
                                                    case 1:
                                                      value = get_geoid03 (lat, lon);
                                                      break;

                                                    case 2:
                                                      value = get_geoid09 (lat, lon);
                                                      break;

                                                    case 3:
                                                      value = get_geoid12a (lat, lon);
                                                      break;

                                                    case 4:
                                                      value = get_geoid12b (lat, lon);
                                                      break;
                                                    }

                                                  if (value != -999.0) z -= value;


                                                  //  Subtract the local datum offset if requested.

                                                  if (!options.ellipsoid) z -= cpf.local_vertical_datum_offset;


                                                  laspoint[j][n].X = NINT64 ((lon - lasheader[j].x_offset) / lasheader[j].x_scale_factor);
                                                  laspoint[j][n].Y = NINT64 ((lat - lasheader[j].y_offset) / lasheader[j].y_scale_factor);
                                                  laspoint[j][n].Z = NINT64 ((z - lasheader[j].z_offset) / lasheader[j].z_scale_factor);
                                                  laspoint[j][n].point_source_ID = point_source;


                                                  //  Putting the actual return number into user_data.  The LAS spec (1.2 or 1.4) can't handle 31 returns.

                                                  laspoint[j][n].user_data = m + 1;


                                                  //  Check for min and max x, y, and z.

                                                  min_x[j] = qMin (min_x[j], lon);
                                                  max_x[j] = qMax (max_x[j], lon);
                                                  min_y[j] = qMin (min_y[j], lat);
                                                  max_y[j] = qMax (max_y[j], lat);
                                                  min_z[j] = qMin (min_z[j], z);
                                                  max_z[j] = qMax (max_z[j], z);


                                                  //  Increment the number of records counter in the header.

                                                  //  This is wrong because v1.2 won't handle the number of points that v1.4 will but if we
                                                  //  don't set both the number_of_point_records and extended_number_of_point_records when 
                                                  //  writing a v1.4 file then we'll get a warning when we close the file.

                                                  lasheader[j].number_of_point_records++;
                                                  if (options.las_v14) lasheader[j].extended_number_of_point_records++;

                                                  n++;
                                                }
                                            }
                                        }
                                    }
                                }
                            }


                          //  If we have more than 5 returns for v1.2 or 15 returns for v1.4 we have to fake the return numbers.

                          if (options.las_v14)
                            {
                              if (n > 15)
                                {
                                  //  Set the first seven returns correctly.  Set the last seven returns to 9, 10, 11, 12, 13, 14, and 15.

                                  for (int32_t k = 0 ; k < 7 ; k++)
                                    {
                                      laspoint[j][k].extended_return_number = k + 1;
                                      lasheader[j].extended_number_of_points_by_return[k]++;
                                    }

                                  for (int32_t k = 14 ; k > 8 ; k--)
                                    {
                                      int32_t n_off = 15 - k;
                                      laspoint[j][n - n_off].extended_return_number = k + 1;
                                      lasheader[j].extended_number_of_points_by_return[k]++;
                                    }


                                  //  Set all other return numbers to 8.

                                  for (int32_t k = 8 ; k < n - 7 ; k++)
                                    {
                                      laspoint[j][k].extended_return_number = 8;
                                      lasheader[j].extended_number_of_points_by_return[7]++;
                                    }
                                }
                              else
                                {
                                  //  Set the return numbers.

                                  for (int32_t k = 0 ; k < n ; k++)
                                    {
                                      laspoint[j][k].extended_return_number = k + 1;
                                      lasheader[j].extended_number_of_points_by_return[k]++;
                                    }
                                }
                            }
                          else
                            {
                              if (n > 5)
                                {
                                  //  Set the first two returns to 1 and 2.  Set the last two returns to 4 and 5.

                                  laspoint[j][0].return_number = 1;
                                  lasheader[j].number_of_points_by_return[0]++;
                                  laspoint[j][1].return_number = 2;
                                  lasheader[j].number_of_points_by_return[1]++;
                                  laspoint[j][n - 2].return_number = 4;
                                  lasheader[j].number_of_points_by_return[3]++;
                                  laspoint[j][n - 1].return_number = 5;
                                  lasheader[j].number_of_points_by_return[4]++;


                                  //  Set all other return numbers to 3.

                                  for (int32_t k = 2 ; k < n - 2 ; k++)
                                    {
                                      laspoint[j][k].return_number = 3;
                                      lasheader[j].number_of_points_by_return[2]++;
                                    }
                                }
                              else
                                {
                                  //  Set the return numbers.

                                  for (int32_t k = 0 ; k < n ; k++)
                                    {
                                      laspoint[j][k].return_number = k + 1;
                                      lasheader[j].number_of_points_by_return[k]++;
                                    }
                                }
                            }


                          for (int32_t k = 0 ; k < n ; k++)
                            {
                              if (options.las_v14)
                                {
                                  laspoint[j][k].extended_number_of_returns = qMin (n, 15);
                                }
                              else
                                {
                                  laspoint[j][k].number_of_returns = qMin (n, 5);
                                }

                              if (!laswriter[j]->write_point (&laspoint[j][k]))
                                {
                                  if (options.las_v14)
                                    {
                                      QMessageBox::critical (this, "czmil2LAS", tr ("Record %1 in file %2 could not be appended.").arg 
                                                             (lasheader[j].number_of_point_records).arg (name));
                                    }
                                  else
                                    {
                                      QMessageBox::critical (this, "czmil2LAS", tr ("Record %1 in file %2 could not be appended.").arg 
                                                             (lasheader[j].extended_number_of_point_records).arg (name));
                                    }
                                  exit (-1);
                                }
                            }
                        }
                    }
                }


              progress.fbar->setValue (prog_count);

              progress.obar->setValue (i * 100 + (int32_t) (((float) prog_count / (float) cpf_header.number_of_records) * 100.0));
              qApp->processEvents ();

              prog_count++;
            }


          czmil_close_cpf_file (cpf_hnd);


          progress.fbar->setValue (cpf_header.number_of_records);


          //  Close the LAS files.

          for (int32_t j = 0 ; j < 9 ; j++)
            {
              if (options.czmil_chan[j])
                {
		  lasheader[j].min_x = min_x[j];
		  lasheader[j].min_y = min_y[j];
		  lasheader[j].min_z = min_z[j];
		  lasheader[j].max_x = max_x[j];
		  lasheader[j].max_y = max_y[j];
		  lasheader[j].max_z = max_z[j];


		  //  Update the header with the min and max x, y, and z, and the number of records/returns.

		  laswriter[j]->update_header (&lasheader[j]);

                  laswriter[j]->close();
                }
            }
        }
    }


  progress.obar->setValue (input_file_count * 100);


  button (QWizard::FinishButton)->setEnabled (true);
  button (QWizard::CancelButton)->setEnabled (false);


  QApplication::restoreOverrideCursor ();
  qApp->processEvents ();


  progress.list->addItem (" ");
  QListWidgetItem *cur = new QListWidgetItem (tr ("Processing complete, press Finish to exit."));

  progress.list->addItem (cur);
  progress.list->setCurrentItem (cur);
  progress.list->scrollToItem (cur);
}



//  Get the users defaults.

void
czmil2LAS::envin ()
{
  //  We need to get the font from the global settings.

#ifdef NVWIN3X
  QString ini_file2 = QString (getenv ("USERPROFILE")) + "/ABE.config/" + "globalABE.ini";
#else
  QString ini_file2 = QString (getenv ("HOME")) + "/ABE.config/" + "globalABE.ini";
#endif

  options.font = QApplication::font ();

  QSettings settings2 (ini_file2, QSettings::IniFormat);
  settings2.beginGroup ("globalABE");


  QString defaultFont = options.font.toString ();
  QString fontString = settings2.value (QString ("ABE map GUI font"), defaultFont).toString ();
  options.font.fromString (fontString);


  settings2.endGroup ();


  double saved_version = 1.0;


  // Set defaults so that if keys don't exist the parameters are defined

  options.window_x = 0;
  options.window_y = 0;
  options.window_width = 900;
  options.window_height = 500;
  options.las_v14 = NVFalse;
  options.las_rgb = NVFalse;
  options.invalid = NVFalse;
  options.ortho = 0;
  options.reference = NVFalse;
  options.water = NVFalse;
  options.ellipsoid = NVTrue;
  options.compress = NVFalse;
  options.upper_intensity = 1.0;
  options.input_dir = ".";
  options.area_dir = ".";
  options.userDataText = "";
  options.userDataCount = 0;
  for (int32_t i = 0 ; i < 9 ; i++)
    {
      options.czmil_chan[i] = NVTrue;
    }


  //  Setting CZMIL channel 7 (IR) to NVFalse because we usually won't want that.

  options.czmil_chan[7] = NVFalse;


  //  Get the INI file name

#ifdef NVWIN3X
  QString ini_file = QString (getenv ("USERPROFILE")) + "/ABE.config/czmil2LAS.ini";
#else
  QString ini_file = QString (getenv ("HOME")) + "/ABE.config/czmil2LAS.ini";
#endif

  QSettings settings (ini_file, QSettings::IniFormat);
  settings.beginGroup ("czmil2LAS");

  saved_version = settings.value (QString ("settings version"), saved_version).toDouble ();


  //  If the settings version has changed we need to leave the values at the new defaults since they may have changed.

  if (settings_version != saved_version) return;


  options.window_width = settings.value (QString ("width"), options.window_width).toInt ();
  options.window_height = settings.value (QString ("height"), options.window_height).toInt ();
  options.window_x = settings.value (QString ("x position"), options.window_x).toInt ();
  options.window_y = settings.value (QString ("y position"), options.window_y).toInt ();

  options.las_v14 = settings.value (QString ("LAS v1.4 flag"), options.las_v14).toBool ();

  options.las_rgb = settings.value (QString ("LAS RGB flag"), options.las_rgb).toBool ();

  options.invalid = settings.value (QString ("include invalid data"), options.invalid).toBool ();

  options.ortho = settings.value (QString ("orthometric correction"), options.ortho).toInt ();

  options.reference = settings.value (QString ("include reference data"), options.reference).toBool ();

  options.water = settings.value (QString ("include water surface data"), options.water).toBool ();

  options.ellipsoid = settings.value (QString ("data relative to ellipsoid"), options.ellipsoid).toBool ();

  options.compress = settings.value (QString ("Compress"), options.compress).toBool ();

  options.upper_intensity = settings.value (QString ("upper intensity"), options.upper_intensity).toFloat ();

  options.input_dir = settings.value (QString ("input directory"), options.input_dir).toString ();

  options.area_dir = settings.value (QString ("area directory"), options.area_dir).toString ();

  options.userDataText = settings.value (QString ("user data limits"), options.userDataText).toString ();

  options.czmil_chan[CZMIL_SHALLOW_CHANNEL_1] =
    settings.value (QString ("use CZMIL shallow channel 1"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_1]).toBool ();
  options.czmil_chan[CZMIL_SHALLOW_CHANNEL_2] =
    settings.value (QString ("use CZMIL shallow channel 2"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_2]).toBool ();
  options.czmil_chan[CZMIL_SHALLOW_CHANNEL_3] =
    settings.value (QString ("use CZMIL shallow channel 3"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_3]).toBool ();
  options.czmil_chan[CZMIL_SHALLOW_CHANNEL_4] =
    settings.value (QString ("use CZMIL shallow channel 4"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_4]).toBool ();
  options.czmil_chan[CZMIL_SHALLOW_CHANNEL_5] =
    settings.value (QString ("use CZMIL shallow channel 5"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_5]).toBool ();
  options.czmil_chan[CZMIL_SHALLOW_CHANNEL_6] =
    settings.value (QString ("use CZMIL shallow channel 6"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_6]).toBool ();
  options.czmil_chan[CZMIL_SHALLOW_CHANNEL_7] =
    settings.value (QString ("use CZMIL shallow channel 7"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_7]).toBool ();
  options.czmil_chan[CZMIL_IR_CHANNEL] = settings.value (QString ("use CZMIL IR channel"), options.czmil_chan[CZMIL_IR_CHANNEL]).toBool ();
  options.czmil_chan[CZMIL_DEEP_CHANNEL] = settings.value (QString ("use CZMIL DEEP channel"), options.czmil_chan[CZMIL_DEEP_CHANNEL]).toBool ();

  settings.endGroup ();
}




//  Save the users defaults.

void
czmil2LAS::envout ()
{
  //  Get the INI file name

#ifdef NVWIN3X
  QString ini_file = QString (getenv ("USERPROFILE")) + "/ABE.config/czmil2LAS.ini";
#else
  QString ini_file = QString (getenv ("HOME")) + "/ABE.config/czmil2LAS.ini";
#endif

  QSettings settings (ini_file, QSettings::IniFormat);
  settings.beginGroup ("czmil2LAS");


  settings.setValue (QString ("settings version"), settings_version);

  settings.setValue (QString ("width"), options.window_width);
  settings.setValue (QString ("height"), options.window_height);
  settings.setValue (QString ("x position"), options.window_x);
  settings.setValue (QString ("y position"), options.window_y);

  settings.setValue (QString ("LAS v1.4 flag"), options.las_v14);

  settings.setValue (QString ("LAS RGB flag"), options.las_rgb);

  settings.setValue (QString ("include invalid data"), options.invalid);

  settings.setValue (QString ("orthometric correction"), options.ortho);

  settings.setValue (QString ("include reference data"), options.reference);

  settings.setValue (QString ("include water surface data"), options.water);

  settings.setValue (QString ("data relative to ellipsoid"), options.ellipsoid);

  settings.setValue (QString ("Compress"), options.compress);

  settings.setValue (QString ("upper intensity"), options.upper_intensity);

  settings.setValue (QString ("input directory"), options.input_dir);

  settings.setValue (QString ("area directory"), options.area_dir);

  settings.setValue (QString ("user data limits"), options.userDataText);

  settings.setValue (QString ("use CZMIL shallow channel 1"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_1]);
  settings.setValue (QString ("use CZMIL shallow channel 2"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_2]);
  settings.setValue (QString ("use CZMIL shallow channel 3"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_3]);
  settings.setValue (QString ("use CZMIL shallow channel 4"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_4]);
  settings.setValue (QString ("use CZMIL shallow channel 5"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_5]);
  settings.setValue (QString ("use CZMIL shallow channel 6"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_6]);
  settings.setValue (QString ("use CZMIL shallow channel 7"), options.czmil_chan[CZMIL_SHALLOW_CHANNEL_7]);
  settings.setValue (QString ("use CZMIL IR channel"), options.czmil_chan[CZMIL_IR_CHANNEL]);
  settings.setValue (QString ("use CZMIL DEEP channel"), options.czmil_chan[CZMIL_DEEP_CHANNEL]);

  settings.endGroup ();
}



void 
czmil2LAS::slotHelpClicked ()
{
  QWhatsThis::enterWhatsThisMode ();
}
