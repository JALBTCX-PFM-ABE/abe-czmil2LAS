
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


#ifndef VERSION

#define     VERSION     "PFM Software - czmil2LAS V3.22 - 08/07/19"

#endif


/*! <pre>

    Version 1.00
    Jan C. Depner
    10/25/12

    First version.
    Only 6 shopping days to retirement!


    Version 1.01
    Jan C. Depner (PFM Software)
    07/17/13

    Added option to output water surface data.  By default we don't want water surface data.
    I'm baaaaaacccccckkkk!


    Version 1.02
    Jan C. Depner (PFM Software)
    12/09/13

    Switched to using .ini file in $HOME (Linux) or $USERPROFILE (Windows) in the ABE.config directory.  Now
    the applications qsettings will not end up in unknown places like ~/.config/navo.navy.mil/blah_blah_blah on
    Linux or, in the registry (shudder) on Windows.


    Version 1.03
    Jan C. Depner (PFM Software)
    01/03/14

    - Finally setting the correct classification values.
    - Saving the channel and return in the UserData field as channel * 100 + return.


    Version 1.04
    Jan C. Depner (PFM Software)
    01/04/14

    - Storing the channel/return numbers in the ReturnNumber field so that we can actually store
      channel * 100 + return.  It won't fit in the UserData field because that is an unsigned 8 bit field.


    Version 1.06
    Jan C. Depner (PFM Software)
    01/06/14

    - Finally got it figured out.  There are only 7 bits for number of returns and return number so I had to
      completely fake these values.  It now just spins through the file writing out 7 returns at a time.
    - I'm storing the channel number * 32 plus the return number in the UserData field.  The deep channel
      is set to 7 to avoid blowing out the 8 bits of UserData.
    - Fixed the directory browse feature.  It was FUBAR.


    Version 1.07
    Jan C. Depner (PFM Software)
    01/07/14

    Replaced get_geoid03 with get_geoid12a.


    Version 1.08
    Jan C. Depner (PFM Software)
    01/11/14

    Fixed the year in the LAS header.


    Version 1.09
    Jan C. Depner (PFM Software)
    01/14/14

    - Made sure not to output filter invalid data.
    - Removed IR data.


    Version 1.10
    Jan C. Depner (PFM Software)
    01/17/14

    - Added GCS_NAD_83 to geokey tag.


    Version 1.11
    Jan C. Depner (PFM Software)
    01/19/14

    Switched to CZMIL_READONLY_SEQUENTIAL for CPF files in order to, hopefully, speed up reads.


    Version 1.12
    Jan C. Depner (PFM Software)
    01/20/14

    Now using processing_mode instead of classification after changes to czmil API to handle
    processing mode being stored in classification prior to libCZMIL 2.0.


    Version 1.13
    Jan C. Depner (PFM Software)
    05/31/14

    Added option (as default) to output time in the LAS 1.2 files as GPS time instead of GPS seconds of the week.


    Version 1.14
    Jan C. Depner (PFM Software)
    06/20/14

    - Point source ID is now set to be the line number from the end of the .cpf file.
    - Returns only go up to 5 as per the brain dead LAS format spec.


    Version 1.15
    Jan C. Depner (PFM Software)
    06/23/14

    - Added per channel options (with the exception of IR).


    Version 2.00
    Jan C. Depner (PFM Software)
    06/25/14

    - Due to the limitations of LAS (and LAS 1.2 especially) this program now outputs one LAS file per selected
      channel.  The return numbers are defined as 1 and 2 for the first two valid (or invalid if requested) returns
      and 4 and 5 for the last two valid (or invalid) returns if there are more than 5 returns.  If there are more
      than 5 returns, all returns other than the first two and the last two are marked as return 3.  In all cases
      the actual return number is stored in the UserData field.


    Version 2.01
    Jan C. Depner (PFM Software)
    06/26/14

    - OK.  I've put the linear units back in to the variable records so that Quick Terrain Modeler will work nicely.
      If Geocue can't handle it, so be it.


    Version 2.02
    Jan C. Depner (PFM Software)
    07/01/14

    - Replaced all of the old, borrowed icons with new, public domain icons.  Mostly from the Tango set
      but a few from flavour-extended and 32pxmania.


    Version 2.10
    Jan C. Depner (PFM Software)
    07/10/14

    - After years of trying to get liblas 1.2.1 to work properly with VLRs I've finally given up.
      I now write the VLR and VLR counr directly to the file myself.


    Version 2.11
    Jan C. Depner (PFM Software)
    07/17/14

    - No longer uses liblas.  Now uses libslas (my own API for LAS).


    Version 2.12
    Jan C. Depner (PFM Software)
    07/23/14

    - Switched from using the old NV_INT64 and NV_U_INT32 type definitions to the C99 standard stdint.h and
      inttypes.h sized data types (e.g. int64_t and uint32_t).


    Version 2.13
    Jan C. Depner (PFM Software)
    09/04/14

    Added support for new Optech classification (processing mode) definitions.


    Version 2.14
    Jan C. Depner (PFM Software)
    12/02/14

    Added option to select GEOID03, GEOID09, or GEOID12a for orthometric correction.


    Version 2.15
    Jan C. Depner (PFM Software)
    12/16/14

    Added option to only output data for a selected area.


    Version 2.16
    Jan C. Depner (PFM Software)
    01/06/15

    Added code to deal with new leap second to be added on June 30th, 2015 at 23:59:60.


    Version 3.00
    Jan C. Depner (PFM Software)
    03/12/15

    Switched to using rapidlasso GmbH LASlib and LASzip instead of my libslas.


    Version 3.01
    Jan C. Depner (PFM Software)
    03/17/15

    - Setting the vertical datum properly.
    - Removed option for setting time to seconds of the week.


    Version 3.02
    Jan C. Depner (PFM Software)
    03/31/15

    - Added ability to use ESRI Polygon, PolygonZ, PolygonM, PolyLine, PolyLineZ, or PolyLineM geographic shape
      files as area files.


    Version 3.03
    Jan C. Depner (PFM Software)
    04/08/15

    - Fixed problem caused by not initializing the withheld/synthetic/keypoint flags.
    - Added support for LAS v1.4 output and LAS RGB fields.


    Version 3.04
    Jan C. Depner (PFM Software)
    07/03/15

    - Finally straightened out the GPS time/leap second problem (I hope).


    Version 3.05
    Jan C. Depner (PFM Software)
    09/15/15

    - Fixed bug in arguments to inside_polygon2.  On vacation in New Mexico!


    Version 3.06
    Jan C. Depner (PFM Software)
    04/01/16

    - Now saves pre-existing classification values (other than 0) to the LAS classification (or extended_classification for LAS1.4).
    - If there is no pre-existing classification value, all processing modes (optech_classification) less than CZMIL_OPTECH_CLASSIFICATION_WATER
      will be marked as land while all those greater than or equal to CZMIL_OPTECH_CLASSIFICATION_WATER will be marked as water (with the exception
      of ip_rank=0, water surface).


    Version 3.07
    Jan C. Depner (PFM Software)
    04/05/16

    - Added geoid12b option.


    Version 3.08
    Jan C. Depner (PFM Software)
    04/29/16

    - Make sure that LAS 1.4 classification values get translated to LAS 1.2 values if we're writing LAS 1.2.


    Version 3.09
    Jan C. Depner (PFM Software)
    05/09/16

    - Now actually meets the LAS 1.4 spec when outputting LAS 1.4 files.  That is, we output Well-known Text (WKT) instead of 
      the GeoKeyDirectoryTag garbage.


    Version 3.10
    Jan C. Depner (PFM Software)
    05/10/16

    - Added a LASF_Spec "Text area description" record that explains what is stored in the "User Data" field of each record.
    - Added "Elevations have been adjusted relative to LOCAL_VERTICAL_DATUM_NAME\n" to the beginning of the LASF_Spec "Text
      area description" record if the local vertical datum has been set and applied.


    Version 3.11
    Jan C. Depner (PFM Software)
    07/13/16

    - Added limiting of output data based on CPF record user_data ranges.


    Version 3.12
    Jan C. Depner (PFM Software)
    08/27/16

    - Now uses the same font as all other ABE GUI apps.  Font can only be changed in pfmView Preferences.


    Version 3.13
    Jan C. Depner (PFM Software)
    01/18/17

    - Reflectance will be multiplied by 65535 insted of 10000 to get a value in the 0-65535 range.


    Version 3.14
    Jan C. Depner (PFM Software)
    04/19/17

    - Properly sets classification for ip_rank = 0 returns for waveforms that were CZMIL_OPTECH_CLASS_HYBRID processed.


    Version 3.15
    Jan C. Depner (PFM Software)
    07/13/17

    - Now takes care of the new ways a point may be marked as a water surface point.  Those are:
      Water processed (i.e. processing mode greater than CZMIL_OPTECH_CLASS_HYBRID) and ip_rank set to 0 
      Point classification set to 9
      Point classification set to 41
      Point classification set to 42


    Version 3.16
    Jan C. Depner (PFM Software)
    08/05/17

    - Added upper intensity/reflectance limit.  This is (hopefully) a temporary solution for CZMIL intensity/reflectance
      fliers.


    Version 3.17
    Jan C. Depner (PFM Software)
    08/29/17

    - Now that the CZMIL API hard-codes ip_rank=0 points to classification 41 (where classification isn't already set), we
      no longer need to check ip_rank to determine water surface.


    Version 3.18
    Jan C. Depner (PFM Software)
    09/26/17

    - A bunch of changes to support doing translations in the future.  There is a generic
      czmil2LAS_xx.ts file that can be run through Qt's "linguist" to translate to another language.


    Version 3.19
    Jan C. Depner (PFM Software)
    05/03/18

    - Small change to support newer version of LASlib.  This fixes problem building compressed
      v1.4 files.


    Version 3.20
    Jan C. Depner (PFM Software)
    05/25/18

    - Added check for CZMIL_REPROCESSING_BUFFER.  Some early files didn't have these set to filter invalid.
    - Changed user data to just have the actual return number.  Channel number is saved in LASF_spec VLR.


    Version 3.21
    Jan C. Depner (PFM Software)
    10/18/18

    - Aaaaaaaaarrrrrrggggghhhh!  Removed the leap second adjustment.  I have no idea who said we needed that
      but, apparently, we don't need it anymore.


    Version 3.22
    Jan C. Depner (PFM Software)
    08/07/19

    - Now that get_area_mbr supports shape files we don't need to handle it differently from the other
      area file types.

</pre>*/
