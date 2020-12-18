
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



#include "optionPage.hpp"
#include "optionPageHelp.hpp"


optionPage::optionPage (QWidget *prnt, OPTIONS *op):
  QWizardPage (prnt)
{
  options = op;
  parent = prnt;

  setTitle (tr ("Options"));

  setPixmap (QWizard::WatermarkPixmap, QPixmap (":/icons/czmil2LASWatermark.png"));


  QVBoxLayout *vbox = new QVBoxLayout (this);
  vbox->setMargin (5);
  vbox->setSpacing (5);


  QGroupBox *topBox = new QGroupBox (this);
  QHBoxLayout *topBoxLayout = new QHBoxLayout;
  topBox->setLayout (topBoxLayout);
  topBoxLayout->setSpacing (10);


  QGroupBox *chanBox = new QGroupBox (tr ("Channels"), this);
  QVBoxLayout *chanBoxLayout = new QVBoxLayout;
  chanBox->setLayout (chanBoxLayout);
  chanBoxLayout->setSpacing (10);


  czmilChan[CZMIL_SHALLOW_CHANNEL_1] = new QCheckBox (tr ("Shallow Channel 1"), this);
  czmilChan[CZMIL_SHALLOW_CHANNEL_1]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_1]);
  czmilChan[CZMIL_SHALLOW_CHANNEL_1]->setToolTip (tr ("If checked, include CZMIL shallow channel 1 (central channel) data"));
  czmilChan[CZMIL_SHALLOW_CHANNEL_1]->setWhatsThis (czmil1Text);
  czmilChan[CZMIL_SHALLOW_CHANNEL_1]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_1]);
  chanBoxLayout->addWidget (czmilChan[CZMIL_SHALLOW_CHANNEL_1]);

  czmilChan[CZMIL_SHALLOW_CHANNEL_2] = new QCheckBox (tr ("Shallow Channel 2"), this);
  czmilChan[CZMIL_SHALLOW_CHANNEL_2]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_2]);
  czmilChan[CZMIL_SHALLOW_CHANNEL_2]->setToolTip (tr ("If checked, include CZMIL shallow channel 2 data"));
  czmilChan[CZMIL_SHALLOW_CHANNEL_2]->setWhatsThis (czmil2Text);
  czmilChan[CZMIL_SHALLOW_CHANNEL_2]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_2]);
  chanBoxLayout->addWidget (czmilChan[CZMIL_SHALLOW_CHANNEL_2]);

  czmilChan[CZMIL_SHALLOW_CHANNEL_3] = new QCheckBox (tr ("Shallow Channel 3"), this);
  czmilChan[CZMIL_SHALLOW_CHANNEL_3]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_3]);
  czmilChan[CZMIL_SHALLOW_CHANNEL_3]->setToolTip (tr ("If checked, include CZMIL shallow channel 3 data"));
  czmilChan[CZMIL_SHALLOW_CHANNEL_3]->setWhatsThis (czmil3Text);
  czmilChan[CZMIL_SHALLOW_CHANNEL_3]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_3]);
  chanBoxLayout->addWidget (czmilChan[CZMIL_SHALLOW_CHANNEL_3]);

  czmilChan[CZMIL_SHALLOW_CHANNEL_4] = new QCheckBox (tr ("Shallow Channel 4"), this);
  czmilChan[CZMIL_SHALLOW_CHANNEL_4]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_4]);
  czmilChan[CZMIL_SHALLOW_CHANNEL_4]->setToolTip (tr ("If checked, include CZMIL shallow channel 4 data"));
  czmilChan[CZMIL_SHALLOW_CHANNEL_4]->setWhatsThis (czmil4Text);
  czmilChan[CZMIL_SHALLOW_CHANNEL_4]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_4]);
  chanBoxLayout->addWidget (czmilChan[CZMIL_SHALLOW_CHANNEL_4]);

  czmilChan[CZMIL_SHALLOW_CHANNEL_5] = new QCheckBox (tr ("Shallow Channel 5"), this);
  czmilChan[CZMIL_SHALLOW_CHANNEL_5]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_5]);
  czmilChan[CZMIL_SHALLOW_CHANNEL_5]->setToolTip (tr ("If checked, include CZMIL shallow channel 5 data"));
  czmilChan[CZMIL_SHALLOW_CHANNEL_5]->setWhatsThis (czmil5Text);
  czmilChan[CZMIL_SHALLOW_CHANNEL_5]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_5]);
  chanBoxLayout->addWidget (czmilChan[CZMIL_SHALLOW_CHANNEL_5]);

  czmilChan[CZMIL_SHALLOW_CHANNEL_6] = new QCheckBox (tr ("Shallow Channel 6"), this);
  czmilChan[CZMIL_SHALLOW_CHANNEL_6]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_6]);
  czmilChan[CZMIL_SHALLOW_CHANNEL_6]->setToolTip (tr ("If checked, include CZMIL shallow channel 6 data"));
  czmilChan[CZMIL_SHALLOW_CHANNEL_6]->setWhatsThis (czmil6Text);
  czmilChan[CZMIL_SHALLOW_CHANNEL_6]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_6]);
  chanBoxLayout->addWidget (czmilChan[CZMIL_SHALLOW_CHANNEL_6]);

  czmilChan[CZMIL_SHALLOW_CHANNEL_7] = new QCheckBox (tr ("Shallow Channel 7"), this);
  czmilChan[CZMIL_SHALLOW_CHANNEL_7]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_7]);
  czmilChan[CZMIL_SHALLOW_CHANNEL_7]->setToolTip (tr ("If checked, include CZMIL shallow channel 7 data"));
  czmilChan[CZMIL_SHALLOW_CHANNEL_7]->setWhatsThis (czmil7Text);
  czmilChan[CZMIL_SHALLOW_CHANNEL_7]->setChecked (options->czmil_chan[CZMIL_SHALLOW_CHANNEL_7]);
  chanBoxLayout->addWidget (czmilChan[CZMIL_SHALLOW_CHANNEL_7]);

  czmilChan[CZMIL_IR_CHANNEL] = new QCheckBox (tr ("IR Channel"), this);
  czmilChan[CZMIL_IR_CHANNEL]->setChecked (options->czmil_chan[CZMIL_IR_CHANNEL]);
  czmilChan[CZMIL_IR_CHANNEL]->setToolTip (tr ("If checked, include CZMIL IR data"));
  czmilChan[CZMIL_IR_CHANNEL]->setWhatsThis (czmilIRText);
  czmilChan[CZMIL_IR_CHANNEL]->setChecked (options->czmil_chan[CZMIL_IR_CHANNEL]);
  chanBoxLayout->addWidget (czmilChan[CZMIL_IR_CHANNEL]);

  czmilChan[CZMIL_DEEP_CHANNEL] = new QCheckBox (tr ("Deep Channel"), this);
  czmilChan[CZMIL_DEEP_CHANNEL]->setChecked (options->czmil_chan[CZMIL_DEEP_CHANNEL]);
  czmilChan[CZMIL_DEEP_CHANNEL]->setToolTip (tr ("If checked, include CZMIL Deep Channel data"));
  czmilChan[CZMIL_DEEP_CHANNEL]->setWhatsThis (czmilDeepText);
  czmilChan[CZMIL_DEEP_CHANNEL]->setChecked (options->czmil_chan[CZMIL_DEEP_CHANNEL]);
  chanBoxLayout->addWidget (czmilChan[CZMIL_DEEP_CHANNEL]);


  topBoxLayout->addWidget (chanBox);


  QGroupBox *orthoBox = new QGroupBox (tr ("Orthometric correction"), this);
  QVBoxLayout *orthoBoxLayout = new QVBoxLayout;
  orthoBox->setLayout (orthoBoxLayout);
  orthoBoxLayout->setSpacing (10);

  QRadioButton *none = new QRadioButton (tr ("None"));
  none->setToolTip (tr ("If checked, data will not be orthometrically corrected"));
  QRadioButton *e03 = new QRadioButton (tr ("GEOID03"));
  QRadioButton *e09 = new QRadioButton (tr ("GEOID09"));
  e09->setToolTip (tr ("If checked, data will be orthometrically corrected using NGS GEOID09"));
  e09->setWhatsThis (ortho09Text);
  QRadioButton *e12a = new QRadioButton (tr ("GEOID12a"));
  e12a->setToolTip (tr ("If checked, data will be orthometrically corrected using NGS GEOID12a"));
  e12a->setWhatsThis (ortho12aText);
  QRadioButton *e12b = new QRadioButton (tr ("GEOID12b"));
  e12b->setToolTip (tr ("If checked, data will be orthometrically corrected using NGS GEOID12b"));
  e12b->setWhatsThis (ortho12bText);

  QButtonGroup *bGrp = new QButtonGroup (this);
  bGrp->setExclusive (true);
  connect (bGrp, SIGNAL (buttonClicked (int)), this, SLOT (slotOrthoClicked (int)));

  bGrp->addButton (none, 0);
  bGrp->addButton (e03, 1);
  bGrp->addButton (e09, 2);
  bGrp->addButton (e12a, 3);
  bGrp->addButton (e12b, 4);

  orthoBoxLayout->addWidget (none);
  orthoBoxLayout->addWidget (e03);
  orthoBoxLayout->addWidget (e09);
  orthoBoxLayout->addWidget (e12a);
  orthoBoxLayout->addWidget (e12b);

  orthoBoxLayout->addStretch (1);

  bGrp->button (options->ortho)->setChecked (true);

  topBoxLayout->addWidget (orthoBox);


  QVBoxLayout *rLayout = new QVBoxLayout;


  QGroupBox *userBox = new QGroupBox (tr ("User Data Limits"), this);
  QHBoxLayout *userBoxLayout = new QHBoxLayout;
  userBox->setLayout (userBoxLayout);
  userBoxLayout->setSpacing (10);


  QLabel *userRangeLabel = new QLabel (tr ("User data ranges"), this);
  userBoxLayout->addWidget (userRangeLabel);

  userRange = new QLineEdit ("", this);
  userRange->setAlignment (Qt::AlignLeft);
  userRange->setWhatsThis (userRangeText);
  userRange->setText (options->userDataText);


  userBoxLayout->addWidget (userRange);


  rLayout->addWidget (userBox);


  QGroupBox *intBox = new QGroupBox (tr ("Intensity Limits"), this);
  QHBoxLayout *intBoxLayout = new QHBoxLayout;
  intBox->setLayout (intBoxLayout);
  intBoxLayout->setSpacing (10);


  QLabel *intLabel = new QLabel (tr ("Upper limit"), this);
  intBoxLayout->addWidget (intLabel);

  upper = new QDoubleSpinBox (this);
  upper->setDecimals (4);
  upper->setRange (0.0001, 1.0);
  upper->setSingleStep (0.01);
  upper->setValue (options->upper_intensity);
  upper->setWrapping (false);
  upper->setToolTip (tr ("Set the upper intesity value limit"));
  upper->setWhatsThis (upperText);


  intBoxLayout->addWidget (upper);


  rLayout->addWidget (intBox);


  topBoxLayout->addLayout (rLayout);


  //  Check for the availability of the geoid files and set the help and button states accordingly.

  int8_t g03, g09, g12a, g12b;

  g03 = check_geoid03 ();
  g09 = check_geoid09 ();
  g12a = check_geoid12a ();
  g12b = check_geoid12b ();

  switch (g03)
    {
    case 0:
      e03->setToolTip (tr ("If checked, data will be orthometrically corrected using NGS GEOID03"));
      e03->setWhatsThis (ortho03Text);
      break;

    case -1:
      e03->setToolTip (tr ("NGS GEOID03 data is not available because the ABE_DATA environment variable is not set"));
      e03->setWhatsThis (tr ("NGS GEOID03 data is not available because the ABE_DATA environment variable is not set"));
      e03->setEnabled (false);
      break;

    case -2:
      e03->setToolTip (tr ("NGS GEOID03 data is not available because one or more of the geoid03 files is missing from the ABE_DATA/geoid_data folder"));
      e03->setWhatsThis (tr ("NGS GEOID03 data is not available because one or more of the geoid03 files is missing from the ABE_DATA/geoid_data folder"));
      e03->setEnabled (false);
      break;
    }

  switch (g09)
    {
    case 0:
      e09->setToolTip (tr ("If checked, data will be orthometrically corrected using NGS GEOID09"));
      e09->setWhatsThis (ortho09Text);
      break;

    case -1:
      e09->setToolTip (tr ("NGS GEOID09 data is not available because the ABE_DATA environment variable is not set"));
      e09->setWhatsThis (tr ("NGS GEOID09 data is not available because the ABE_DATA environment variable is not set"));
      e09->setEnabled (false);
      break;

    case -2:
      e09->setToolTip (tr ("NGS GEOID09 data is not available because one or more of the geoid09 files is missing from the ABE_DATA/geoid_data folder"));
      e09->setWhatsThis (tr ("NGS GEOID09 data is not available because one or more of the geoid09 files is missing from the ABE_DATA/geoid_data folder"));
      e09->setEnabled (false);
      break;
    }

  switch (g12a)
    {
    case 0:
      e12a->setToolTip (tr ("If checked, data will be orthometrically corrected using NGS GEOID12a"));
      e12a->setWhatsThis (ortho12aText);
      break;

    case -1:
      e12a->setToolTip (tr ("NGS GEOID12a data is not available because the ABE_DATA environment variable is not set"));
      e12a->setWhatsThis (tr ("NGS GEOID12a data is not available because the ABE_DATA environment variable is not set"));
      e12a->setEnabled (false);
      break;

    case -2:
      e12a->setToolTip (tr ("NGS GEOID12a data is not available because one or more of the geoid12a files is missing from the ABE_DATA/geoid_data folder"));
      e12a->setWhatsThis (tr ("NGS GEOID12a data is not available because one or more of the geoid12a files is missing from the ABE_DATA/geoid_data folder"));
      e12a->setEnabled (false);
      break;
    }

  switch (g12b)
    {
    case 0:
      e12b->setToolTip (tr ("If checked, data will be orthometrically corrected using NGS GEOID12b"));
      e12b->setWhatsThis (ortho12bText);
      break;

    case -1:
      e12b->setToolTip (tr ("NGS GEOID12b data is not available because the ABE_DATA environment variable is not set"));
      e12b->setWhatsThis (tr ("NGS GEOID12b data is not available because the ABE_DATA environment variable is not set"));
      e12b->setEnabled (false);
      break;

    case -2:
      e12b->setToolTip (tr ("NGS GEOID12b data is not available because one or more of the geoid12b files is missing from the ABE_DATA/geoid_data folder"));
      e12b->setWhatsThis (tr ("NGS GEOID12b data is not available because one or more of the geoid12b files is missing from the ABE_DATA/geoid_data folder"));
      e12b->setEnabled (false);
      break;
    }


  vbox->addWidget (topBox);


  QGroupBox *oBox = new QGroupBox (this);
  QHBoxLayout *oBoxLayout = new QHBoxLayout;
  oBox->setLayout (oBoxLayout);
  oBoxLayout->setSpacing (10);


  QGroupBox *verBox = new QGroupBox ("LAS v1.4", this);
  QHBoxLayout *verBoxLayout = new QHBoxLayout;
  verBox->setLayout (verBoxLayout);
  verBoxLayout->setSpacing (10);
  verBox->setToolTip (tr ("If checked, output data will be in LAS version 1.4"));
  verBox->setWhatsThis (verText);


  oBoxLayout->addWidget (verBox);


  ver = new QCheckBox (this);
  ver->setToolTip (tr ("If checked, output data will be in LAS version 1.4"));
  ver->setWhatsThis (verText);
  ver->setChecked (options->las_v14);
  verBoxLayout->addWidget (ver);


  QGroupBox *rgbBox = new QGroupBox (tr ("RGB"), this);
  QHBoxLayout *rgbBoxLayout = new QHBoxLayout;
  rgbBox->setLayout (rgbBoxLayout);
  rgbBoxLayout->setSpacing (10);
  rgbBox->setToolTip (tr ("If checked, output point data will include space for RGB"));
  rgbBox->setWhatsThis (rgbText);


  oBoxLayout->addWidget (rgbBox);


  rgb = new QCheckBox (this);
  rgb->setToolTip (tr ("If checked, output point data will include space for RGB"));
  rgb->setWhatsThis (rgbText);
  rgb->setChecked (options->las_rgb);
  rgbBoxLayout->addWidget (rgb);


  QGroupBox *cBox = new QGroupBox (tr ("Compress"), this);
  QHBoxLayout *cBoxLayout = new QHBoxLayout;
  cBox->setLayout (cBoxLayout);
  cBoxLayout->setSpacing (10);
  cBox->setToolTip (tr ("If checked, compress output files"));
  cBox->setWhatsThis (compText);


  oBoxLayout->addWidget (cBox);


  comp = new QCheckBox (this);
  comp->setToolTip (tr ("If checked, compress output files"));
  comp->setWhatsThis (compText);
  comp->setChecked (options->compress);
  cBoxLayout->addWidget (comp);


  QGroupBox *iBox = new QGroupBox (tr ("Invalid data"), this);
  QHBoxLayout *iBoxLayout = new QHBoxLayout;
  iBox->setLayout (iBoxLayout);
  iBoxLayout->setSpacing (10);
  iBox->setToolTip (tr ("If checked, include manually invalid data in output LAS file"));
  iBox->setWhatsThis (invText);


  oBoxLayout->addWidget (iBox);


  inv = new QCheckBox (this);
  inv->setToolTip (tr ("If checked, include manually invalid data in output LAS file"));
  inv->setWhatsThis (invText);
  inv->setChecked (options->invalid);
  iBoxLayout->addWidget (inv);


  QGroupBox *rBox = new QGroupBox (tr ("Reference data"), this);
  QHBoxLayout *rBoxLayout = new QHBoxLayout;
  rBox->setLayout (rBoxLayout);
  rBoxLayout->setSpacing (10);
  rBox->setToolTip (tr ("If checked, include reference data in output LAS file"));
  rBox->setWhatsThis (refText);


  oBoxLayout->addWidget (rBox);


  ref = new QCheckBox (this);
  ref->setToolTip (tr ("If checked, include reference data in output LAS file"));
  ref->setWhatsThis (refText);
  ref->setChecked (options->reference);
  rBoxLayout->addWidget (ref);


  QGroupBox *wBox = new QGroupBox (tr ("Water surface data"), this);
  QHBoxLayout *wBoxLayout = new QHBoxLayout;
  wBox->setLayout (wBoxLayout);
  wBoxLayout->setSpacing (10);
  wBox->setToolTip (tr ("If checked, include water surface data in output LAS file"));
  wBox->setWhatsThis (watText);


  oBoxLayout->addWidget (wBox);


  wat = new QCheckBox (this);
  wat->setToolTip (tr ("If checked, include water surface data in output LAS file"));
  wat->setWhatsThis (watText);
  wat->setChecked (options->water);
  wBoxLayout->addWidget (wat);


  QGroupBox *eBox = new QGroupBox (tr ("Relative to ellipsoid"), this);
  QHBoxLayout *eBoxLayout = new QHBoxLayout;
  eBox->setLayout (eBoxLayout);
  eBoxLayout->setSpacing (10);
  eBox->setToolTip (tr ("If checked, elevations will be relative to the ellipsoid"));
  eBox->setWhatsThis (ellText);


  oBoxLayout->addWidget (eBox);


  ell = new QCheckBox (this);
  ell->setToolTip (tr ("If checked, elevations will be relative to the ellipsoid"));
  ell->setWhatsThis (ellText);
  ell->setChecked (options->ellipsoid);
  eBoxLayout->addWidget (ell);


  vbox->addWidget (oBox);


  registerField ("czmilChan1", czmilChan[CZMIL_SHALLOW_CHANNEL_1]);
  registerField ("czmilChan2", czmilChan[CZMIL_SHALLOW_CHANNEL_2]);
  registerField ("czmilChan3", czmilChan[CZMIL_SHALLOW_CHANNEL_3]);
  registerField ("czmilChan4", czmilChan[CZMIL_SHALLOW_CHANNEL_4]);
  registerField ("czmilChan5", czmilChan[CZMIL_SHALLOW_CHANNEL_5]);
  registerField ("czmilChan6", czmilChan[CZMIL_SHALLOW_CHANNEL_6]);
  registerField ("czmilChan7", czmilChan[CZMIL_SHALLOW_CHANNEL_7]);
  registerField ("czmilIRChan", czmilChan[CZMIL_IR_CHANNEL]);
  registerField ("czmilDeepChan", czmilChan[CZMIL_DEEP_CHANNEL]);
  registerField ("las_v14", ver);
  registerField ("las_rgb", rgb);
  registerField ("invalid", inv);
  registerField ("reference", ref);
  registerField ("water", wat);
  registerField ("ellipsoid", ell);
  registerField ("compress", comp);
  registerField ("upper", upper, "value", "valueChanged");
}



void optionPage::slotOrthoClicked (int id)
{
  options->ortho = id;
}



bool optionPage::validatePage ()
{
  QString range = userRange->text ();


  //  If it's blank we're good to go (no need to parse since there are no user data limits).

  if (!range.isEmpty ())
    {
      //  First check for invalid characters.

      for (int32_t i = 0 ; i < range.length () ; i++)
        {
          if (!(range.at (i).isDigit ()))
            {
              if (range.at (i) != ',' && range.at (i) != '-' && range.at (i) != '.')
                {
                  QMessageBox::warning (this, tr ("czmil2LAS User Data Limits"), tr ("Invalid character %1 in attribute filter range text").arg (range.at (i)));
                  return false;
                }
            }
        }


      //  Split the string into sections divided by commas.

      QStringList ranges = range.split (",", QString::SkipEmptyParts);


      options->userDataCount = ranges.size ();


      //  Allocate the memory for the user data ranges.

      options->userDataMin = (uint8_t *) calloc (options->userDataCount, sizeof (uint8_t));
      if (options->userDataMin == NULL)
        {
          perror ("Allocating options->userDataMin memory in optionPage.cpp");
          exit (-1);
        }


      options->userDataMax = (uint8_t *) calloc (options->userDataCount, sizeof (uint8_t));
      if (options->userDataMax == NULL)
        {
          perror ("Allocating options->userDataMax memory in optionPage.cpp");
          exit (-1);
        }


      for (int32_t i = 0 ; i < options->userDataCount ; i++)
        {
          if (ranges.at (i).contains ('-'))
            {
              QString aminString = ranges.at (i).section ('-', 0, 0);
              QString amaxString = ranges.at (i).section ('-', 1, 1);

              options->userDataMin[i] = (uint8_t) aminString.toInt ();
              options->userDataMax[i] = (uint8_t) amaxString.toInt ();
            }
          else
            {
              options->userDataMin[i] = options->userDataMax[i] = (uint8_t) ranges.at (i).toInt ();
            }


          //  Check for inverted range.

          if (options->userDataMin[i] > options->userDataMax[i])
            {
              QMessageBox::warning (this, tr ("czmil2LAS User Data Limits"),
                                    tr ("Range minimum %1 greater than range maximum %2").arg (options->userDataMin[i]).arg (options->userDataMax[i]));
              return false;
            }
        }
    }


  //  Save the range limits.

  options->userDataText = range;

  return true;
}
