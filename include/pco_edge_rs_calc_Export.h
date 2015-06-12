//-----------------------------------------------------------------//
// Name        | Pco_Edge_RS_Calc_Export.h   | Type: ( ) source    //
//-------------------------------------------|       (*) header    //
// Project     | PCO                         |       ( ) others    //
//-----------------------------------------------------------------//
// Platform    | PC                                                //
//-----------------------------------------------------------------//
// Environment | Visual 'C++'                                      //
//-----------------------------------------------------------------//
// Purpose     | pco edge RollingShutter conversion                 //
//-----------------------------------------------------------------//
// Author      | MBL, PCO AG                                       //
//-----------------------------------------------------------------//
// Revision    | rev. 0.01 rel. 0.00                               //
//-----------------------------------------------------------------//
// Notes       |                                                   //
//             |                                                   //
//             |                                                   //
//             |                                                   //
//-----------------------------------------------------------------//
// (c) 2011 PCO AG * Donaupark 11 *                                //
// D-93309      Kelheim / Germany * Phone: +49 (0)9441 / 2005-0 *  //
// Fax: +49 (0)9441 / 2005-20 * Email: info@pco.de                 //
//-----------------------------------------------------------------//


//-----------------------------------------------------------------//
// Revision History:                                               //
//-----------------------------------------------------------------//
// Rev.:     | Date:      | Changed:                               //
// --------- | ---------- | ---------------------------------------//
//  0.01     | 15.12.2011 |  new file                              //
//           |            |                                        //
//-----------------------------------------------------------------//

#ifdef PCO_CALC_EXPORT
 #define RS_CONV_CEXP __declspec(dllexport) WINAPI
#elif PCO_EXPORT_DEF
 #define RS_CONV_CEXP WINAPI
#else
#if !defined RS_CONV_CEXP
#define RS_CONV_CEXP __declspec(dllimport) WINAPI
#endif
#endif

#ifdef __cplusplus
extern "C" {            //  Assume C declarations for C++
#endif  //C++


DWORD RS_CONV_CEXP PCO_RS_ConvertCreate(HANDLE *ph);
//Create a unique conversion set
//A unique set must be used, when the conversion functions are called
//simultaneously from different threads
//in:
// ph   -> pointer to hold the Handle of the unique set
//         must be set to NULL
//
//out:
//*ph   -> Handle of the unique set

DWORD RS_CONV_CEXP PCO_RS_ConvertCreateS(HANDLE *ph,int select);
//Create a unique conversion set
//A unique set must be used, when the conversion functions are called
//simultaneously from different threads
//in:
// ph   -> pointer to hold the Handle of the unique set
//         must be set to NULL
// select  different conversion 
//
//out:
//*ph   -> Handle of the unique set



DWORD RS_CONV_CEXP PCO_RS_ConvertDelete(HANDLE *ph);
//Delete a previously created conversion set
//in:
// *ph  -> Handle of the conversion set
//
//out:
//*ph   -> NULL if conversion set was deleted successfully


DWORD RS_CONV_CEXP PCO_RS_Build_Random(HANDLE ph,unsigned int seed,int size);
//Does build a table of random numbers, which is needed for the calculation function.
//The memory, which is allocated for the table is released, when the library is closed or
//when the function is called again with a different size or when the conversion set is deleted.
//
//in:
// ph     -> Handle of the conversion set
// seed   -> initialisation value for random number generator
// size   -> size of table in bytes. Size should be at least 65536.
//
//out:


DWORD RS_CONV_CEXP PCO_RS_Get_Random(HANDLE ph,unsigned int *seed,int *size);
//Return the values which have been used to create the random table
//
//in:
// ph     -> Handle of the conversion set
//
//out:
// *seed   -> initialisation value for random number generator
// *size   -> size of table in bytes.


DWORD RS_CONV_CEXP PCO_RS_Set_Random_Offset(HANDLE ph,unsigned int offset);
//Does set the internal offset into the random table.
//This offset is counted up in every image conversion.
//Setting and reading the offset might be necessary to get always
//the same resulting 16Bit images from an image sequence saved in Raw-Format.
//
//in:
// ph     -> Handle of the conversion set
// offset -> offset into random table
//
//out:


DWORD RS_CONV_CEXP PCO_RS_Get_Random_Offset(HANDLE ph,unsigned int *offset);
//Does get the internal offset into the randomtable.
//in:
// ph     -> Handle of the conversion set
//
//out:
// *offset -> current value of internal counted offset value


DWORD RS_CONV_CEXP PCO_RS_Calculate(HANDLE ph,int width,int height,unsigned short *picin,unsigned short *picout);
//Calculate image from a raw pco.edge RollingShutter image, which does contain the packed 
//data image with sorted lines.
//
//in:
// ph     -> Handle of the conversion set
// width  -> camera image width
// height -> camera image height
// picin  -> pointer of buffer, which contains the packed camera image
//           size of this buffer must be ((width*12)/16)*height*2 Bytes  
// picout -> pointer of buffer, which receives the calculated image
//           size of this buffer must be width*height*2 Bytes  
//
//out:
//*picout -> resulting image data



DWORD RS_CONV_CEXP PCO_RS_Calculate_Off(HANDLE ph,int width,int height,unsigned short *picin,unsigned short *picout,unsigned int *off);
//Calculate image from a raw pco.edge RollingShutter image, which does contain the packed 
//data image with sorted lines.
//
//in:
// ph     -> Handle of the conversion set
// width   -> camera image width
// height  -> camera image height
// picin   -> pointer of buffer, which contains the packed camera image
//           size of this buffer must be ((width*12)/16)*height*2 Bytes  
// picout  -> pointer of buffer, which receives the calculated image
//           size of this buffer must be width*height*2 Bytes  
// *off    -> offset into random table, which should be used 
//            for calculation
//
//out:
// *picout -> resulting image data
// *off    -> offset into random table after calculation


DWORD RS_CONV_CEXP PCO_RS_Calculate_SB(HANDLE ph,int width,int height,unsigned short *pic_InOut);
//Calculate image from a raw pco.edge RollingShutter image, which does contain the packed 
//data image with sorted lines, Calculation is done in place 
//
//in:
// ph         -> Handle of the conversion set
// width      -> camera image width
// height     -> camera image height
// pic_InOut  -> pointer of buffer, which contains the packed camera image
//               and is filled with the calculated image
//               size of this buffer must be width*height*2 Bytes  
//
//out:
//*pic_InOut  -> resulting image data

DWORD RS_CONV_CEXP PCO_RS_Calculate_SB_Offset(HANDLE ph,int width,int height,unsigned short *pic_InOut,unsigned int *off);
//Calculate image from a raw pco.edge RollingShutter image, which does contain the packed 
//data image with sorted lines, Calculation is done in place 
//
//in:
// ph         -> Handle of the conversion set
// width      -> camera image width
// height     -> camera image height
// pic_InOut  -> pointer of buffer, which contains the packed camera image
//               and is filled with the calculated image
//               size of this buffer must be width*height*2 Bytes  
// *off       -> offset into random table, which should be used 
//               for calculation
//
//out:
//*pic_InOut  -> resulting image data


DWORD RS_CONV_CEXP PCO_RS_Calculate_Format(HANDLE ph,int Dataformat,int width,int height,unsigned short *picin,unsigned short *picout);
//Calculate image from a raw pco.edge RollingShutter image, which does contain the packed 
//data image in format DataFormat
//
//in:
// ph          -> Handle of the conversion set
// DataFormat  -> camera dataformat
// width       -> camera image width
// height      -> camera image height
// picin       -> pointer of buffer, which contains the packed camera image
//                size of this buffer must be ((width*12)/16)*height*2 Bytes  
// picout      -> pointer of buffer, which receives the calculated image
//                size of this buffer must be width*height*2 Bytes  
//
//out:
//*picout -> resulting image data



DWORD RS_CONV_CEXP PCO_RS_Calculate_Format_Offset(HANDLE ph,int Dataformat,int width,int height,unsigned short *picin,unsigned short *picout,unsigned int *off);
//Calculate image from a raw pco.edge RollingShutter image, which does contain the packed 
//data image in format DataFormat
//
//in:
// ph          -> Handle of the conversion set
// DataFormat  -> camera dataformat
// width       -> camera image width
// height      -> camera image height
// picin       -> pointer of buffer, which contains the packed camera image
//               size of this buffer must be ((width*12)/16)*height*2 Bytes  
// picout      -> pointer of buffer, which receives the calculated image
//               size of this buffer must be width*height*2 Bytes  
// *off        -> offset into random table, which should be used 
//                for calculation
//
//out:
// *picout -> resulting image data
// *off    -> offset into random table after calculation



#ifdef __cplusplus
}       //  Assume C declarations for C++
#endif  //C++
