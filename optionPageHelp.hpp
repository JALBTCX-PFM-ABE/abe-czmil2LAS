
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



QString czmil1Text = 
  optionPage::tr ("Checking this box will cause all CZMIL Shallow Channel 1 (central channel) data to be read from the "
                  "CZMIL point file(s) and placed in the LAS output file.");

QString czmil2Text = 
  optionPage::tr ("Checking this box will cause all CZMIL Shallow Channel 2 data to be read from the CZMIL point file(s) "
                  "and placed in the LAS output file.");

QString czmil3Text = 
  optionPage::tr ("Checking this box will cause all CZMIL Shallow Channel 3 data to be read from the CZMIL point file(s) "
                  "and placed in the LAS output file.");

QString czmil4Text = 
  optionPage::tr ("Checking this box will cause all CZMIL Shallow Channel 4 data to be read from the CZMIL point file(s) "
                  "and placed in the LAS output file.");

QString czmil5Text = 
  optionPage::tr ("Checking this box will cause all CZMIL Shallow Channel 5 data to be read from the CZMIL point file(s) "
                  "and placed in the LAS output file.");

QString czmil6Text = 
  optionPage::tr ("Checking this box will cause all CZMIL Shallow Channel 6 data to be read from the CZMIL point file(s) "
                  "and placed in the LAS output file.");

QString czmil7Text = 
  optionPage::tr ("Checking this box will cause all CZMIL Shallow Channel 7 data to be read from the CZMIL point file(s) "
                  "and placed in the LAS output file.");

QString czmilIRText = 
  optionPage::tr ("Checking this box will cause all CZMIL IR Channel data to be read from the CZMIL point file(s) "
                  "and placed in the LAS output file.");

QString czmilDeepText = 
  optionPage::tr ("Checking this box will cause all CZMIL Deep Channel data to be read from the CZMIL point file(s) "
                  "and placed in the LAS output file.");

QString verText = 
  optionPage::tr ("If this box is checked the output LAS files will be in LAS version 1.4.  At present, support for version 1.4 "
                  "in commercial packages is fairly unusual.  If you need the most compatible output files leave this unchecked "
                  "and the output files will be in LAS version 1.2.");

QString rgbText = 
  optionPage::tr ("If this box is checked the output LAS files will contain space for RGB values.  The RGB values will not be "
                  "filled by this program but will be available to be filled by other programs.  If LAS version 1.4 is chosen "
                  "this will cause the output point data format ID to be 7.  If it's not checked the output point data format ID "
                  "will be 6.  IF LAS version 1.4 is not requested then, if this is checked, the output point data format ID will "
                  "be 3.  Otherwise it will be 1.");

QString invText = 
  optionPage::tr ("If this box is checked invalid data will be output along with valid data.  If an invalid point is output "
                  "to the LAS file its <b>Classification</b> field will be set to <b>7</b> for invalid.<br><br>"
                  "<b>IMPORTANT NOTE: Data that is marked <i>Filter Invalid</i> will never be output to the LAS file. "
                  "Data is only marked as <i>Filter Invalid</i> by HydroFusion when it is being created.</b>");

QString refText = 
  optionPage::tr ("If this box is checked reference data will be output along with valid/invalid data.  If a reference point is output "
                  "to the LAS file its <b>Classification</b> field will be set to <b>28</b> for reference.");

QString watText = 
  optionPage::tr ("If this box is checked water surface data (water processed, ip_rank=0) will be output.");

QString ellText = 
  optionPage::tr ("If this box is checked elevation data will be relative to the ellipsoid.  If it is unchecked then any local "
                  "vertical datum offset stored in the CPF record will be subtracted from the elevation so that it will be relative "
                  "to the local vertical datum.");

QString ortho03Text = 
  optionPage::tr ("If this button is toggled on then we will attempt to correct the ellipsoidal height to an orthometric height "
                  "using the National Geodetic Survey (NGS) GEOID03 files.  The files must be stored in a directory called geoid_data that "
                  "is in the directory pointed to by the environment variable ABE_DATA.  The "
                  "files must be the binary versions (not ASCII) and the file names must be the following:<br><br>"
                  "<ul>"
                  "<li>g2003a01.bin</li>"
                  "<li>g2003a02.bin</li>"
                  "<li>g2003a03.bin</li>"
                  "<li>g2003a04.bin</li>"
                  "<li>g2003u01.bin</li>"
                  "<li>g2003u02.bin</li>"
                  "<li>g2003u03.bin</li>"
                  "<li>g2003u04.bin</li>"
                  "<li>g2003u05.bin</li>"
                  "<li>g2003u06.bin</li>"
                  "<li>g2003u07.bin</li>"
                  "<li>g2003u08.bin</li>"
                  "<li>g2003h01.bin</li>"
                  "<li>g2003p01.bin</li>"
                  "</ul><br><br>"
                  "<b>IMPORTANT NOTE: This option implies that the input files were relative to GCS_NAD83.</b>");

QString ortho09Text = 
  optionPage::tr ("If this button is toggled on then we will attempt to correct the ellipsoidal height to an orthometric height "
                  "using the National Geodetic Survey (NGS) GEOID09 files.  The files must be stored in a directory called geoid_data that "
                  "is in the directory pointed to by the environment variable ABE_DATA.  The "
                  "files must be the binary versions (not ASCII) and the file names must be the following:<br><br>"
                  "<ul>"
                  "<li>g2009a01.bin</li>"
                  "<li>g2009a02.bin</li>"
                  "<li>g2009a03.bin</li>"
                  "<li>g2009a04.bin</li>"
                  "<li>g2009u01.bin</li>"
                  "<li>g2009u02.bin</li>"
                  "<li>g2009u03.bin</li>"
                  "<li>g2009u04.bin</li>"
                  "<li>g2009u05.bin</li>"
                  "<li>g2009u06.bin</li>"
                  "<li>g2009u07.bin</li>"
                  "<li>g2009u08.bin</li>"
                  "<li>g2009h01.bin</li>"
                  "<li>g2009p01.bin</li>"
                  "<li>g2009g01.bin</li>"
                  "<li>g2009s01.bin</li>"
                  "</ul><br><br>"
                  "<b>IMPORTANT NOTE: This option implies that the input file(s) were relative to GCS_NAD83.</b>");

QString ortho12aText = 
  optionPage::tr ("If this button is toggled on then we will attempt to correct the ellipsoidal height to an orthometric height "
                  "using the National Geodetic Survey (NGS) GEOID12a files.  The files must be stored in a directory called geoid_data that "
                  "is in the directory pointed to by the environment variable ABE_DATA.  The "
                  "files must be the binary versions (not ASCII) and the file names must be the following:<br><br>"
                  "<ul>"
                  "<li>g2012au0.bin</li>"
                  "<li>g2012aa0.bin</li>"
                  "<li>g2012ah0.bin</li>"
                  "<li>g2012ap0.bin</li>"
                  "<li>g2012ag0.bin</li>"
                  "<li>g2012as0.bin</li>"
                  "</ul><br><br>"
                  "<b>IMPORTANT NOTE: This option implies that the input file(s) were relative to GCS_NAD83.</b>");

QString ortho12bText = 
  optionPage::tr ("If this button is toggled on then we will attempt to correct the ellipsoidal height to an orthometric height "
                  "using the National Geodetic Survey (NGS) GEOID12b files.  The files must be stored in a directory called geoid_data that "
                  "is in the directory pointed to by the environment variable ABE_DATA.  The "
                  "files must be the binary versions (not ASCII) and the file names must be the following:<br><br>"
                  "<ul>"
                  "<li>g2012bu0.bin</li>"
                  "<li>g2012ba0.bin</li>"
                  "<li>g2012bh0.bin</li>"
                  "<li>g2012bp0.bin</li>"
                  "<li>g2012bg0.bin</li>"
                  "<li>g2012bs0.bin</li>"
                  "</ul><br><br>"
                  "<b>IMPORTANT NOTE: This option implies that the input file(s) were relative to GCS_NAD83.</b>");

QString userRangeText =
  optionPage::tr ("This is where you may set limits on the output data based on the <b>user_data</b> field of the CPF record.  The contents of "
                  "the <b>user_data</b> field is defined by the application that sets it.  To see what is being placed in the field for a "
                  "particular CPF file just open a terminal window (konsole on Linux or MSys on Windows) and run <b>less</b> on the CPF "
                  "file (e.g. <b>less CPF_FILE.cpf</b>).<br><br>"
                  "The range limits entered into this field will be used to filter the data prior to writing it to the LAS file.  If the field "
                  "is left blank, no filtering will be done.  The <b>User data ranges</b> field will accept a combination of values separated by "
                  "commas (,) and/or dashes (-).  For example, the text <b>2,7-26,30</b> will cause all data having a <b>user_data</b> value "
                  "of 2, or in the range 7 to 26 inclusive, or having a value of 30 to be output to the LAS file.  All data outside "
                  "those ranges will be ignored.<br><br>");

QString upperText =
  optionPage::tr ("Setting this value to anything other than 1.0 will cause all intensity/reflectance values that exceed this value to be "
                  "set to 0 in the output LAS file.  This is (hopefully) a temporary solution to intensity/reflectance fliers in the CZMIL data.");

QString compText = 
  optionPage::tr ("If this box is checked, the output files will be stored using <b>rapidlasso GmbH</b> LASzip format.  They will have a file "
		  "extension of .laz instead of the normal .las extension.");
