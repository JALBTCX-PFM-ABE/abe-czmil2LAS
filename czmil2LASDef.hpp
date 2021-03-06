
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



#ifndef __CZMIL2LASDEF_H__
#define __CZMIL2LASDEF_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cerrno>
#include <proj_api.h>
#include <laswriter.hpp>

#include <QtCore>
#include <QtGui>
#if QT_VERSION >= 0x050000
#include <QtWidgets>
#endif

#include "nvutility.hpp"

#include "czmil.h"
#include "shapefil.h"


#define  GCS_WGS_84           4326
#define  GCS_NAD_83           4269


typedef struct
{
  int32_t                     window_x;
  int32_t                     window_y;
  int32_t                     window_width;
  int32_t                     window_height;
  uint8_t                     las_v14;              //!<  Set to 1 for LAS v1.4, otherwise, v1.2
  uint8_t                     las_rgb;              //!<  Set to 1 to include RGB space in LAS point data
  uint8_t                     invalid;
  uint8_t                     ortho;                /*!<  Ortho correction - 0 = None, 1 = GEOID03, 2 = GEOID09, 3 = GEOID12A, 4 = GEOID12B
                                                          (1 through 4 imply NAVD88)  */
  uint8_t                     reference;
  uint8_t                     ellipsoid;
  uint8_t                     water;
  uint8_t                     compress;
  uint8_t                     czmil_chan[9];
  float                       upper_intensity;      //!< Upper limit of intensity/reflectance value.  Values exceeding this will be set to 0.
  QString                     input_dir;
  QString                     output_dir;
  QString                     area_dir;             //!<  Last directory searched for area files
  QString                     userDataText;         //!<  User data limits on output.
  uint8_t                     *userDataMin;
  uint8_t                     *userDataMax;
  int32_t                     userDataCount;
  QFont                       font;                 //!<  Font used for all ABE GUI applications
} OPTIONS;


typedef struct
{
  QGroupBox           *obox;
  QGroupBox           *fbox;
  QProgressBar        *obar;
  QProgressBar        *fbar;
  QListWidget         *list;
} RUN_PROGRESS;


#endif
