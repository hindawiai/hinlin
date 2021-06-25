<शैली गुरु>
/****************************************************************************\
* 
*  Module Name    displayobjectsoc15.h
*  Project        
*  Device         
*
*  Description    Contains the common definitions क्रम display objects क्रम SoC15 products.
*
*  Copyright 2014 Advanced Micro Devices, Inc.
*
* Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy of this software 
* and associated करोcumentation files (the "Software"), to deal in the Software without restriction,
* including without limitation the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the Software is furnished to करो so,
* subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial
* portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
* THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
* OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*
\****************************************************************************/
#अगर_अघोषित _DISPLAY_OBJECT_SOC15_H_
#घोषणा _DISPLAY_OBJECT_SOC15_H_

#अगर defined(_X86_)
#आशय pack(1)
#पूर्ण_अगर


/****************************************************
* Display Object Type Definition 
*****************************************************/
क्रमागत display_object_typeअणु
DISPLAY_OBJECT_TYPE_NONE						=0x00,
DISPLAY_OBJECT_TYPE_GPU							=0x01,
DISPLAY_OBJECT_TYPE_ENCODER						=0x02,
DISPLAY_OBJECT_TYPE_CONNECTOR					=0x03
पूर्ण;

/****************************************************
* Encorder Object Type Definition 
*****************************************************/
क्रमागत encoder_object_typeअणु
ENCODER_OBJECT_ID_NONE							 =0x00,
ENCODER_OBJECT_ID_INTERNAL_UNIPHY				 =0x01,
ENCODER_OBJECT_ID_INTERNAL_UNIPHY1				 =0x02,
ENCODER_OBJECT_ID_INTERNAL_UNIPHY2				 =0x03,
पूर्ण;


/****************************************************
* Connector Object ID Definition 
*****************************************************/

क्रमागत connector_object_typeअणु
CONNECTOR_OBJECT_ID_NONE						  =0x00, 
CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D			  =0x01,
CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D				  =0x02,
CONNECTOR_OBJECT_ID_HDMI_TYPE_A					  =0x03,
CONNECTOR_OBJECT_ID_LVDS						  =0x04,
CONNECTOR_OBJECT_ID_DISPLAYPORT					  =0x05,
CONNECTOR_OBJECT_ID_eDP							  =0x06,
CONNECTOR_OBJECT_ID_OPM							  =0x07
पूर्ण;


/****************************************************
* Protection Object ID Definition 
*****************************************************/
//No need

/****************************************************
*  Object ENUM ID Definition 
*****************************************************/

क्रमागत object_क्रमागत_idअणु
OBJECT_ENUM_ID1									  =0x01,
OBJECT_ENUM_ID2									  =0x02,
OBJECT_ENUM_ID3									  =0x03,
OBJECT_ENUM_ID4									  =0x04,
OBJECT_ENUM_ID5									  =0x05,
OBJECT_ENUM_ID6									  =0x06
पूर्ण;

/****************************************************
*Object ID Bit definition 
*****************************************************/
क्रमागत object_id_bitअणु
OBJECT_ID_MASK									  =0x00FF,
ENUM_ID_MASK									  =0x0F00,
OBJECT_TYPE_MASK								  =0xF000,
OBJECT_ID_SHIFT									  =0x00,
ENUM_ID_SHIFT									  =0x08,
OBJECT_TYPE_SHIFT								  =0x0C
पूर्ण;


/****************************************************
* GPU Object definition - Shared with BIOS
*****************************************************/
क्रमागत gpu_objet_defअणु
GPU_ENUM_ID1                            =( DISPLAY_OBJECT_TYPE_GPU << OBJECT_TYPE_SHIFT | OBJECT_ENUM_ID1 << ENUM_ID_SHIFT)
पूर्ण;

/****************************************************
* Encoder Object definition - Shared with BIOS
*****************************************************/

क्रमागत encoder_objet_defअणु
ENCODER_INTERNAL_UNIPHY_ENUM_ID1         =( DISPLAY_OBJECT_TYPE_ENCODER << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 ENCODER_OBJECT_ID_INTERNAL_UNIPHY << OBJECT_ID_SHIFT),

ENCODER_INTERNAL_UNIPHY_ENUM_ID2         =( DISPLAY_OBJECT_TYPE_ENCODER << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 ENCODER_OBJECT_ID_INTERNAL_UNIPHY << OBJECT_ID_SHIFT),

ENCODER_INTERNAL_UNIPHY1_ENUM_ID1        =( DISPLAY_OBJECT_TYPE_ENCODER << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 ENCODER_OBJECT_ID_INTERNAL_UNIPHY1 << OBJECT_ID_SHIFT),

ENCODER_INTERNAL_UNIPHY1_ENUM_ID2        =( DISPLAY_OBJECT_TYPE_ENCODER << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 ENCODER_OBJECT_ID_INTERNAL_UNIPHY1 << OBJECT_ID_SHIFT),

ENCODER_INTERNAL_UNIPHY2_ENUM_ID1        =( DISPLAY_OBJECT_TYPE_ENCODER << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 ENCODER_OBJECT_ID_INTERNAL_UNIPHY2 << OBJECT_ID_SHIFT),

ENCODER_INTERNAL_UNIPHY2_ENUM_ID2        =( DISPLAY_OBJECT_TYPE_ENCODER << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 ENCODER_OBJECT_ID_INTERNAL_UNIPHY2 << OBJECT_ID_SHIFT)
पूर्ण;


/****************************************************
* Connector Object definition - Shared with BIOS
*****************************************************/


क्रमागत connector_objet_defअणु
CONNECTOR_LVDS_ENUM_ID1							=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_LVDS << OBJECT_ID_SHIFT),


CONNECTOR_eDP_ENUM_ID1							=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_eDP << OBJECT_ID_SHIFT),

CONNECTOR_SINGLE_LINK_DVI_D_ENUM_ID1			=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D << OBJECT_ID_SHIFT),

CONNECTOR_SINGLE_LINK_DVI_D_ENUM_ID2			=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_SINGLE_LINK_DVI_D << OBJECT_ID_SHIFT),


CONNECTOR_DUAL_LINK_DVI_D_ENUM_ID1				=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D << OBJECT_ID_SHIFT),

CONNECTOR_DUAL_LINK_DVI_D_ENUM_ID2				=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_DUAL_LINK_DVI_D << OBJECT_ID_SHIFT),

CONNECTOR_HDMI_TYPE_A_ENUM_ID1					=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_HDMI_TYPE_A << OBJECT_ID_SHIFT),

CONNECTOR_HDMI_TYPE_A_ENUM_ID2					=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_HDMI_TYPE_A << OBJECT_ID_SHIFT),

CONNECTOR_DISPLAYPORT_ENUM_ID1					=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_DISPLAYPORT << OBJECT_ID_SHIFT),

CONNECTOR_DISPLAYPORT_ENUM_ID2					=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_DISPLAYPORT << OBJECT_ID_SHIFT),

CONNECTOR_DISPLAYPORT_ENUM_ID3					=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID3 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_DISPLAYPORT << OBJECT_ID_SHIFT),

CONNECTOR_DISPLAYPORT_ENUM_ID4					=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID4 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_DISPLAYPORT << OBJECT_ID_SHIFT),

CONNECTOR_OPM_ENUM_ID1							=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID1 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_OPM << OBJECT_ID_SHIFT),          //Mapping to MXM_DP_A

CONNECTOR_OPM_ENUM_ID2							=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID2 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_OPM << OBJECT_ID_SHIFT),          //Mapping to MXM_DP_B

CONNECTOR_OPM_ENUM_ID3							=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID3 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_OPM << OBJECT_ID_SHIFT),          //Mapping to MXM_DP_C

CONNECTOR_OPM_ENUM_ID4							=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID4 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_OPM << OBJECT_ID_SHIFT),          //Mapping to MXM_DP_D

CONNECTOR_OPM_ENUM_ID5							=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID5 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_OPM << OBJECT_ID_SHIFT),          //Mapping to MXM_LVDS_TXxx


CONNECTOR_OPM_ENUM_ID6							=( DISPLAY_OBJECT_TYPE_CONNECTOR << OBJECT_TYPE_SHIFT |\
                                                 OBJECT_ENUM_ID6 << ENUM_ID_SHIFT |\
                                                 CONNECTOR_OBJECT_ID_OPM << OBJECT_ID_SHIFT)         //Mapping to MXM_LVDS_TXxx
पूर्ण;

/****************************************************
* Router Object ID definition - Shared with BIOS
*****************************************************/
//No Need, in future we ever need, we can define a record in atomfirwareSoC15.h associated with an object that has this router


/****************************************************
* PROTECTION Object ID definition - Shared with BIOS
*****************************************************/
//No need,in future we ever need, all display path are capable of protection now.

/****************************************************
* Generic Object ID definition - Shared with BIOS
*****************************************************/
//No need, in future we ever need like GLsync, we can define a record in atomfirwareSoC15.h associated with an object.


#अगर defined(_X86_)
#आशय pack()
#पूर्ण_अगर

#पूर्ण_अगर



