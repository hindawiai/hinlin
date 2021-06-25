<शैली गुरु>
/****************************************************************************\
* 
*  File Name      atomfirmware.h
*  Project        This is an पूर्णांकerface header file between atombios and OS GPU drivers क्रम SoC15 products
*
*  Description    header file of general definitions क्रम OS nd pre-OS video drivers 
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

/*IMPORTANT NOTES
* If a change in VBIOS/Driver/Tool's पूर्णांकerface is only needed क्रम SoC15 and क्रमward products, then the change is only needed in this atomfirmware.h header file.
* If a change in VBIOS/Driver/Tool's पूर्णांकerface is only needed क्रम pre-SoC15 products, then the change is only needed in atomमूलप्रण.स header file.
* If a change is needed क्रम both pre and post SoC15 products, then the change has to be made separately and might be dअगरferently in both atomfirmware.h and atomमूलप्रण.स.
*/

#अगर_अघोषित _ATOMFIRMWARE_H_
#घोषणा _ATOMFIRMWARE_H_

क्रमागत  atom_bios_header_version_defअणु
  ATOM_MAJOR_VERSION        =0x0003,
  ATOM_MINOR_VERSION        =0x0003,
पूर्ण;

#अगर_घोषित _H2INC
  #अगर_अघोषित uपूर्णांक32_t
    प्रकार अचिन्हित दीर्घ uपूर्णांक32_t;
  #पूर्ण_अगर

  #अगर_अघोषित uपूर्णांक16_t
    प्रकार अचिन्हित लघु uपूर्णांक16_t;
  #पूर्ण_अगर

  #अगर_अघोषित uपूर्णांक8_t 
    प्रकार अचिन्हित अक्षर uपूर्णांक8_t;
  #पूर्ण_अगर
#पूर्ण_अगर

क्रमागत atom_crtc_defअणु
  ATOM_CRTC1      =0,
  ATOM_CRTC2      =1,
  ATOM_CRTC3      =2,
  ATOM_CRTC4      =3,
  ATOM_CRTC5      =4,
  ATOM_CRTC6      =5,
  ATOM_CRTC_INVALID  =0xff,
पूर्ण;

क्रमागत atom_ppll_defअणु
  ATOM_PPLL0          =2,
  ATOM_GCK_DFS        =8,
  ATOM_FCH_CLK        =9,
  ATOM_DP_DTO         =11,
  ATOM_COMBOPHY_PLL0  =20,
  ATOM_COMBOPHY_PLL1  =21,
  ATOM_COMBOPHY_PLL2  =22,
  ATOM_COMBOPHY_PLL3  =23,
  ATOM_COMBOPHY_PLL4  =24,
  ATOM_COMBOPHY_PLL5  =25,
  ATOM_PPLL_INVALID   =0xff,
पूर्ण;

// define ASIC पूर्णांकernal encoder id ( bit vector ), used क्रम CRTC_SourceSel
क्रमागत atom_dig_defअणु
  ASIC_INT_DIG1_ENCODER_ID  =0x03,
  ASIC_INT_DIG2_ENCODER_ID  =0x09,
  ASIC_INT_DIG3_ENCODER_ID  =0x0a,
  ASIC_INT_DIG4_ENCODER_ID  =0x0b,
  ASIC_INT_DIG5_ENCODER_ID  =0x0c,
  ASIC_INT_DIG6_ENCODER_ID  =0x0d,
  ASIC_INT_DIG7_ENCODER_ID  =0x0e,
पूर्ण;

//ucEncoderMode
क्रमागत atom_encode_mode_def
अणु
  ATOM_ENCODER_MODE_DP          =0,
  ATOM_ENCODER_MODE_DP_SST      =0,
  ATOM_ENCODER_MODE_LVDS        =1,
  ATOM_ENCODER_MODE_DVI         =2,
  ATOM_ENCODER_MODE_HDMI        =3,
  ATOM_ENCODER_MODE_DP_AUDIO    =5,
  ATOM_ENCODER_MODE_DP_MST      =5,
  ATOM_ENCODER_MODE_CRT         =15,
  ATOM_ENCODER_MODE_DVO         =16,
पूर्ण;

क्रमागत atom_encoder_refclk_src_defअणु
  ENCODER_REFCLK_SRC_P1PLL      =0,
  ENCODER_REFCLK_SRC_P2PLL      =1,
  ENCODER_REFCLK_SRC_P3PLL      =2,
  ENCODER_REFCLK_SRC_EXTCLK     =3,
  ENCODER_REFCLK_SRC_INVALID    =0xff,
पूर्ण;

क्रमागत atom_scaler_defअणु
  ATOM_SCALER_DISABLE          =0,  /*scaler bypass mode, स्वतः-center & no replication*/
  ATOM_SCALER_CENTER           =1,  //For Fuकरो, it's bypass and स्वतः-center & स्वतः replication
  ATOM_SCALER_EXPANSION        =2,  /*scaler expansion by 2 tap alpha blending mode*/
पूर्ण;

क्रमागत atom_operation_defअणु
  ATOM_DISABLE             = 0,
  ATOM_ENABLE              = 1,
  ATOM_INIT                = 7,
  ATOM_GET_STATUS          = 8,
पूर्ण;

क्रमागत atom_embedded_display_op_defअणु
  ATOM_LCD_BL_OFF                = 2,
  ATOM_LCD_BL_OM                 = 3,
  ATOM_LCD_BL_BRIGHTNESS_CONTROL = 4,
  ATOM_LCD_SELFTEST_START        = 5,
  ATOM_LCD_SELFTEST_STOP         = 6,
पूर्ण;

क्रमागत atom_spपढ़ो_spectrum_modeअणु
  ATOM_SS_CENTER_OR_DOWN_MODE_MASK  = 0x01,
  ATOM_SS_DOWN_SPREAD_MODE          = 0x00,
  ATOM_SS_CENTRE_SPREAD_MODE        = 0x01,
  ATOM_INT_OR_EXT_SS_MASK           = 0x02,
  ATOM_INTERNAL_SS_MASK             = 0x00,
  ATOM_EXTERNAL_SS_MASK             = 0x02,
पूर्ण;

/* define panel bit per color  */
क्रमागत atom_panel_bit_per_colorअणु
  PANEL_BPC_UNDEFINE     =0x00,
  PANEL_6BIT_PER_COLOR   =0x01,
  PANEL_8BIT_PER_COLOR   =0x02,
  PANEL_10BIT_PER_COLOR  =0x03,
  PANEL_12BIT_PER_COLOR  =0x04,
  PANEL_16BIT_PER_COLOR  =0x05,
पूर्ण;

//ucVoltageType
क्रमागत atom_voltage_type
अणु
  VOLTAGE_TYPE_VDDC = 1,
  VOLTAGE_TYPE_MVDDC = 2,
  VOLTAGE_TYPE_MVDDQ = 3,
  VOLTAGE_TYPE_VDDCI = 4,
  VOLTAGE_TYPE_VDDGFX = 5,
  VOLTAGE_TYPE_PCC = 6,
  VOLTAGE_TYPE_MVPP = 7,
  VOLTAGE_TYPE_LEDDPM = 8,
  VOLTAGE_TYPE_PCC_MVDD = 9,
  VOLTAGE_TYPE_PCIE_VDDC = 10,
  VOLTAGE_TYPE_PCIE_VDDR = 11,
  VOLTAGE_TYPE_GENERIC_I2C_1 = 0x11,
  VOLTAGE_TYPE_GENERIC_I2C_2 = 0x12,
  VOLTAGE_TYPE_GENERIC_I2C_3 = 0x13,
  VOLTAGE_TYPE_GENERIC_I2C_4 = 0x14,
  VOLTAGE_TYPE_GENERIC_I2C_5 = 0x15,
  VOLTAGE_TYPE_GENERIC_I2C_6 = 0x16,
  VOLTAGE_TYPE_GENERIC_I2C_7 = 0x17,
  VOLTAGE_TYPE_GENERIC_I2C_8 = 0x18,
  VOLTAGE_TYPE_GENERIC_I2C_9 = 0x19,
  VOLTAGE_TYPE_GENERIC_I2C_10 = 0x1A,
पूर्ण;

क्रमागत atom_dgpu_vram_type अणु
  ATOM_DGPU_VRAM_TYPE_GDDR5 = 0x50,
  ATOM_DGPU_VRAM_TYPE_HBM2  = 0x60,
  ATOM_DGPU_VRAM_TYPE_HBM2E = 0x61,
  ATOM_DGPU_VRAM_TYPE_GDDR6 = 0x70,
पूर्ण;

क्रमागत atom_dp_vs_preemph_defअणु
  DP_VS_LEVEL0_PREEMPH_LEVEL0 = 0x00,
  DP_VS_LEVEL1_PREEMPH_LEVEL0 = 0x01,
  DP_VS_LEVEL2_PREEMPH_LEVEL0 = 0x02,
  DP_VS_LEVEL3_PREEMPH_LEVEL0 = 0x03,
  DP_VS_LEVEL0_PREEMPH_LEVEL1 = 0x08,
  DP_VS_LEVEL1_PREEMPH_LEVEL1 = 0x09,
  DP_VS_LEVEL2_PREEMPH_LEVEL1 = 0x0a,
  DP_VS_LEVEL0_PREEMPH_LEVEL2 = 0x10,
  DP_VS_LEVEL1_PREEMPH_LEVEL2 = 0x11,
  DP_VS_LEVEL0_PREEMPH_LEVEL3 = 0x18,
पूर्ण;


/*
क्रमागत atom_string_defअणु
asic_bus_type_pcie_string = "PCI_EXPRESS", 
atom_fire_gl_string       = "FGL",
atom_bios_string          = "ATOM"
पूर्ण;
*/

#आशय pack(1)                          /* BIOS data must use byte aligment*/

क्रमागत atombios_image_offsetअणु
OFFSET_TO_ATOM_ROM_HEADER_POINTER          =0x00000048,
OFFSET_TO_ATOM_ROM_IMAGE_SIZE              =0x00000002,
OFFSET_TO_ATOMBIOS_ASIC_BUS_MEM_TYPE       =0x94,
MAXSIZE_OF_ATOMBIOS_ASIC_BUS_MEM_TYPE      =20,  /*including the terminator 0x0!*/
OFFSET_TO_GET_ATOMBIOS_NUMBER_OF_STRINGS   =0x2f,
OFFSET_TO_GET_ATOMBIOS_STRING_START        =0x6e,
पूर्ण;

/****************************************************************************   
* Common header क्रम all tables (Data table, Command function).
* Every table poपूर्णांकed in _ATOM_MASTER_DATA_TABLE has this common header. 
* And the poपूर्णांकer actually poपूर्णांकs to this header.
****************************************************************************/   

काष्ठा atom_common_table_header
अणु
  uपूर्णांक16_t काष्ठाuresize;
  uपूर्णांक8_t  क्रमmat_revision;   //मुख्यly used क्रम a hw function, when the parser is not backward compatible 
  uपूर्णांक8_t  content_revision;  //change it when a data table has a काष्ठाure change, or a hw function has a input/output parameter change                                
पूर्ण;

/****************************************************************************  
* Structure stores the ROM header.
****************************************************************************/   
काष्ठा atom_rom_header_v2_2
अणु
  काष्ठा atom_common_table_header table_header;
  uपूर्णांक8_t  atom_bios_string[4];        //क्रमागत atom_string_def atom_bios_string;     //Signature to distinguish between Atombios and non-atombios, 
  uपूर्णांक16_t bios_segment_address;
  uपूर्णांक16_t रक्षितmodeoffset;
  uपूर्णांक16_t configfilenameoffset;
  uपूर्णांक16_t crc_block_offset;
  uपूर्णांक16_t vbios_bootupmessageoffset;
  uपूर्णांक16_t पूर्णांक10_offset;
  uपूर्णांक16_t pcibusdevinitcode;
  uपूर्णांक16_t iobaseaddress;
  uपूर्णांक16_t subप्रणाली_venकरोr_id;
  uपूर्णांक16_t subप्रणाली_id;
  uपूर्णांक16_t pci_info_offset;
  uपूर्णांक16_t masterhwfunction_offset;      //Offest क्रम SW to get all command function offsets, Don't change the position
  uपूर्णांक16_t masterdatatable_offset;       //Offest क्रम SW to get all data table offsets, Don't change the position
  uपूर्णांक16_t reserved;
  uपूर्णांक32_t pspdirtableoffset;
पूर्ण;

/*==============================hw function portion======================================================================*/


/****************************************************************************   
* Structures used in Command.mtb, each function name is not given here since those function could change from समय to समय
* The real functionality of each function is associated with the parameter काष्ठाure version when defined
* For all पूर्णांकernal cmd function definitions, please reference to atomकाष्ठा.h
****************************************************************************/   
काष्ठा atom_master_list_of_command_functions_v2_1अणु
  uपूर्णांक16_t asic_init;                   //Function
  uपूर्णांक16_t cmd_function1;               //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function2;               //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function3;               //used as an पूर्णांकernal one
  uपूर्णांक16_t digxencodercontrol;          //Function   
  uपूर्णांक16_t cmd_function5;               //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function6;               //used as an पूर्णांकernal one 
  uपूर्णांक16_t cmd_function7;               //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function8;               //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function9;               //used as an पूर्णांकernal one
  uपूर्णांक16_t setengineघड़ी;              //Function
  uपूर्णांक16_t seपंचांगemoryघड़ी;              //Function
  uपूर्णांक16_t setpixelघड़ी;               //Function
  uपूर्णांक16_t enabledispघातergating;       //Function            
  uपूर्णांक16_t cmd_function14;              //used as an पूर्णांकernal one             
  uपूर्णांक16_t cmd_function15;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function16;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function17;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function18;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function19;              //used as an पूर्णांकernal one 
  uपूर्णांक16_t cmd_function20;              //used as an पूर्णांकernal one               
  uपूर्णांक16_t cmd_function21;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function22;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function23;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function24;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function25;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function26;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function27;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function28;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function29;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function30;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function31;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function32;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function33;              //used as an पूर्णांकernal one
  uपूर्णांक16_t blankcrtc;                   //Function
  uपूर्णांक16_t enablecrtc;                  //Function
  uपूर्णांक16_t cmd_function36;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function37;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function38;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function39;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function40;              //used as an पूर्णांकernal one
  uपूर्णांक16_t माला_लोmuघड़ीinfo;             //Function
  uपूर्णांक16_t selectcrtc_source;           //Function
  uपूर्णांक16_t cmd_function43;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function44;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function45;              //used as an पूर्णांकernal one
  uपूर्णांक16_t setdceघड़ी;                 //Function
  uपूर्णांक16_t geपंचांगemoryघड़ी;              //Function           
  uपूर्णांक16_t getengineघड़ी;              //Function           
  uपूर्णांक16_t setcrtc_usingdtdtiming;      //Function
  uपूर्णांक16_t बाह्यalencodercontrol;      //Function 
  uपूर्णांक16_t cmd_function51;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function52;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function53;              //used as an पूर्णांकernal one
  uपूर्णांक16_t processi2cchanneltransaction;//Function           
  uपूर्णांक16_t cmd_function55;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function56;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function57;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function58;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function59;              //used as an पूर्णांकernal one
  uपूर्णांक16_t computegpuघड़ीparam;        //Function         
  uपूर्णांक16_t cmd_function61;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function62;              //used as an पूर्णांकernal one
  uपूर्णांक16_t dynamicmemorysettings;       //Function function
  uपूर्णांक16_t memorytraining;              //Function function
  uपूर्णांक16_t cmd_function65;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function66;              //used as an पूर्णांकernal one
  uपूर्णांक16_t setvoltage;                  //Function
  uपूर्णांक16_t cmd_function68;              //used as an पूर्णांकernal one
  uपूर्णांक16_t पढ़ोefusevalue;              //Function
  uपूर्णांक16_t cmd_function70;              //used as an पूर्णांकernal one 
  uपूर्णांक16_t cmd_function71;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function72;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function73;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function74;              //used as an पूर्णांकernal one
  uपूर्णांक16_t cmd_function75;              //used as an पूर्णांकernal one
  uपूर्णांक16_t dig1transmittercontrol;      //Function
  uपूर्णांक16_t cmd_function77;              //used as an पूर्णांकernal one
  uपूर्णांक16_t processauxchanneltransaction;//Function
  uपूर्णांक16_t cmd_function79;              //used as an पूर्णांकernal one
  uपूर्णांक16_t getvoltageinfo;              //Function
पूर्ण;

काष्ठा atom_master_command_function_v2_1
अणु
  काष्ठा atom_common_table_header  table_header;
  काष्ठा atom_master_list_of_command_functions_v2_1 listofcmdfunctions;
पूर्ण;

/**************************************************************************** 
* Structures used in every command function
****************************************************************************/   
काष्ठा atom_function_attribute
अणु
  uपूर्णांक16_t  ws_in_bytes:8;            //[7:0]=Size of workspace in Bytes (in multiple of a dword), 
  uपूर्णांक16_t  ps_in_bytes:7;            //[14:8]=Size of parameter space in Bytes (multiple of a dword), 
  uपूर्णांक16_t  updated_by_util:1;        //[15]=flag to indicate the function is updated by util
पूर्ण;


/**************************************************************************** 
* Common header क्रम all hw functions.
* Every function poपूर्णांकed by _master_list_of_hw_function has this common header. 
* And the poपूर्णांकer actually poपूर्णांकs to this header.
****************************************************************************/   
काष्ठा atom_rom_hw_function_header
अणु
  काष्ठा atom_common_table_header func_header;
  काष्ठा atom_function_attribute func_attrib;  
पूर्ण;


/*==============================sw data table portion======================================================================*/
/****************************************************************************
* Structures used in data.mtb, each data table name is not given here since those data table could change from समय to समय
* The real name of each table is given when its data काष्ठाure version is defined
****************************************************************************/
काष्ठा atom_master_list_of_data_tables_v2_1अणु
  uपूर्णांक16_t utilitypipeline;               /* Offest क्रम the utility to get parser info,Don't change this position!*/
  uपूर्णांक16_t mulसमयdia_info;               
  uपूर्णांक16_t smc_dpm_info;
  uपूर्णांक16_t sw_datatable3;                 
  uपूर्णांक16_t firmwareinfo;                  /* Shared by various SW components */
  uपूर्णांक16_t sw_datatable5;
  uपूर्णांक16_t lcd_info;                      /* Shared by various SW components */
  uपूर्णांक16_t sw_datatable7;
  uपूर्णांक16_t smu_info;                 
  uपूर्णांक16_t sw_datatable9;
  uपूर्णांक16_t sw_datatable10; 
  uपूर्णांक16_t vram_usagebyfirmware;          /* Shared by various SW components */
  uपूर्णांक16_t gpio_pin_lut;                  /* Shared by various SW components */
  uपूर्णांक16_t sw_datatable13; 
  uपूर्णांक16_t gfx_info;
  uपूर्णांक16_t घातerplayinfo;                 /* Shared by various SW components */
  uपूर्णांक16_t sw_datatable16;                
  uपूर्णांक16_t sw_datatable17;
  uपूर्णांक16_t sw_datatable18;
  uपूर्णांक16_t sw_datatable19;                
  uपूर्णांक16_t sw_datatable20;
  uपूर्णांक16_t sw_datatable21;
  uपूर्णांक16_t displayobjectinfo;             /* Shared by various SW components */
  uपूर्णांक16_t indirectioaccess;			  /* used as an पूर्णांकernal one */
  uपूर्णांक16_t umc_info;                      /* Shared by various SW components */
  uपूर्णांक16_t sw_datatable25;
  uपूर्णांक16_t sw_datatable26;
  uपूर्णांक16_t dce_info;                      /* Shared by various SW components */
  uपूर्णांक16_t vram_info;                     /* Shared by various SW components */
  uपूर्णांक16_t sw_datatable29;
  uपूर्णांक16_t पूर्णांकegratedप्रणालीinfo;          /* Shared by various SW components */
  uपूर्णांक16_t asic_profiling_info;           /* Shared by various SW components */
  uपूर्णांक16_t voltageobject_info;            /* shared by various SW components */
  uपूर्णांक16_t sw_datatable33;
  uपूर्णांक16_t sw_datatable34;
पूर्ण;


काष्ठा atom_master_data_table_v2_1
अणु 
  काष्ठा atom_common_table_header table_header;
  काष्ठा atom_master_list_of_data_tables_v2_1 listOfdatatables;
पूर्ण;


काष्ठा atom_dtd_क्रमmat
अणु
  uपूर्णांक16_t  pixclk;
  uपूर्णांक16_t  h_active;
  uपूर्णांक16_t  h_blanking_समय;
  uपूर्णांक16_t  v_active;
  uपूर्णांक16_t  v_blanking_समय;
  uपूर्णांक16_t  h_sync_offset;
  uपूर्णांक16_t  h_sync_width;
  uपूर्णांक16_t  v_sync_offset;
  uपूर्णांक16_t  v_syncwidth;
  uपूर्णांक16_t  reserved;
  uपूर्णांक16_t  reserved0;
  uपूर्णांक8_t   h_border;
  uपूर्णांक8_t   v_border;
  uपूर्णांक16_t  miscinfo;
  uपूर्णांक8_t   atom_mode_id;
  uपूर्णांक8_t   refreshrate;
पूर्ण;

/* atom_dtd_क्रमmat.modemiscinfo defपूर्णांकion */
क्रमागत atom_dtd_क्रमmat_modemiscinfoअणु
  ATOM_HSYNC_POLARITY    = 0x0002,
  ATOM_VSYNC_POLARITY    = 0x0004,
  ATOM_H_REPLICATIONBY2  = 0x0010,
  ATOM_V_REPLICATIONBY2  = 0x0020,
  ATOM_INTERLACE         = 0x0080,
  ATOM_COMPOSITESYNC     = 0x0040,
पूर्ण;


/* utilitypipeline
 * when क्रमmat_revision==1 && content_revision==1, then this an info table क्रम atomworks to use during debug session, no काष्ठाure is associated with it.
 * the location of it can't change
*/


/* 
  ***************************************************************************
    Data Table firmwareinfo  काष्ठाure
  ***************************************************************************
*/

काष्ठा atom_firmware_info_v3_1
अणु
  काष्ठा atom_common_table_header table_header;
  uपूर्णांक32_t firmware_revision;
  uपूर्णांक32_t bootup_sclk_in10khz;
  uपूर्णांक32_t bootup_mclk_in10khz;
  uपूर्णांक32_t firmware_capability;             // क्रमागत atombios_firmware_capability
  uपूर्णांक32_t मुख्य_call_parser_entry;          /* direct address of मुख्य parser call in VBIOS binary. */
  uपूर्णांक32_t bios_scratch_reg_startaddr;      // 1st bios scratch रेजिस्टर dword address 
  uपूर्णांक16_t bootup_vddc_mv;
  uपूर्णांक16_t bootup_vddci_mv; 
  uपूर्णांक16_t bootup_mvddc_mv;
  uपूर्णांक16_t bootup_vddgfx_mv;
  uपूर्णांक8_t  mem_module_id;       
  uपूर्णांक8_t  coolingsolution_id;              /*0: Air cooling; 1: Liquid cooling ... */
  uपूर्णांक8_t  reserved1[2];
  uपूर्णांक32_t mc_baseaddr_high;
  uपूर्णांक32_t mc_baseaddr_low;
  uपूर्णांक32_t reserved2[6];
पूर्ण;

/* Total 32bit cap indication */
क्रमागत atombios_firmware_capability
अणु
	ATOM_FIRMWARE_CAP_FIRMWARE_POSTED = 0x00000001,
	ATOM_FIRMWARE_CAP_GPU_VIRTUALIZATION  = 0x00000002,
	ATOM_FIRMWARE_CAP_WMI_SUPPORT  = 0x00000040,
	ATOM_FIRMWARE_CAP_HWEMU_ENABLE  = 0x00000080,
	ATOM_FIRMWARE_CAP_HWEMU_UMC_CFG = 0x00000100,
	ATOM_FIRMWARE_CAP_SRAM_ECC      = 0x00000200,
	ATOM_FIRMWARE_CAP_ENABLE_2STAGE_BIST_TRAINING  = 0x00000400,
	ATOM_FIRMWARE_CAP_ENABLE_2ND_USB20PORT = 0x0008000,
पूर्ण;

क्रमागत atom_cooling_solution_idअणु
  AIR_COOLING    = 0x00,
  LIQUID_COOLING = 0x01
पूर्ण;

काष्ठा atom_firmware_info_v3_2 अणु
  काष्ठा atom_common_table_header table_header;
  uपूर्णांक32_t firmware_revision;
  uपूर्णांक32_t bootup_sclk_in10khz;
  uपूर्णांक32_t bootup_mclk_in10khz;
  uपूर्णांक32_t firmware_capability;             // क्रमागत atombios_firmware_capability
  uपूर्णांक32_t मुख्य_call_parser_entry;          /* direct address of मुख्य parser call in VBIOS binary. */
  uपूर्णांक32_t bios_scratch_reg_startaddr;      // 1st bios scratch रेजिस्टर dword address
  uपूर्णांक16_t bootup_vddc_mv;
  uपूर्णांक16_t bootup_vddci_mv;
  uपूर्णांक16_t bootup_mvddc_mv;
  uपूर्णांक16_t bootup_vddgfx_mv;
  uपूर्णांक8_t  mem_module_id;
  uपूर्णांक8_t  coolingsolution_id;              /*0: Air cooling; 1: Liquid cooling ... */
  uपूर्णांक8_t  reserved1[2];
  uपूर्णांक32_t mc_baseaddr_high;
  uपूर्णांक32_t mc_baseaddr_low;
  uपूर्णांक8_t  board_i2c_feature_id;            // क्रमागत of atom_board_i2c_feature_id_def
  uपूर्णांक8_t  board_i2c_feature_gpio_id;       // i2c id find in gpio_lut data table gpio_id
  uपूर्णांक8_t  board_i2c_feature_slave_addr;
  uपूर्णांक8_t  reserved3;
  uपूर्णांक16_t bootup_mvddq_mv;
  uपूर्णांक16_t bootup_mvpp_mv;
  uपूर्णांक32_t zfbstartaddrin16mb;
  uपूर्णांक32_t reserved2[3];
पूर्ण;

काष्ठा atom_firmware_info_v3_3
अणु
  काष्ठा atom_common_table_header table_header;
  uपूर्णांक32_t firmware_revision;
  uपूर्णांक32_t bootup_sclk_in10khz;
  uपूर्णांक32_t bootup_mclk_in10khz;
  uपूर्णांक32_t firmware_capability;             // क्रमागत atombios_firmware_capability
  uपूर्णांक32_t मुख्य_call_parser_entry;          /* direct address of मुख्य parser call in VBIOS binary. */
  uपूर्णांक32_t bios_scratch_reg_startaddr;      // 1st bios scratch रेजिस्टर dword address
  uपूर्णांक16_t bootup_vddc_mv;
  uपूर्णांक16_t bootup_vddci_mv;
  uपूर्णांक16_t bootup_mvddc_mv;
  uपूर्णांक16_t bootup_vddgfx_mv;
  uपूर्णांक8_t  mem_module_id;
  uपूर्णांक8_t  coolingsolution_id;              /*0: Air cooling; 1: Liquid cooling ... */
  uपूर्णांक8_t  reserved1[2];
  uपूर्णांक32_t mc_baseaddr_high;
  uपूर्णांक32_t mc_baseaddr_low;
  uपूर्णांक8_t  board_i2c_feature_id;            // क्रमागत of atom_board_i2c_feature_id_def
  uपूर्णांक8_t  board_i2c_feature_gpio_id;       // i2c id find in gpio_lut data table gpio_id
  uपूर्णांक8_t  board_i2c_feature_slave_addr;
  uपूर्णांक8_t  reserved3;
  uपूर्णांक16_t bootup_mvddq_mv;
  uपूर्णांक16_t bootup_mvpp_mv;
  uपूर्णांक32_t zfbstartaddrin16mb;
  uपूर्णांक32_t pplib_pptable_id;                // अगर pplib_pptable_id!=0, pplib get घातerplay table inside driver instead of from VBIOS
  uपूर्णांक32_t reserved2[2];
पूर्ण;

काष्ठा atom_firmware_info_v3_4 अणु
	काष्ठा atom_common_table_header table_header;
	uपूर्णांक32_t firmware_revision;
	uपूर्णांक32_t bootup_sclk_in10khz;
	uपूर्णांक32_t bootup_mclk_in10khz;
	uपूर्णांक32_t firmware_capability;             // क्रमागत atombios_firmware_capability
	uपूर्णांक32_t मुख्य_call_parser_entry;          /* direct address of मुख्य parser call in VBIOS binary. */
	uपूर्णांक32_t bios_scratch_reg_startaddr;      // 1st bios scratch रेजिस्टर dword address
	uपूर्णांक16_t bootup_vddc_mv;
	uपूर्णांक16_t bootup_vddci_mv;
	uपूर्णांक16_t bootup_mvddc_mv;
	uपूर्णांक16_t bootup_vddgfx_mv;
	uपूर्णांक8_t  mem_module_id;
	uपूर्णांक8_t  coolingsolution_id;              /*0: Air cooling; 1: Liquid cooling ... */
	uपूर्णांक8_t  reserved1[2];
	uपूर्णांक32_t mc_baseaddr_high;
	uपूर्णांक32_t mc_baseaddr_low;
	uपूर्णांक8_t  board_i2c_feature_id;            // क्रमागत of atom_board_i2c_feature_id_def
	uपूर्णांक8_t  board_i2c_feature_gpio_id;       // i2c id find in gpio_lut data table gpio_id
	uपूर्णांक8_t  board_i2c_feature_slave_addr;
	uपूर्णांक8_t  reserved3;
	uपूर्णांक16_t bootup_mvddq_mv;
	uपूर्णांक16_t bootup_mvpp_mv;
	uपूर्णांक32_t zfbstartaddrin16mb;
	uपूर्णांक32_t pplib_pptable_id;                // अगर pplib_pptable_id!=0, pplib get घातerplay table inside driver instead of from VBIOS
	uपूर्णांक32_t mvdd_ratio;                      // mvdd_raio = (real mvdd in घातer rail)*1000/(mvdd_output_from_svi2)
	uपूर्णांक16_t hw_bootup_vddgfx_mv;             // hw शेष vddgfx voltage level decide by board strap
	uपूर्णांक16_t hw_bootup_vddc_mv;               // hw शेष vddc voltage level decide by board strap
	uपूर्णांक16_t hw_bootup_mvddc_mv;              // hw शेष mvddc voltage level decide by board strap
	uपूर्णांक16_t hw_bootup_vddci_mv;              // hw शेष vddci voltage level decide by board strap
	uपूर्णांक32_t maco_pwrlimit_mw;                // bomaco mode घातer limit in unit of m-watt
	uपूर्णांक32_t usb_pwrlimit_mw;                 // घातer limit when USB is enable in unit of m-watt
	uपूर्णांक32_t fw_reserved_size_in_kb;          // VBIOS reserved extra fw size in unit of kb.
        uपूर्णांक32_t pspbl_init_करोne_reg_addr;
        uपूर्णांक32_t pspbl_init_करोne_value;
        uपूर्णांक32_t pspbl_init_करोne_check_समयout;   // समय out in unit of us when polling pspbl init करोne
        uपूर्णांक32_t reserved[2];
पूर्ण;

/* 
  ***************************************************************************
    Data Table lcd_info  काष्ठाure
  ***************************************************************************
*/

काष्ठा lcd_info_v2_1
अणु
  काष्ठा  atom_common_table_header table_header;
  काष्ठा  atom_dtd_क्रमmat  lcd_timing;
  uपूर्णांक16_t backlight_pwm;
  uपूर्णांक16_t special_handle_cap;
  uपूर्णांक16_t panel_misc;
  uपूर्णांक16_t lvds_max_slink_pclk;
  uपूर्णांक16_t lvds_ss_percentage;
  uपूर्णांक16_t lvds_ss_rate_10hz;
  uपूर्णांक8_t  pwr_on_digon_to_de;          /*all pwr sequence numbers below are in uपूर्णांक of 4ms*/
  uपूर्णांक8_t  pwr_on_de_to_vary_bl;
  uपूर्णांक8_t  pwr_करोwn_vary_bloff_to_de;
  uपूर्णांक8_t  pwr_करोwn_de_to_digoff;
  uपूर्णांक8_t  pwr_off_delay;
  uपूर्णांक8_t  pwr_on_vary_bl_to_blon;
  uपूर्णांक8_t  pwr_करोwn_bloff_to_vary_bloff;
  uपूर्णांक8_t  panel_bpc;
  uपूर्णांक8_t  dpcd_edp_config_cap;
  uपूर्णांक8_t  dpcd_max_link_rate;
  uपूर्णांक8_t  dpcd_max_lane_count;
  uपूर्णांक8_t  dpcd_max_करोwnspपढ़ो;
  uपूर्णांक8_t  min_allowed_bl_level;
  uपूर्णांक8_t  max_allowed_bl_level;
  uपूर्णांक8_t  bootup_bl_level;
  uपूर्णांक8_t  dplvdsrxid;
  uपूर्णांक32_t reserved1[8];
पूर्ण;

/* lcd_info_v2_1.panel_misc defपूर्णांकion */
क्रमागत atom_lcd_info_panel_miscअणु
  ATOM_PANEL_MISC_FPDI            =0x0002,
पूर्ण;

//uceDPToLVDSRxId
क्रमागत atom_lcd_info_dptolvds_rx_id
अणु
  eDP_TO_LVDS_RX_DISABLE                 = 0x00,       // no eDP->LVDS translator chip 
  eDP_TO_LVDS_COMMON_ID                  = 0x01,       // common eDP->LVDS translator chip without AMD SW init
  eDP_TO_LVDS_REALTEK_ID                 = 0x02,       // Realtek tansaltor which require AMD SW init
पूर्ण;

    
/* 
  ***************************************************************************
    Data Table gpio_pin_lut  काष्ठाure
  ***************************************************************************
*/

काष्ठा atom_gpio_pin_assignment
अणु
  uपूर्णांक32_t data_a_reg_index;
  uपूर्णांक8_t  gpio_bitshअगरt;
  uपूर्णांक8_t  gpio_mask_bitshअगरt;
  uपूर्णांक8_t  gpio_id;
  uपूर्णांक8_t  reserved;
पूर्ण;

/* atom_gpio_pin_assignment.gpio_id definition */
क्रमागत atom_gpio_pin_assignment_gpio_id अणु
  I2C_HW_LANE_MUX        =0x0f, /* only valid when bit7=1 */
  I2C_HW_ENGINE_ID_MASK  =0x70, /* only valid when bit7=1 */ 
  I2C_HW_CAP             =0x80, /*only when the I2C_HW_CAP is set, the pin ID is asचिन्हित to an I2C pin pair, otherwise, it's an generic GPIO pin */

  /* gpio_id pre-define id क्रम multiple usage */
  /* GPIO use to control PCIE_VDDC in certain SLT board */
  PCIE_VDDC_CONTROL_GPIO_PINID = 56,
  /* अगर PP_AC_DC_SWITCH_GPIO_PINID in Gpio_Pin_LutTable, AC/DC swithing feature is enable */
  PP_AC_DC_SWITCH_GPIO_PINID = 60,
  /* VDDC_REGULATOR_VRHOT_GPIO_PINID in Gpio_Pin_LutTable, VRHot feature is enable */
  VDDC_VRHOT_GPIO_PINID = 61,
  /*अगर VDDC_PCC_GPIO_PINID in GPIO_LUTable, Peak Current Control feature is enabled */
  VDDC_PCC_GPIO_PINID = 62,
  /* Only used on certain SLT/PA board to allow utility to cut Efuse. */
  EFUSE_CUT_ENABLE_GPIO_PINID = 63,
  /* ucGPIO=DRAM_SELF_REFRESH_GPIO_PIND uses  क्रम memory self refresh (ucGPIO=0, DRAM self-refresh; ucGPIO= */
  DRAM_SELF_REFRESH_GPIO_PINID = 64,
  /* Thermal पूर्णांकerrupt output->प्रणाली thermal chip GPIO pin */
  THERMAL_INT_OUTPUT_GPIO_PINID =65,
पूर्ण;


काष्ठा atom_gpio_pin_lut_v2_1
अणु
  काष्ठा  atom_common_table_header  table_header;
  /*the real number of this included in the काष्ठाure is calcualted by using the (whole काष्ठाure size - the header size)/size of atom_gpio_pin_lut  */
  काष्ठा  atom_gpio_pin_assignment  gpio_pin[8];
पूर्ण;


/* 
  ***************************************************************************
    Data Table vram_usagebyfirmware  काष्ठाure
  ***************************************************************************
*/

काष्ठा vram_usagebyfirmware_v2_1
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक32_t  start_address_in_kb;
  uपूर्णांक16_t  used_by_firmware_in_kb;
  uपूर्णांक16_t  used_by_driver_in_kb; 
पूर्ण;


/* 
  ***************************************************************************
    Data Table displayobjectinfo  काष्ठाure
  ***************************************************************************
*/

क्रमागत atom_object_record_type_id 
अणु
  ATOM_I2C_RECORD_TYPE =1,
  ATOM_HPD_INT_RECORD_TYPE =2,
  ATOM_OBJECT_GPIO_CNTL_RECORD_TYPE =9,
  ATOM_CONNECTOR_HPDPIN_LUT_RECORD_TYPE =16,
  ATOM_CONNECTOR_AUXDDC_LUT_RECORD_TYPE =17,
  ATOM_ENCODER_CAP_RECORD_TYPE=20,
  ATOM_BRACKET_LAYOUT_RECORD_TYPE=21,
  ATOM_CONNECTOR_FORCED_TMDS_CAP_RECORD_TYPE=22,
  ATOM_DISP_CONNECTOR_CAPS_RECORD_TYPE=23,
  ATOM_RECORD_END_TYPE  =0xFF,
पूर्ण;

काष्ठा atom_common_record_header
अणु
  uपूर्णांक8_t record_type;                      //An emun to indicate the record type
  uपूर्णांक8_t record_size;                      //The size of the whole record in byte
पूर्ण;

काष्ठा atom_i2c_record
अणु
  काष्ठा atom_common_record_header record_header;   //record_type = ATOM_I2C_RECORD_TYPE
  uपूर्णांक8_t i2c_id; 
  uपूर्णांक8_t i2c_slave_addr;                   //The slave address, it's 0 when the record is attached to connector क्रम DDC
पूर्ण;

काष्ठा atom_hpd_पूर्णांक_record
अणु
  काष्ठा atom_common_record_header record_header;  //record_type = ATOM_HPD_INT_RECORD_TYPE
  uपूर्णांक8_t  pin_id;              //Corresponding block in GPIO_PIN_INFO table gives the pin info           
  uपूर्णांक8_t  plugin_pin_state;
पूर्ण;

// Bit maps क्रम ATOM_ENCODER_CAP_RECORD.usEncoderCap
क्रमागत atom_encoder_caps_def
अणु
  ATOM_ENCODER_CAP_RECORD_HBR2                  =0x01,         // DP1.2 HBR2 is supported by HW encoder, it is retired in NI. the real meaning from SI is MST_EN
  ATOM_ENCODER_CAP_RECORD_MST_EN                =0x01,         // from SI, this bit means DP MST is enable or not. 
  ATOM_ENCODER_CAP_RECORD_HBR2_EN               =0x02,         // DP1.2 HBR2 setting is qualअगरied and HBR2 can be enabled 
  ATOM_ENCODER_CAP_RECORD_HDMI6Gbps_EN          =0x04,         // HDMI2.0 6Gbps enable or not. 
  ATOM_ENCODER_CAP_RECORD_HBR3_EN               =0x08,         // DP1.3 HBR3 is supported by board. 
  ATOM_ENCODER_CAP_RECORD_USB_C_TYPE            =0x100,        // the DP connector is a USB-C type.
पूर्ण;

काष्ठा  atom_encoder_caps_record
अणु
  काष्ठा atom_common_record_header record_header;  //record_type = ATOM_ENCODER_CAP_RECORD_TYPE
  uपूर्णांक32_t  encodercaps;
पूर्ण;

क्रमागत atom_connector_caps_def
अणु
  ATOM_CONNECTOR_CAP_INTERNAL_DISPLAY         = 0x01,        //a cap bit to indicate that this non-embedded display connector is an पूर्णांकernal display
  ATOM_CONNECTOR_CAP_INTERNAL_DISPLAY_BL      = 0x02,        //a cap bit to indicate that this पूर्णांकernal display requires BL control from GPU, refers to lcd_info क्रम BL PWM freq 
पूर्ण;

काष्ठा atom_disp_connector_caps_record
अणु
  काष्ठा atom_common_record_header record_header;
  uपूर्णांक32_t connectcaps;                          
पूर्ण;

//The following generic object gpio pin control record type will replace JTAG_RECORD/FPGA_CONTROL_RECORD/DVI_EXT_INPUT_RECORD above gradually
काष्ठा atom_gpio_pin_control_pair
अणु
  uपूर्णांक8_t gpio_id;               // GPIO_ID, find the corresponding ID in GPIO_LUT table
  uपूर्णांक8_t gpio_pinstate;         // Pin state showing how to set-up the pin
पूर्ण;

काष्ठा atom_object_gpio_cntl_record
अणु
  काष्ठा atom_common_record_header record_header;
  uपूर्णांक8_t flag;                   // Future expnadibility
  uपूर्णांक8_t number_of_pins;         // Number of GPIO pins used to control the object
  काष्ठा atom_gpio_pin_control_pair gpio[1];              // the real gpio pin pair determined by number of pins ucNumberOfPins
पूर्ण;

//Definitions क्रम GPIO pin state 
क्रमागत atom_gpio_pin_control_pinstate_def
अणु
  GPIO_PIN_TYPE_INPUT             = 0x00,
  GPIO_PIN_TYPE_OUTPUT            = 0x10,
  GPIO_PIN_TYPE_HW_CONTROL        = 0x20,

//For GPIO_PIN_TYPE_OUTPUT the following is defined 
  GPIO_PIN_OUTPUT_STATE_MASK      = 0x01,
  GPIO_PIN_OUTPUT_STATE_SHIFT     = 0,
  GPIO_PIN_STATE_ACTIVE_LOW       = 0x0,
  GPIO_PIN_STATE_ACTIVE_HIGH      = 0x1,
पूर्ण;

// Indexes to GPIO array in GLSync record 
// GLSync record is क्रम Frame Lock/Gen Lock feature.
क्रमागत atom_glsync_record_gpio_index_def
अणु
  ATOM_GPIO_INDEX_GLSYNC_REFCLK    = 0,
  ATOM_GPIO_INDEX_GLSYNC_HSYNC     = 1,
  ATOM_GPIO_INDEX_GLSYNC_VSYNC     = 2,
  ATOM_GPIO_INDEX_GLSYNC_SWAP_REQ  = 3,
  ATOM_GPIO_INDEX_GLSYNC_SWAP_GNT  = 4,
  ATOM_GPIO_INDEX_GLSYNC_INTERRUPT = 5,
  ATOM_GPIO_INDEX_GLSYNC_V_RESET   = 6,
  ATOM_GPIO_INDEX_GLSYNC_SWAP_CNTL = 7,
  ATOM_GPIO_INDEX_GLSYNC_SWAP_SEL  = 8,
  ATOM_GPIO_INDEX_GLSYNC_MAX       = 9,
पूर्ण;


काष्ठा atom_connector_hpdpin_lut_record     //record क्रम ATOM_CONNECTOR_HPDPIN_LUT_RECORD_TYPE
अणु
  काष्ठा atom_common_record_header record_header;
  uपूर्णांक8_t hpd_pin_map[8];             
पूर्ण;

काष्ठा atom_connector_auxddc_lut_record     //record क्रम ATOM_CONNECTOR_AUXDDC_LUT_RECORD_TYPE
अणु
  काष्ठा atom_common_record_header record_header;
  uपूर्णांक8_t aux_ddc_map[8];
पूर्ण;

काष्ठा atom_connector_क्रमced_पंचांगds_cap_record
अणु
  काष्ठा atom_common_record_header record_header;
  // override TMDS capability on this connector when it operate in TMDS mode.  usMaxTmdsClkRate = max TMDS Clock in Mhz/2.5
  uपूर्णांक8_t  maxपंचांगdsclkrate_in2_5mhz;
  uपूर्णांक8_t  reserved;
पूर्ण;    

काष्ठा atom_connector_layout_info
अणु
  uपूर्णांक16_t connectorobjid;
  uपूर्णांक8_t  connector_type;
  uपूर्णांक8_t  position;
पूर्ण;

// define ATOM_CONNECTOR_LAYOUT_INFO.ucConnectorType to describe the display connector size
क्रमागत atom_connector_layout_info_connector_type_def
अणु
  CONNECTOR_TYPE_DVI_D                 = 1,
 
  CONNECTOR_TYPE_HDMI                  = 4,
  CONNECTOR_TYPE_DISPLAY_PORT          = 5,
  CONNECTOR_TYPE_MINI_DISPLAY_PORT     = 6,
पूर्ण;

काष्ठा  atom_bracket_layout_record
अणु
  काष्ठा atom_common_record_header record_header;
  uपूर्णांक8_t bracketlen;
  uपूर्णांक8_t bracketwidth;
  uपूर्णांक8_t conn_num;
  uपूर्णांक8_t reserved;
  काष्ठा atom_connector_layout_info  conn_info[1];
पूर्ण;

क्रमागत atom_display_device_tag_defअणु
  ATOM_DISPLAY_LCD1_SUPPORT            = 0x0002,  //an embedded display is either an LVDS or eDP संकेत type of display
  ATOM_DISPLAY_DFP1_SUPPORT            = 0x0008,
  ATOM_DISPLAY_DFP2_SUPPORT            = 0x0080,
  ATOM_DISPLAY_DFP3_SUPPORT            = 0x0200,
  ATOM_DISPLAY_DFP4_SUPPORT            = 0x0400,
  ATOM_DISPLAY_DFP5_SUPPORT            = 0x0800,
  ATOM_DISPLAY_DFP6_SUPPORT            = 0x0040,
  ATOM_DISPLAY_DFPx_SUPPORT            = 0x0ec8,
पूर्ण;

काष्ठा atom_display_object_path_v2
अणु
  uपूर्णांक16_t display_objid;                  //Connector Object ID or Misc Object ID
  uपूर्णांक16_t disp_recorकरोffset;
  uपूर्णांक16_t encoderobjid;                   //first encoder बंदr to the connector, could be either an बाह्यal or पूर्णांकenal encoder
  uपूर्णांक16_t extencoderobjid;                //2nd encoder after the first encoder, from the connector poपूर्णांक of view;
  uपूर्णांक16_t encoder_recorकरोffset;
  uपूर्णांक16_t extencoder_recorकरोffset;
  uपूर्णांक16_t device_tag;                     //a supported device vector, each display path starts with this.the paths are क्रमागतerated in the way of priority, a path appears first 
  uपूर्णांक8_t  priority_id;
  uपूर्णांक8_t  reserved;
पूर्ण;

काष्ठा display_object_info_table_v1_4
अणु
  काष्ठा    atom_common_table_header  table_header;
  uपूर्णांक16_t  supporteddevices;
  uपूर्णांक8_t   number_of_path;
  uपूर्णांक8_t   reserved;
  काष्ठा    atom_display_object_path_v2 display_path[8];   //the real number of this included in the काष्ठाure is calculated by using the (whole काष्ठाure size - the header size- number_of_path)/size of atom_display_object_path
पूर्ण;


/* 
  ***************************************************************************
    Data Table dce_info  काष्ठाure
  ***************************************************************************
*/
काष्ठा atom_display_controller_info_v4_1
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक32_t display_caps;
  uपूर्णांक32_t bootup_dispclk_10khz;
  uपूर्णांक16_t dce_refclk_10khz;
  uपूर्णांक16_t i2c_engine_refclk_10khz;
  uपूर्णांक16_t dvi_ss_percentage;       // in unit of 0.001%
  uपूर्णांक16_t dvi_ss_rate_10hz;        
  uपूर्णांक16_t hdmi_ss_percentage;      // in unit of 0.001%
  uपूर्णांक16_t hdmi_ss_rate_10hz;
  uपूर्णांक16_t dp_ss_percentage;        // in unit of 0.001%
  uपूर्णांक16_t dp_ss_rate_10hz;
  uपूर्णांक8_t  dvi_ss_mode;             // क्रमागत of atom_spपढ़ो_spectrum_mode
  uपूर्णांक8_t  hdmi_ss_mode;            // क्रमागत of atom_spपढ़ो_spectrum_mode
  uपूर्णांक8_t  dp_ss_mode;              // क्रमागत of atom_spपढ़ो_spectrum_mode 
  uपूर्णांक8_t  ss_reserved;
  uपूर्णांक8_t  hardcode_mode_num;       // a hardcode mode number defined in StandardVESA_TimingTable when a CRT or DFP EDID is not available
  uपूर्णांक8_t  reserved1[3];
  uपूर्णांक16_t dpphy_refclk_10khz;  
  uपूर्णांक16_t reserved2;
  uपूर्णांक8_t  dceip_min_ver;
  uपूर्णांक8_t  dceip_max_ver;
  uपूर्णांक8_t  max_disp_pipe_num;
  uपूर्णांक8_t  max_vbios_active_disp_pipe_num;
  uपूर्णांक8_t  max_ppll_num;
  uपूर्णांक8_t  max_disp_phy_num;
  uपूर्णांक8_t  max_aux_pairs;
  uपूर्णांक8_t  remotedisplayconfig;
  uपूर्णांक8_t  reserved3[8];
पूर्ण;

काष्ठा atom_display_controller_info_v4_2
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक32_t display_caps;            
  uपूर्णांक32_t bootup_dispclk_10khz;
  uपूर्णांक16_t dce_refclk_10khz;
  uपूर्णांक16_t i2c_engine_refclk_10khz;
  uपूर्णांक16_t dvi_ss_percentage;       // in unit of 0.001%   
  uपूर्णांक16_t dvi_ss_rate_10hz;
  uपूर्णांक16_t hdmi_ss_percentage;      // in unit of 0.001%
  uपूर्णांक16_t hdmi_ss_rate_10hz;
  uपूर्णांक16_t dp_ss_percentage;        // in unit of 0.001%
  uपूर्णांक16_t dp_ss_rate_10hz;
  uपूर्णांक8_t  dvi_ss_mode;             // क्रमागत of atom_spपढ़ो_spectrum_mode
  uपूर्णांक8_t  hdmi_ss_mode;            // क्रमागत of atom_spपढ़ो_spectrum_mode
  uपूर्णांक8_t  dp_ss_mode;              // क्रमागत of atom_spपढ़ो_spectrum_mode 
  uपूर्णांक8_t  ss_reserved;
  uपूर्णांक8_t  dfp_hardcode_mode_num;   // DFP hardcode mode number defined in StandardVESA_TimingTable when EDID is not available
  uपूर्णांक8_t  dfp_hardcode_refreshrate;// DFP hardcode mode refreshrate defined in StandardVESA_TimingTable when EDID is not available
  uपूर्णांक8_t  vga_hardcode_mode_num;   // VGA hardcode mode number defined in StandardVESA_TimingTable when EDID is not avablable
  uपूर्णांक8_t  vga_hardcode_refreshrate;// VGA hardcode mode number defined in StandardVESA_TimingTable when EDID is not avablable
  uपूर्णांक16_t dpphy_refclk_10khz;  
  uपूर्णांक16_t reserved2;
  uपूर्णांक8_t  dcnip_min_ver;
  uपूर्णांक8_t  dcnip_max_ver;
  uपूर्णांक8_t  max_disp_pipe_num;
  uपूर्णांक8_t  max_vbios_active_disp_pipe_num;
  uपूर्णांक8_t  max_ppll_num;
  uपूर्णांक8_t  max_disp_phy_num;
  uपूर्णांक8_t  max_aux_pairs;
  uपूर्णांक8_t  remotedisplayconfig;
  uपूर्णांक8_t  reserved3[8];
पूर्ण;

काष्ठा atom_display_controller_info_v4_3
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक32_t display_caps;
  uपूर्णांक32_t bootup_dispclk_10khz;
  uपूर्णांक16_t dce_refclk_10khz;
  uपूर्णांक16_t i2c_engine_refclk_10khz;
  uपूर्णांक16_t dvi_ss_percentage;       // in unit of 0.001%
  uपूर्णांक16_t dvi_ss_rate_10hz;
  uपूर्णांक16_t hdmi_ss_percentage;      // in unit of 0.001%
  uपूर्णांक16_t hdmi_ss_rate_10hz;
  uपूर्णांक16_t dp_ss_percentage;        // in unit of 0.001%
  uपूर्णांक16_t dp_ss_rate_10hz;
  uपूर्णांक8_t  dvi_ss_mode;             // क्रमागत of atom_spपढ़ो_spectrum_mode
  uपूर्णांक8_t  hdmi_ss_mode;            // क्रमागत of atom_spपढ़ो_spectrum_mode
  uपूर्णांक8_t  dp_ss_mode;              // क्रमागत of atom_spपढ़ो_spectrum_mode
  uपूर्णांक8_t  ss_reserved;
  uपूर्णांक8_t  dfp_hardcode_mode_num;   // DFP hardcode mode number defined in StandardVESA_TimingTable when EDID is not available
  uपूर्णांक8_t  dfp_hardcode_refreshrate;// DFP hardcode mode refreshrate defined in StandardVESA_TimingTable when EDID is not available
  uपूर्णांक8_t  vga_hardcode_mode_num;   // VGA hardcode mode number defined in StandardVESA_TimingTable when EDID is not avablable
  uपूर्णांक8_t  vga_hardcode_refreshrate;// VGA hardcode mode number defined in StandardVESA_TimingTable when EDID is not avablable
  uपूर्णांक16_t dpphy_refclk_10khz;
  uपूर्णांक16_t reserved2;
  uपूर्णांक8_t  dcnip_min_ver;
  uपूर्णांक8_t  dcnip_max_ver;
  uपूर्णांक8_t  max_disp_pipe_num;
  uपूर्णांक8_t  max_vbios_active_disp_pipe_num;
  uपूर्णांक8_t  max_ppll_num;
  uपूर्णांक8_t  max_disp_phy_num;
  uपूर्णांक8_t  max_aux_pairs;
  uपूर्णांक8_t  remotedisplayconfig;
  uपूर्णांक8_t  reserved3[8];
पूर्ण;

काष्ठा atom_display_controller_info_v4_4 अणु
	काष्ठा atom_common_table_header table_header;
	uपूर्णांक32_t display_caps;
	uपूर्णांक32_t bootup_dispclk_10khz;
	uपूर्णांक16_t dce_refclk_10khz;
	uपूर्णांक16_t i2c_engine_refclk_10khz;
	uपूर्णांक16_t dvi_ss_percentage;	 // in unit of 0.001%
	uपूर्णांक16_t dvi_ss_rate_10hz;
	uपूर्णांक16_t hdmi_ss_percentage;	 // in unit of 0.001%
	uपूर्णांक16_t hdmi_ss_rate_10hz;
	uपूर्णांक16_t dp_ss_percentage;	 // in unit of 0.001%
	uपूर्णांक16_t dp_ss_rate_10hz;
	uपूर्णांक8_t dvi_ss_mode;		 // क्रमागत of atom_spपढ़ो_spectrum_mode
	uपूर्णांक8_t hdmi_ss_mode;		 // क्रमागत of atom_spपढ़ो_spectrum_mode
	uपूर्णांक8_t dp_ss_mode;		 // क्रमागत of atom_spपढ़ो_spectrum_mode
	uपूर्णांक8_t ss_reserved;
	uपूर्णांक8_t dfp_hardcode_mode_num;	 // DFP hardcode mode number defined in StandardVESA_TimingTable when EDID is not available
	uपूर्णांक8_t dfp_hardcode_refreshrate;// DFP hardcode mode refreshrate defined in StandardVESA_TimingTable when EDID is not available
	uपूर्णांक8_t vga_hardcode_mode_num;	 // VGA hardcode mode number defined in StandardVESA_TimingTable when EDID is not avablable
	uपूर्णांक8_t vga_hardcode_refreshrate;// VGA hardcode mode number defined in StandardVESA_TimingTable when EDID is not avablable
	uपूर्णांक16_t dpphy_refclk_10khz;
	uपूर्णांक16_t hw_chip_id;
	uपूर्णांक8_t dcnip_min_ver;
	uपूर्णांक8_t dcnip_max_ver;
	uपूर्णांक8_t max_disp_pipe_num;
	uपूर्णांक8_t max_vbios_active_disp_pipum;
	uपूर्णांक8_t max_ppll_num;
	uपूर्णांक8_t max_disp_phy_num;
	uपूर्णांक8_t max_aux_pairs;
	uपूर्णांक8_t remotedisplayconfig;
	uपूर्णांक32_t dispclk_pll_vco_freq;
	uपूर्णांक32_t dp_ref_clk_freq;
	uपूर्णांक32_t max_mclk_chg_lat;	 // Worst हाल blackout duration क्रम a memory घड़ी frequency (p-state) change, units of 100s of ns (0.1 us)
	uपूर्णांक32_t max_sr_निकास_lat;	 // Worst हाल memory self refresh निकास समय, units of 100ns of ns (0.1us)
	uपूर्णांक32_t max_sr_enter_निकास_lat;	 // Worst हाल memory self refresh entry followed by immediate निकास समय, units of 100ns of ns (0.1us)
	uपूर्णांक16_t dc_golden_table_offset; // poपूर्णांक of काष्ठा of atom_dc_golden_table_vxx
	uपूर्णांक16_t dc_golden_table_ver;
	uपूर्णांक32_t reserved3[3];
पूर्ण;

काष्ठा atom_dc_golden_table_v1
अणु
	uपूर्णांक32_t aux_dphy_rx_control0_val;
	uपूर्णांक32_t aux_dphy_tx_control_val;
	uपूर्णांक32_t aux_dphy_rx_control1_val;
	uपूर्णांक32_t dc_gpio_aux_ctrl_0_val;
	uपूर्णांक32_t dc_gpio_aux_ctrl_1_val;
	uपूर्णांक32_t dc_gpio_aux_ctrl_2_val;
	uपूर्णांक32_t dc_gpio_aux_ctrl_3_val;
	uपूर्णांक32_t dc_gpio_aux_ctrl_4_val;
	uपूर्णांक32_t dc_gpio_aux_ctrl_5_val;
	uपूर्णांक32_t reserved[23];
पूर्ण;

क्रमागत dce_info_caps_def
अणु
  // only क्रम VBIOS
  DCE_INFO_CAPS_FORCE_DISPDEV_CONNECTED  =0x02,      
  // only क्रम VBIOS
  DCE_INFO_CAPS_DISABLE_DFP_DP_HBR2      =0x04,
  // only क्रम VBIOS
  DCE_INFO_CAPS_ENABLE_INTERLAC_TIMING   =0x08,
  // only क्रम VBIOS
  DCE_INFO_CAPS_LTTPR_SUPPORT_ENABLE	 =0x20,
  DCE_INFO_CAPS_VBIOS_LTTPR_TRANSPARENT_ENABLE = 0x40,
पूर्ण;

/* 
  ***************************************************************************
    Data Table ATOM_EXTERNAL_DISPLAY_CONNECTION_INFO  काष्ठाure
  ***************************************************************************
*/
काष्ठा atom_ext_display_path
अणु
  uपूर्णांक16_t  device_tag;                      //A bit vector to show what devices are supported 
  uपूर्णांक16_t  device_acpi_क्रमागत;                //16bit device ACPI id. 
  uपूर्णांक16_t  connectorobjid;                  //A physical connector क्रम displays to plug in, using object connector definitions
  uपूर्णांक8_t   auxddclut_index;                 //An index पूर्णांकo बाह्यal AUX/DDC channel LUT
  uपूर्णांक8_t   hpdlut_index;                    //An index पूर्णांकo बाह्यal HPD pin LUT
  uपूर्णांक16_t  ext_encoder_objid;               //बाह्यal encoder object id
  uपूर्णांक8_t   channelmapping;                  // अगर ucChannelMapping=0, using शेष one to one mapping
  uपूर्णांक8_t   chpninvert;                      // bit vector क्रम up to 8 lanes, =0: P and N is not invert, =1 P and N is inverted
  uपूर्णांक16_t  caps;
  uपूर्णांक16_t  reserved; 
पूर्ण;

//usCaps
क्रमागत ext_display_path_cap_def अणु
	EXT_DISPLAY_PATH_CAPS__HBR2_DISABLE =           0x0001,
	EXT_DISPLAY_PATH_CAPS__DP_FIXED_VS_EN =         0x0002,
	EXT_DISPLAY_PATH_CAPS__EXT_CHIP_MASK =          0x007C,
	EXT_DISPLAY_PATH_CAPS__HDMI20_PI3EQX1204 =      (0x01 << 2), //PI redriver chip
	EXT_DISPLAY_PATH_CAPS__HDMI20_TISN65DP159RSBT = (0x02 << 2), //TI reसमयr chip
	EXT_DISPLAY_PATH_CAPS__HDMI20_PARADE_PS175 =    (0x03 << 2)  //Parade DP->HDMI recoverter chip
पूर्ण;

काष्ठा atom_बाह्यal_display_connection_info
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक8_t                  guid[16];                                  // a GUID is a 16 byte दीर्घ string
  काष्ठा atom_ext_display_path path[7];                               // total of fixed 7 entries.
  uपूर्णांक8_t                  checksum;                                  // a simple Checksum of the sum of whole काष्ठाure equal to 0x0. 
  uपूर्णांक8_t                  stereopinid;                               // use क्रम eDP panel
  uपूर्णांक8_t                  remotedisplayconfig;
  uपूर्णांक8_t                  edptolvdsrxid;
  uपूर्णांक8_t                  fixdpvoltageswing;                         // usCaps[1]=1, this indicate DP_LANE_SET value
  uपूर्णांक8_t                  reserved[3];                               // क्रम potential expansion
पूर्ण;

/* 
  ***************************************************************************
    Data Table पूर्णांकegratedप्रणालीinfo  काष्ठाure
  ***************************************************************************
*/

काष्ठा atom_camera_dphy_timing_param
अणु
  uपूर्णांक8_t  profile_id;       // SENSOR_PROखाताS
  uपूर्णांक32_t param;
पूर्ण;

काष्ठा atom_camera_dphy_elec_param
अणु
  uपूर्णांक16_t param[3];
पूर्ण;

काष्ठा atom_camera_module_info
अणु
  uपूर्णांक8_t module_id;                    // 0: Rear, 1: Front right of user, 2: Front left of user
  uपूर्णांक8_t module_name[8];
  काष्ठा atom_camera_dphy_timing_param timingparam[6]; // Exact number is under estimation and confirmation from sensor venकरोr
पूर्ण;

काष्ठा atom_camera_flashlight_info
अणु
  uपूर्णांक8_t flashlight_id;                // 0: Rear, 1: Front
  uपूर्णांक8_t name[8];
पूर्ण;

काष्ठा atom_camera_data
अणु
  uपूर्णांक32_t versionCode;
  काष्ठा atom_camera_module_info cameraInfo[3];      // Assuming 3 camera sensors max
  काष्ठा atom_camera_flashlight_info flashInfo;      // Assuming 1 flashlight max
  काष्ठा atom_camera_dphy_elec_param dphy_param;
  uपूर्णांक32_t crc_val;         // CRC
पूर्ण;


काष्ठा atom_14nm_dpphy_dvihdmi_tuningset
अणु
  uपूर्णांक32_t max_symclk_in10khz;
  uपूर्णांक8_t encoder_mode;            //atom_encode_mode_def, =2: DVI, =3: HDMI mode
  uपूर्णांक8_t phy_sel;                 //bit vector of phy, bit0= phya, bit1=phyb, ....bit5 = phyf 
  uपूर्णांक16_t margindeemph;           //COMMON_MAR_DEEMPH_NOM[7:0]tx_margin_nom [15:8]deemph_gen1_nom
  uपूर्णांक8_t deemph_6db_4;            //COMMON_SELDEEMPH60[31:24]deemph_6db_4
  uपूर्णांक8_t boostadj;                //CMD_BUS_GLOBAL_FOR_TX_LANE0 [19:16]tx_boost_adj  [20]tx_boost_en  [23:22]tx_binary_ron_code_offset
  uपूर्णांक8_t tx_driver_fअगरty_ohms;    //COMMON_ZCALCODE_CTRL[21].tx_driver_fअगरty_ohms
  uपूर्णांक8_t deemph_sel;              //MARGIN_DEEMPH_LANE0.DEEMPH_SEL
पूर्ण;

काष्ठा atom_14nm_dpphy_dp_settingअणु
  uपूर्णांक8_t dp_vs_pemph_level;       //क्रमागत of atom_dp_vs_preemph_def
  uपूर्णांक16_t margindeemph;           //COMMON_MAR_DEEMPH_NOM[7:0]tx_margin_nom [15:8]deemph_gen1_nom
  uपूर्णांक8_t deemph_6db_4;            //COMMON_SELDEEMPH60[31:24]deemph_6db_4
  uपूर्णांक8_t boostadj;                //CMD_BUS_GLOBAL_FOR_TX_LANE0 [19:16]tx_boost_adj  [20]tx_boost_en  [23:22]tx_binary_ron_code_offset
पूर्ण;

काष्ठा atom_14nm_dpphy_dp_tuningsetअणु
  uपूर्णांक8_t phy_sel;                 // bit vector of phy, bit0= phya, bit1=phyb, ....bit5 = phyf 
  uपूर्णांक8_t version;
  uपूर्णांक16_t table_size;             // size of atom_14nm_dpphy_dp_tuningset
  uपूर्णांक16_t reserved;
  काष्ठा atom_14nm_dpphy_dp_setting dptuning[10];
पूर्ण;

काष्ठा atom_14nm_dig_transmitter_info_header_v4_0अणु  
  काष्ठा  atom_common_table_header  table_header;  
  uपूर्णांक16_t pcie_phy_पंचांगds_hdmi_macro_settings_offset;     // offset of PCIEPhyTMDSHDMIMacroSettingsTbl 
  uपूर्णांक16_t uniphy_vs_emph_lookup_table_offset;           // offset of UniphyVSEmphLookUpTbl
  uपूर्णांक16_t uniphy_xbar_settings_table_offset;            // offset of UniphyXbarSettingsTbl
पूर्ण;

काष्ठा atom_14nm_combphy_पंचांगds_vs_set
अणु
  uपूर्णांक8_t sym_clk;
  uपूर्णांक8_t dig_mode;
  uपूर्णांक8_t phy_sel;
  uपूर्णांक16_t common_mar_deemph_nom__margin_deemph_val;
  uपूर्णांक8_t common_seldeemph60__deemph_6db_4_val;
  uपूर्णांक8_t cmd_bus_global_क्रम_tx_lane0__boostadj_val ;
  uपूर्णांक8_t common_zcalcode_ctrl__tx_driver_fअगरty_ohms_val;
  uपूर्णांक8_t margin_deemph_lane0__deemph_sel_val;         
पूर्ण;

काष्ठा atom_DCN_dpphy_dvihdmi_tuningset
अणु
  uपूर्णांक32_t max_symclk_in10khz;
  uपूर्णांक8_t  encoder_mode;           //atom_encode_mode_def, =2: DVI, =3: HDMI mode
  uपूर्णांक8_t  phy_sel;                //bit vector of phy, bit0= phya, bit1=phyb, ....bit5 = phyf 
  uपूर्णांक8_t  tx_eq_मुख्य;             // map to RDPCSTX_PHY_FUSE0/1/2/3[5:0](EQ_MAIN)
  uपूर्णांक8_t  tx_eq_pre;              // map to RDPCSTX_PHY_FUSE0/1/2/3[11:6](EQ_PRE)
  uपूर्णांक8_t  tx_eq_post;             // map to RDPCSTX_PHY_FUSE0/1/2/3[17:12](EQ_POST)
  uपूर्णांक8_t  reserved1;
  uपूर्णांक8_t  tx_vboost_lvl;          // tx_vboost_lvl, map to RDPCSTX_PHY_CNTL0.RDPCS_PHY_TX_VBOOST_LVL
  uपूर्णांक8_t  reserved2;
पूर्ण;

काष्ठा atom_DCN_dpphy_dp_settingअणु
  uपूर्णांक8_t dp_vs_pemph_level;       //क्रमागत of atom_dp_vs_preemph_def
  uपूर्णांक8_t tx_eq_मुख्य;             // map to RDPCSTX_PHY_FUSE0/1/2/3[5:0](EQ_MAIN)
  uपूर्णांक8_t tx_eq_pre;              // map to RDPCSTX_PHY_FUSE0/1/2/3[11:6](EQ_PRE)
  uपूर्णांक8_t tx_eq_post;             // map to RDPCSTX_PHY_FUSE0/1/2/3[17:12](EQ_POST)
  uपूर्णांक8_t tx_vboost_lvl;          // tx_vboost_lvl, map to RDPCSTX_PHY_CNTL0.RDPCS_PHY_TX_VBOOST_LVL
पूर्ण;

काष्ठा atom_DCN_dpphy_dp_tuningsetअणु
  uपूर्णांक8_t phy_sel;                 // bit vector of phy, bit0= phya, bit1=phyb, ....bit5 = phyf 
  uपूर्णांक8_t version;
  uपूर्णांक16_t table_size;             // size of atom_14nm_dpphy_dp_setting
  uपूर्णांक16_t reserved;
  काष्ठा atom_DCN_dpphy_dp_setting dptunings[10];
पूर्ण;

काष्ठा atom_i2c_reg_info अणु
  uपूर्णांक8_t ucI2cRegIndex;
  uपूर्णांक8_t ucI2cRegVal;
पूर्ण;

काष्ठा atom_hdmi_reसमयr_redriver_set अणु
  uपूर्णांक8_t HdmiSlvAddr;
  uपूर्णांक8_t HdmiRegNum;
  uपूर्णांक8_t Hdmi6GRegNum;
  काष्ठा atom_i2c_reg_info HdmiRegSetting[9];        //For non 6G Hz use
  काष्ठा atom_i2c_reg_info Hdmi6GhzRegSetting[3];    //For 6G Hz use.
पूर्ण;

काष्ठा atom_पूर्णांकegrated_प्रणाली_info_v1_11
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक32_t  vbios_misc;                       //क्रमागत of atom_प्रणाली_vbiosmisc_def
  uपूर्णांक32_t  gpucapinfo;                       //क्रमागत of atom_प्रणाली_gpucapinf_def   
  uपूर्णांक32_t  प्रणाली_config;                    
  uपूर्णांक32_t  cpucapinfo;
  uपूर्णांक16_t  gpuclk_ss_percentage;             //unit of 0.001%,   1000 mean 1% 
  uपूर्णांक16_t  gpuclk_ss_type;
  uपूर्णांक16_t  lvds_ss_percentage;               //unit of 0.001%,   1000 mean 1%
  uपूर्णांक16_t  lvds_ss_rate_10hz;
  uपूर्णांक16_t  hdmi_ss_percentage;               //unit of 0.001%,   1000 mean 1%
  uपूर्णांक16_t  hdmi_ss_rate_10hz;
  uपूर्णांक16_t  dvi_ss_percentage;                //unit of 0.001%,   1000 mean 1%
  uपूर्णांक16_t  dvi_ss_rate_10hz;
  uपूर्णांक16_t  dpphy_override;                   // bit vector, क्रमागत of atom_sysinfo_dpphy_override_def
  uपूर्णांक16_t  lvds_misc;                        // क्रमागत of atom_sys_info_lvds_misc_def
  uपूर्णांक16_t  backlight_pwm_hz;                 // pwm frequency in hz
  uपूर्णांक8_t   memorytype;                       // क्रमागत of atom_dmi_t17_mem_type_def, APU memory type indication.
  uपूर्णांक8_t   umachannelnumber;                 // number of memory channels
  uपूर्णांक8_t   pwr_on_digon_to_de;               /* all pwr sequence numbers below are in uपूर्णांक of 4ms */
  uपूर्णांक8_t   pwr_on_de_to_vary_bl;
  uपूर्णांक8_t   pwr_करोwn_vary_bloff_to_de;
  uपूर्णांक8_t   pwr_करोwn_de_to_digoff;
  uपूर्णांक8_t   pwr_off_delay;
  uपूर्णांक8_t   pwr_on_vary_bl_to_blon;
  uपूर्णांक8_t   pwr_करोwn_bloff_to_vary_bloff;
  uपूर्णांक8_t   min_allowed_bl_level;
  uपूर्णांक8_t   htc_hyst_limit;
  uपूर्णांक8_t   htc_पंचांगp_limit;
  uपूर्णांक8_t   reserved1;
  uपूर्णांक8_t   reserved2;
  काष्ठा atom_बाह्यal_display_connection_info extdispconninfo;
  काष्ठा atom_14nm_dpphy_dvihdmi_tuningset dvi_tuningset;
  काष्ठा atom_14nm_dpphy_dvihdmi_tuningset hdmi_tuningset;
  काष्ठा atom_14nm_dpphy_dvihdmi_tuningset hdmi6g_tuningset;
  काष्ठा atom_14nm_dpphy_dp_tuningset dp_tuningset;        // rbr 1.62G dp tuning set
  काष्ठा atom_14nm_dpphy_dp_tuningset dp_hbr3_tuningset;   // HBR3 dp tuning set
  काष्ठा atom_camera_data  camera_info;
  काष्ठा atom_hdmi_reसमयr_redriver_set dp0_reसमयr_set;   //क्रम DP0
  काष्ठा atom_hdmi_reसमयr_redriver_set dp1_reसमयr_set;   //क्रम DP1
  काष्ठा atom_hdmi_reसमयr_redriver_set dp2_reसमयr_set;   //क्रम DP2
  काष्ठा atom_hdmi_reसमयr_redriver_set dp3_reसमयr_set;   //क्रम DP3
  काष्ठा atom_14nm_dpphy_dp_tuningset dp_hbr_tuningset;    //hbr 2.7G dp tuning set
  काष्ठा atom_14nm_dpphy_dp_tuningset dp_hbr2_tuningset;   //hbr2 5.4G dp turnig set
  काष्ठा atom_14nm_dpphy_dp_tuningset edp_tuningset;       //edp tuning set
  uपूर्णांक32_t  reserved[66];
पूर्ण;

काष्ठा atom_पूर्णांकegrated_प्रणाली_info_v1_12
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक32_t  vbios_misc;                       //क्रमागत of atom_प्रणाली_vbiosmisc_def
  uपूर्णांक32_t  gpucapinfo;                       //क्रमागत of atom_प्रणाली_gpucapinf_def   
  uपूर्णांक32_t  प्रणाली_config;                    
  uपूर्णांक32_t  cpucapinfo;
  uपूर्णांक16_t  gpuclk_ss_percentage;             //unit of 0.001%,   1000 mean 1% 
  uपूर्णांक16_t  gpuclk_ss_type;
  uपूर्णांक16_t  lvds_ss_percentage;               //unit of 0.001%,   1000 mean 1%
  uपूर्णांक16_t  lvds_ss_rate_10hz;
  uपूर्णांक16_t  hdmi_ss_percentage;               //unit of 0.001%,   1000 mean 1%
  uपूर्णांक16_t  hdmi_ss_rate_10hz;
  uपूर्णांक16_t  dvi_ss_percentage;                //unit of 0.001%,   1000 mean 1%
  uपूर्णांक16_t  dvi_ss_rate_10hz;
  uपूर्णांक16_t  dpphy_override;                   // bit vector, क्रमागत of atom_sysinfo_dpphy_override_def
  uपूर्णांक16_t  lvds_misc;                        // क्रमागत of atom_sys_info_lvds_misc_def
  uपूर्णांक16_t  backlight_pwm_hz;                 // pwm frequency in hz
  uपूर्णांक8_t   memorytype;                       // क्रमागत of atom_dmi_t17_mem_type_def, APU memory type indication.
  uपूर्णांक8_t   umachannelnumber;                 // number of memory channels
  uपूर्णांक8_t   pwr_on_digon_to_de;               // all pwr sequence numbers below are in uपूर्णांक of 4ms //
  uपूर्णांक8_t   pwr_on_de_to_vary_bl;
  uपूर्णांक8_t   pwr_करोwn_vary_bloff_to_de;
  uपूर्णांक8_t   pwr_करोwn_de_to_digoff;
  uपूर्णांक8_t   pwr_off_delay;
  uपूर्णांक8_t   pwr_on_vary_bl_to_blon;
  uपूर्णांक8_t   pwr_करोwn_bloff_to_vary_bloff;
  uपूर्णांक8_t   min_allowed_bl_level;
  uपूर्णांक8_t   htc_hyst_limit;
  uपूर्णांक8_t   htc_पंचांगp_limit;
  uपूर्णांक8_t   reserved1;
  uपूर्णांक8_t   reserved2;
  काष्ठा atom_बाह्यal_display_connection_info extdispconninfo;
  काष्ठा atom_DCN_dpphy_dvihdmi_tuningset  TMDS_tuningset;
  काष्ठा atom_DCN_dpphy_dvihdmi_tuningset  hdmiCLK5_tuningset;
  काष्ठा atom_DCN_dpphy_dvihdmi_tuningset  hdmiCLK8_tuningset;
  काष्ठा atom_DCN_dpphy_dp_tuningset rbr_tuningset;        // rbr 1.62G dp tuning set
  काष्ठा atom_DCN_dpphy_dp_tuningset hbr3_tuningset;   // HBR3 dp tuning set  
  काष्ठा atom_camera_data  camera_info;
  काष्ठा atom_hdmi_reसमयr_redriver_set dp0_reसमयr_set;   //क्रम DP0
  काष्ठा atom_hdmi_reसमयr_redriver_set dp1_reसमयr_set;   //क्रम DP1
  काष्ठा atom_hdmi_reसमयr_redriver_set dp2_reसमयr_set;   //क्रम DP2
  काष्ठा atom_hdmi_reसमयr_redriver_set dp3_reसमयr_set;   //क्रम DP3
  काष्ठा atom_DCN_dpphy_dp_tuningset hbr_tuningset;    //hbr 2.7G dp tuning set
  काष्ठा atom_DCN_dpphy_dp_tuningset hbr2_tuningset;   //hbr2 5.4G dp turnig set
  काष्ठा atom_DCN_dpphy_dp_tuningset edp_tunings;       //edp tuning set
  काष्ठा atom_DCN_dpphy_dvihdmi_tuningset  hdmiCLK6_tuningset;
  uपूर्णांक32_t  reserved[63];
पूर्ण;

काष्ठा edp_info_table
अणु
        uपूर्णांक16_t edp_backlight_pwm_hz;
        uपूर्णांक16_t edp_ss_percentage;
        uपूर्णांक16_t edp_ss_rate_10hz;
        uपूर्णांक16_t reserved1;
        uपूर्णांक32_t reserved2;
        uपूर्णांक8_t  edp_pwr_on_off_delay;
        uपूर्णांक8_t  edp_pwr_on_vary_bl_to_blon;
        uपूर्णांक8_t  edp_pwr_करोwn_bloff_to_vary_bloff;
        uपूर्णांक8_t  edp_panel_bpc;
        uपूर्णांक8_t  edp_bootup_bl_level;
        uपूर्णांक8_t  reserved3[3];
        uपूर्णांक32_t reserved4[3];
पूर्ण;

काष्ठा atom_पूर्णांकegrated_प्रणाली_info_v2_1
अणु
        काष्ठा  atom_common_table_header  table_header;
        uपूर्णांक32_t  vbios_misc;                       //क्रमागत of atom_प्रणाली_vbiosmisc_def
        uपूर्णांक32_t  gpucapinfo;                       //क्रमागत of atom_प्रणाली_gpucapinf_def
        uपूर्णांक32_t  प्रणाली_config;
        uपूर्णांक32_t  cpucapinfo;
        uपूर्णांक16_t  gpuclk_ss_percentage;             //unit of 0.001%,   1000 mean 1%
        uपूर्णांक16_t  gpuclk_ss_type;
        uपूर्णांक16_t  dpphy_override;                   // bit vector, क्रमागत of atom_sysinfo_dpphy_override_def
        uपूर्णांक8_t   memorytype;                       // क्रमागत of atom_dmi_t17_mem_type_def, APU memory type indication.
        uपूर्णांक8_t   umachannelnumber;                 // number of memory channels
        uपूर्णांक8_t   htc_hyst_limit;
        uपूर्णांक8_t   htc_पंचांगp_limit;
        uपूर्णांक8_t   reserved1;
        uपूर्णांक8_t   reserved2;
        काष्ठा edp_info_table edp1_info;
        काष्ठा edp_info_table edp2_info;
        uपूर्णांक32_t  reserved3[8];
        काष्ठा atom_बाह्यal_display_connection_info extdispconninfo;
        काष्ठा atom_DCN_dpphy_dvihdmi_tuningset  TMDS_tuningset;
        काष्ठा atom_DCN_dpphy_dvihdmi_tuningset  hdmiCLK5_tuningset; //add clk6
        काष्ठा atom_DCN_dpphy_dvihdmi_tuningset  hdmiCLK6_tuningset;
        काष्ठा atom_DCN_dpphy_dvihdmi_tuningset  hdmiCLK8_tuningset;
        uपूर्णांक32_t reserved4[6];//reserve 2*माप(atom_DCN_dpphy_dvihdmi_tuningset)
        काष्ठा atom_DCN_dpphy_dp_tuningset rbr_tuningset;        // rbr 1.62G dp tuning set
        काष्ठा atom_DCN_dpphy_dp_tuningset hbr_tuningset;    //hbr 2.7G dp tuning set
        काष्ठा atom_DCN_dpphy_dp_tuningset hbr2_tuningset;   //hbr2 5.4G dp turnig set
        काष्ठा atom_DCN_dpphy_dp_tuningset hbr3_tuningset;   // HBR3 dp tuning set
        काष्ठा atom_DCN_dpphy_dp_tuningset edp_tunings;       //edp tuning set
        uपूर्णांक32_t reserved5[28];//reserve 2*माप(atom_DCN_dpphy_dp_tuningset)
        काष्ठा atom_hdmi_reसमयr_redriver_set dp0_reसमयr_set;   //क्रम DP0
        काष्ठा atom_hdmi_reसमयr_redriver_set dp1_reसमयr_set;   //क्रम DP1
        काष्ठा atom_hdmi_reसमयr_redriver_set dp2_reसमयr_set;   //क्रम DP2
        काष्ठा atom_hdmi_reसमयr_redriver_set dp3_reसमयr_set;   //क्रम DP3
        uपूर्णांक32_t reserved6[30];// reserve size of(atom_camera_data) क्रम camera_info
        uपूर्णांक32_t reserved7[32];

पूर्ण;

// प्रणाली_config
क्रमागत atom_प्रणाली_vbiosmisc_defअणु
  INTEGRATED_SYSTEM_INFO__GET_EDID_CALLBACK_FUNC_SUPPORT = 0x01,
पूर्ण;


// gpucapinfo
क्रमागत atom_प्रणाली_gpucapinf_defअणु
  SYS_INFO_GPUCAPS__ENABEL_DFS_BYPASS  = 0x10,
पूर्ण;

//dpphy_override
क्रमागत atom_sysinfo_dpphy_override_defअणु
  ATOM_ENABLE_DVI_TUNINGSET   = 0x01,
  ATOM_ENABLE_HDMI_TUNINGSET  = 0x02,
  ATOM_ENABLE_HDMI6G_TUNINGSET  = 0x04,
  ATOM_ENABLE_DP_TUNINGSET  = 0x08,
  ATOM_ENABLE_DP_HBR3_TUNINGSET  = 0x10,  
पूर्ण;

//lvds_misc
क्रमागत atom_sys_info_lvds_misc_def
अणु
  SYS_INFO_LVDS_MISC_888_FPDI_MODE                 =0x01,
  SYS_INFO_LVDS_MISC_888_BPC_MODE                  =0x04,
  SYS_INFO_LVDS_MISC_OVERRIDE_EN                   =0x08,
पूर्ण;


//memorytype  DMI Type 17 offset 12h - Memory Type
क्रमागत atom_dmi_t17_mem_type_defअणु
  OtherMemType = 0x01,                                  ///< Assign 01 to Other
  UnknownMemType,                                       ///< Assign 02 to Unknown
  DramMemType,                                          ///< Assign 03 to DRAM
  EdramMemType,                                         ///< Assign 04 to EDRAM
  VramMemType,                                          ///< Assign 05 to VRAM
  SramMemType,                                          ///< Assign 06 to SRAM
  RamMemType,                                           ///< Assign 07 to RAM
  RomMemType,                                           ///< Assign 08 to ROM
  FlashMemType,                                         ///< Assign 09 to Flash
  EepromMemType,                                        ///< Assign 10 to EEPROM
  FepromMemType,                                        ///< Assign 11 to FEPROM
  EpromMemType,                                         ///< Assign 12 to EPROM
  CdramMemType,                                         ///< Assign 13 to CDRAM
  ThreeDramMemType,                                     ///< Assign 14 to 3DRAM
  SdramMemType,                                         ///< Assign 15 to SDRAM
  SgramMemType,                                         ///< Assign 16 to SGRAM
  RdramMemType,                                         ///< Assign 17 to RDRAM
  DdrMemType,                                           ///< Assign 18 to DDR
  Ddr2MemType,                                          ///< Assign 19 to DDR2
  Ddr2FbdimmMemType,                                    ///< Assign 20 to DDR2 FB-DIMM
  Ddr3MemType = 0x18,                                   ///< Assign 24 to DDR3
  Fbd2MemType,                                          ///< Assign 25 to FBD2
  Ddr4MemType,                                          ///< Assign 26 to DDR4
  LpDdrMemType,                                         ///< Assign 27 to LPDDR
  LpDdr2MemType,                                        ///< Assign 28 to LPDDR2
  LpDdr3MemType,                                        ///< Assign 29 to LPDDR3
  LpDdr4MemType,                                        ///< Assign 30 to LPDDR4
  GDdr6MemType,                                         ///< Assign 31 to GDDR6
  HbmMemType,                                           ///< Assign 32 to HBM
  Hbm2MemType,                                          ///< Assign 33 to HBM2
  Ddr5MemType,                                          ///< Assign 34 to DDR5
  LpDdr5MemType,                                        ///< Assign 35 to LPDDR5
पूर्ण;


// this Table is used starting from NL/AM, used by SBIOS and pass the IntegratedSystemInfoTable/PowerPlayInfoTable/SystemCameraInfoTable 
काष्ठा atom_fusion_प्रणाली_info_v4
अणु
  काष्ठा atom_पूर्णांकegrated_प्रणाली_info_v1_11   sysinfo;           // refer to ATOM_INTEGRATED_SYSTEM_INFO_V1_8 definition
  uपूर्णांक32_t   घातerplayinfo[256];                                // Reserve 1024 bytes space क्रम PowerPlayInfoTable
पूर्ण; 


/* 
  ***************************************************************************
    Data Table gfx_info  काष्ठाure
  ***************************************************************************
*/

काष्ठा  atom_gfx_info_v2_2
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक8_t gfxip_min_ver;
  uपूर्णांक8_t gfxip_max_ver;
  uपूर्णांक8_t max_shader_engines;
  uपूर्णांक8_t max_tile_pipes;
  uपूर्णांक8_t max_cu_per_sh;
  uपूर्णांक8_t max_sh_per_se;
  uपूर्णांक8_t max_backends_per_se;
  uपूर्णांक8_t max_texture_channel_caches;
  uपूर्णांक32_t regaddr_cp_dma_src_addr;
  uपूर्णांक32_t regaddr_cp_dma_src_addr_hi;
  uपूर्णांक32_t regaddr_cp_dma_dst_addr;
  uपूर्णांक32_t regaddr_cp_dma_dst_addr_hi;
  uपूर्णांक32_t regaddr_cp_dma_command; 
  uपूर्णांक32_t regaddr_cp_status;
  uपूर्णांक32_t regaddr_rlc_gpu_घड़ी_32;
  uपूर्णांक32_t rlc_gpu_समयr_refclk; 
पूर्ण;

काष्ठा  atom_gfx_info_v2_3 अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक8_t gfxip_min_ver;
  uपूर्णांक8_t gfxip_max_ver;
  uपूर्णांक8_t max_shader_engines;
  uपूर्णांक8_t max_tile_pipes;
  uपूर्णांक8_t max_cu_per_sh;
  uपूर्णांक8_t max_sh_per_se;
  uपूर्णांक8_t max_backends_per_se;
  uपूर्णांक8_t max_texture_channel_caches;
  uपूर्णांक32_t regaddr_cp_dma_src_addr;
  uपूर्णांक32_t regaddr_cp_dma_src_addr_hi;
  uपूर्णांक32_t regaddr_cp_dma_dst_addr;
  uपूर्णांक32_t regaddr_cp_dma_dst_addr_hi;
  uपूर्णांक32_t regaddr_cp_dma_command;
  uपूर्णांक32_t regaddr_cp_status;
  uपूर्णांक32_t regaddr_rlc_gpu_घड़ी_32;
  uपूर्णांक32_t rlc_gpu_समयr_refclk;
  uपूर्णांक8_t active_cu_per_sh;
  uपूर्णांक8_t active_rb_per_se;
  uपूर्णांक16_t gcgoldenoffset;
  uपूर्णांक32_t rm21_sram_vmin_value;
पूर्ण;

काष्ठा  atom_gfx_info_v2_4
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक8_t gfxip_min_ver;
  uपूर्णांक8_t gfxip_max_ver;
  uपूर्णांक8_t max_shader_engines;
  uपूर्णांक8_t reserved;
  uपूर्णांक8_t max_cu_per_sh;
  uपूर्णांक8_t max_sh_per_se;
  uपूर्णांक8_t max_backends_per_se;
  uपूर्णांक8_t max_texture_channel_caches;
  uपूर्णांक32_t regaddr_cp_dma_src_addr;
  uपूर्णांक32_t regaddr_cp_dma_src_addr_hi;
  uपूर्णांक32_t regaddr_cp_dma_dst_addr;
  uपूर्णांक32_t regaddr_cp_dma_dst_addr_hi;
  uपूर्णांक32_t regaddr_cp_dma_command;
  uपूर्णांक32_t regaddr_cp_status;
  uपूर्णांक32_t regaddr_rlc_gpu_घड़ी_32;
  uपूर्णांक32_t rlc_gpu_समयr_refclk;
  uपूर्णांक8_t active_cu_per_sh;
  uपूर्णांक8_t active_rb_per_se;
  uपूर्णांक16_t gcgoldenoffset;
  uपूर्णांक16_t gc_num_gprs;
  uपूर्णांक16_t gc_gsprim_buff_depth;
  uपूर्णांक16_t gc_parameter_cache_depth;
  uपूर्णांक16_t gc_wave_size;
  uपूर्णांक16_t gc_max_waves_per_simd;
  uपूर्णांक16_t gc_lds_size;
  uपूर्णांक8_t gc_num_max_gs_thds;
  uपूर्णांक8_t gc_gs_table_depth;
  uपूर्णांक8_t gc_द्विगुन_offchip_lds_buffer;
  uपूर्णांक8_t gc_max_scratch_slots_per_cu;
  uपूर्णांक32_t sram_rm_fuses_val;
  uपूर्णांक32_t sram_custom_rm_fuses_val;
पूर्ण;

काष्ठा atom_gfx_info_v2_7 अणु
	काष्ठा atom_common_table_header table_header;
	uपूर्णांक8_t gfxip_min_ver;
	uपूर्णांक8_t gfxip_max_ver;
	uपूर्णांक8_t max_shader_engines;
	uपूर्णांक8_t reserved;
	uपूर्णांक8_t max_cu_per_sh;
	uपूर्णांक8_t max_sh_per_se;
	uपूर्णांक8_t max_backends_per_se;
	uपूर्णांक8_t max_texture_channel_caches;
	uपूर्णांक32_t regaddr_cp_dma_src_addr;
	uपूर्णांक32_t regaddr_cp_dma_src_addr_hi;
	uपूर्णांक32_t regaddr_cp_dma_dst_addr;
	uपूर्णांक32_t regaddr_cp_dma_dst_addr_hi;
	uपूर्णांक32_t regaddr_cp_dma_command;
	uपूर्णांक32_t regaddr_cp_status;
	uपूर्णांक32_t regaddr_rlc_gpu_घड़ी_32;
	uपूर्णांक32_t rlc_gpu_समयr_refclk;
	uपूर्णांक8_t active_cu_per_sh;
	uपूर्णांक8_t active_rb_per_se;
	uपूर्णांक16_t gcgoldenoffset;
	uपूर्णांक16_t gc_num_gprs;
	uपूर्णांक16_t gc_gsprim_buff_depth;
	uपूर्णांक16_t gc_parameter_cache_depth;
	uपूर्णांक16_t gc_wave_size;
	uपूर्णांक16_t gc_max_waves_per_simd;
	uपूर्णांक16_t gc_lds_size;
	uपूर्णांक8_t gc_num_max_gs_thds;
	uपूर्णांक8_t gc_gs_table_depth;
	uपूर्णांक8_t gc_द्विगुन_offchip_lds_buffer;
	uपूर्णांक8_t gc_max_scratch_slots_per_cu;
	uपूर्णांक32_t sram_rm_fuses_val;
	uपूर्णांक32_t sram_custom_rm_fuses_val;
	uपूर्णांक8_t cut_cu;
	uपूर्णांक8_t active_cu_total;
	uपूर्णांक8_t cu_reserved[2];
	uपूर्णांक32_t gc_config;
	uपूर्णांक8_t inactive_cu_per_se[8];
	uपूर्णांक32_t reserved2[6];
पूर्ण;

/* 
  ***************************************************************************
    Data Table smu_info  काष्ठाure
  ***************************************************************************
*/
काष्ठा atom_smu_info_v3_1
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक8_t smuip_min_ver;
  uपूर्णांक8_t smuip_max_ver;
  uपूर्णांक8_t smu_rsd1;
  uपूर्णांक8_t gpuclk_ss_mode;           // क्रमागत of atom_spपढ़ो_spectrum_mode
  uपूर्णांक16_t sclk_ss_percentage;
  uपूर्णांक16_t sclk_ss_rate_10hz;
  uपूर्णांक16_t gpuclk_ss_percentage;    // in unit of 0.001%
  uपूर्णांक16_t gpuclk_ss_rate_10hz;
  uपूर्णांक32_t core_refclk_10khz;
  uपूर्णांक8_t  ac_dc_gpio_bit;          // GPIO bit shअगरt in SMU_GPIOPAD_A  configured क्रम AC/DC चयनing, =0xff means invalid
  uपूर्णांक8_t  ac_dc_polarity;          // GPIO polarity क्रम AC/DC चयनing
  uपूर्णांक8_t  vr0hot_gpio_bit;         // GPIO bit shअगरt in SMU_GPIOPAD_A  configured क्रम VR0 HOT event, =0xff means invalid
  uपूर्णांक8_t  vr0hot_polarity;         // GPIO polarity क्रम VR0 HOT event
  uपूर्णांक8_t  vr1hot_gpio_bit;         // GPIO bit shअगरt in SMU_GPIOPAD_A configured क्रम VR1 HOT event , =0xff means invalid
  uपूर्णांक8_t  vr1hot_polarity;         // GPIO polarity क्रम VR1 HOT event 
  uपूर्णांक8_t  fw_ctf_gpio_bit;         // GPIO bit shअगरt in SMU_GPIOPAD_A configured क्रम CTF, =0xff means invalid
  uपूर्णांक8_t  fw_ctf_polarity;         // GPIO polarity क्रम CTF
पूर्ण;

काष्ठा atom_smu_info_v3_2 अणु
  काष्ठा   atom_common_table_header  table_header;
  uपूर्णांक8_t  smuip_min_ver;
  uपूर्णांक8_t  smuip_max_ver;
  uपूर्णांक8_t  smu_rsd1;
  uपूर्णांक8_t  gpuclk_ss_mode;
  uपूर्णांक16_t sclk_ss_percentage;
  uपूर्णांक16_t sclk_ss_rate_10hz;
  uपूर्णांक16_t gpuclk_ss_percentage;    // in unit of 0.001%
  uपूर्णांक16_t gpuclk_ss_rate_10hz;
  uपूर्णांक32_t core_refclk_10khz;
  uपूर्णांक8_t  ac_dc_gpio_bit;          // GPIO bit shअगरt in SMU_GPIOPAD_A  configured क्रम AC/DC चयनing, =0xff means invalid
  uपूर्णांक8_t  ac_dc_polarity;          // GPIO polarity क्रम AC/DC चयनing
  uपूर्णांक8_t  vr0hot_gpio_bit;         // GPIO bit shअगरt in SMU_GPIOPAD_A  configured क्रम VR0 HOT event, =0xff means invalid
  uपूर्णांक8_t  vr0hot_polarity;         // GPIO polarity क्रम VR0 HOT event
  uपूर्णांक8_t  vr1hot_gpio_bit;         // GPIO bit shअगरt in SMU_GPIOPAD_A configured क्रम VR1 HOT event , =0xff means invalid
  uपूर्णांक8_t  vr1hot_polarity;         // GPIO polarity क्रम VR1 HOT event
  uपूर्णांक8_t  fw_ctf_gpio_bit;         // GPIO bit shअगरt in SMU_GPIOPAD_A configured क्रम CTF, =0xff means invalid
  uपूर्णांक8_t  fw_ctf_polarity;         // GPIO polarity क्रम CTF
  uपूर्णांक8_t  pcc_gpio_bit;            // GPIO bit shअगरt in SMU_GPIOPAD_A configured क्रम PCC, =0xff means invalid
  uपूर्णांक8_t  pcc_gpio_polarity;       // GPIO polarity क्रम CTF
  uपूर्णांक16_t smugoldenoffset;
  uपूर्णांक32_t gpupll_vco_freq_10khz;
  uपूर्णांक32_t bootup_smnclk_10khz;
  uपूर्णांक32_t bootup_socclk_10khz;
  uपूर्णांक32_t bootup_mp0clk_10khz;
  uपूर्णांक32_t bootup_mp1clk_10khz;
  uपूर्णांक32_t bootup_lclk_10khz;
  uपूर्णांक32_t bootup_dcefclk_10khz;
  uपूर्णांक32_t ctf_threshold_override_value;
  uपूर्णांक32_t reserved[5];
पूर्ण;

काष्ठा atom_smu_info_v3_3 अणु
  काष्ठा   atom_common_table_header  table_header;
  uपूर्णांक8_t  smuip_min_ver;
  uपूर्णांक8_t  smuip_max_ver;
  uपूर्णांक8_t  waflclk_ss_mode;
  uपूर्णांक8_t  gpuclk_ss_mode;
  uपूर्णांक16_t sclk_ss_percentage;
  uपूर्णांक16_t sclk_ss_rate_10hz;
  uपूर्णांक16_t gpuclk_ss_percentage;    // in unit of 0.001%
  uपूर्णांक16_t gpuclk_ss_rate_10hz;
  uपूर्णांक32_t core_refclk_10khz;
  uपूर्णांक8_t  ac_dc_gpio_bit;          // GPIO bit shअगरt in SMU_GPIOPAD_A  configured क्रम AC/DC चयनing, =0xff means invalid
  uपूर्णांक8_t  ac_dc_polarity;          // GPIO polarity क्रम AC/DC चयनing
  uपूर्णांक8_t  vr0hot_gpio_bit;         // GPIO bit shअगरt in SMU_GPIOPAD_A  configured क्रम VR0 HOT event, =0xff means invalid
  uपूर्णांक8_t  vr0hot_polarity;         // GPIO polarity क्रम VR0 HOT event
  uपूर्णांक8_t  vr1hot_gpio_bit;         // GPIO bit shअगरt in SMU_GPIOPAD_A configured क्रम VR1 HOT event , =0xff means invalid
  uपूर्णांक8_t  vr1hot_polarity;         // GPIO polarity क्रम VR1 HOT event
  uपूर्णांक8_t  fw_ctf_gpio_bit;         // GPIO bit shअगरt in SMU_GPIOPAD_A configured क्रम CTF, =0xff means invalid
  uपूर्णांक8_t  fw_ctf_polarity;         // GPIO polarity क्रम CTF
  uपूर्णांक8_t  pcc_gpio_bit;            // GPIO bit shअगरt in SMU_GPIOPAD_A configured क्रम PCC, =0xff means invalid
  uपूर्णांक8_t  pcc_gpio_polarity;       // GPIO polarity क्रम CTF
  uपूर्णांक16_t smugoldenoffset;
  uपूर्णांक32_t gpupll_vco_freq_10khz;
  uपूर्णांक32_t bootup_smnclk_10khz;
  uपूर्णांक32_t bootup_socclk_10khz;
  uपूर्णांक32_t bootup_mp0clk_10khz;
  uपूर्णांक32_t bootup_mp1clk_10khz;
  uपूर्णांक32_t bootup_lclk_10khz;
  uपूर्णांक32_t bootup_dcefclk_10khz;
  uपूर्णांक32_t ctf_threshold_override_value;
  uपूर्णांक32_t syspll3_0_vco_freq_10khz;
  uपूर्णांक32_t syspll3_1_vco_freq_10khz;
  uपूर्णांक32_t bootup_fclk_10khz;
  uपूर्णांक32_t bootup_waflclk_10khz;
  uपूर्णांक32_t smu_info_caps;
  uपूर्णांक16_t waflclk_ss_percentage;    // in unit of 0.001%
  uपूर्णांक16_t smuinitoffset;
  uपूर्णांक32_t reserved;
पूर्ण;

/*
 ***************************************************************************
   Data Table smc_dpm_info  काष्ठाure
 ***************************************************************************
 */
काष्ठा atom_smc_dpm_info_v4_1
अणु
  काष्ठा   atom_common_table_header  table_header;
  uपूर्णांक8_t  liquid1_i2c_address;
  uपूर्णांक8_t  liquid2_i2c_address;
  uपूर्णांक8_t  vr_i2c_address;
  uपूर्णांक8_t  plx_i2c_address;

  uपूर्णांक8_t  liquid_i2c_linescl;
  uपूर्णांक8_t  liquid_i2c_linesda;
  uपूर्णांक8_t  vr_i2c_linescl;
  uपूर्णांक8_t  vr_i2c_linesda;

  uपूर्णांक8_t  plx_i2c_linescl;
  uपूर्णांक8_t  plx_i2c_linesda;
  uपूर्णांक8_t  vrsensorpresent;
  uपूर्णांक8_t  liquidsensorpresent;

  uपूर्णांक16_t maxvoltagestepgfx;
  uपूर्णांक16_t maxvoltagestepsoc;

  uपूर्णांक8_t  vddgfxvrmapping;
  uपूर्णांक8_t  vddsocvrmapping;
  uपूर्णांक8_t  vddmem0vrmapping;
  uपूर्णांक8_t  vddmem1vrmapping;

  uपूर्णांक8_t  gfxulvphasesheddingmask;
  uपूर्णांक8_t  soculvphasesheddingmask;
  uपूर्णांक8_t  padding8_v[2];

  uपूर्णांक16_t gfxmaxcurrent;
  uपूर्णांक8_t  gfxoffset;
  uपूर्णांक8_t  padding_telemetrygfx;

  uपूर्णांक16_t socmaxcurrent;
  uपूर्णांक8_t  socoffset;
  uपूर्णांक8_t  padding_telemetrysoc;

  uपूर्णांक16_t mem0maxcurrent;
  uपूर्णांक8_t  mem0offset;
  uपूर्णांक8_t  padding_telemetrymem0;

  uपूर्णांक16_t mem1maxcurrent;
  uपूर्णांक8_t  mem1offset;
  uपूर्णांक8_t  padding_telemetrymem1;

  uपूर्णांक8_t  acdcgpio;
  uपूर्णांक8_t  acdcpolarity;
  uपूर्णांक8_t  vr0hotgpio;
  uपूर्णांक8_t  vr0hotpolarity;

  uपूर्णांक8_t  vr1hotgpio;
  uपूर्णांक8_t  vr1hotpolarity;
  uपूर्णांक8_t  padding1;
  uपूर्णांक8_t  padding2;

  uपूर्णांक8_t  ledpin0;
  uपूर्णांक8_t  ledpin1;
  uपूर्णांक8_t  ledpin2;
  uपूर्णांक8_t  padding8_4;

	uपूर्णांक8_t  pllgfxclkspपढ़ोenabled;
	uपूर्णांक8_t  pllgfxclkspपढ़ोpercent;
	uपूर्णांक16_t pllgfxclkspपढ़ोfreq;

  uपूर्णांक8_t uclkspपढ़ोenabled;
  uपूर्णांक8_t uclkspपढ़ोpercent;
  uपूर्णांक16_t uclkspपढ़ोfreq;

  uपूर्णांक8_t socclkspपढ़ोenabled;
  uपूर्णांक8_t socclkspपढ़ोpercent;
  uपूर्णांक16_t socclkspपढ़ोfreq;

	uपूर्णांक8_t  acggfxclkspपढ़ोenabled;
	uपूर्णांक8_t  acggfxclkspपढ़ोpercent;
	uपूर्णांक16_t acggfxclkspपढ़ोfreq;

	uपूर्णांक8_t Vr2_I2C_address;
	uपूर्णांक8_t padding_vr2[3];

	uपूर्णांक32_t boardreserved[9];
पूर्ण;

/*
 ***************************************************************************
   Data Table smc_dpm_info  काष्ठाure
 ***************************************************************************
 */
काष्ठा atom_smc_dpm_info_v4_3
अणु
  काष्ठा   atom_common_table_header  table_header;
  uपूर्णांक8_t  liquid1_i2c_address;
  uपूर्णांक8_t  liquid2_i2c_address;
  uपूर्णांक8_t  vr_i2c_address;
  uपूर्णांक8_t  plx_i2c_address;

  uपूर्णांक8_t  liquid_i2c_linescl;
  uपूर्णांक8_t  liquid_i2c_linesda;
  uपूर्णांक8_t  vr_i2c_linescl;
  uपूर्णांक8_t  vr_i2c_linesda;

  uपूर्णांक8_t  plx_i2c_linescl;
  uपूर्णांक8_t  plx_i2c_linesda;
  uपूर्णांक8_t  vrsensorpresent;
  uपूर्णांक8_t  liquidsensorpresent;

  uपूर्णांक16_t maxvoltagestepgfx;
  uपूर्णांक16_t maxvoltagestepsoc;

  uपूर्णांक8_t  vddgfxvrmapping;
  uपूर्णांक8_t  vddsocvrmapping;
  uपूर्णांक8_t  vddmem0vrmapping;
  uपूर्णांक8_t  vddmem1vrmapping;

  uपूर्णांक8_t  gfxulvphasesheddingmask;
  uपूर्णांक8_t  soculvphasesheddingmask;
  uपूर्णांक8_t  बाह्यalsensorpresent;
  uपूर्णांक8_t  padding8_v;

  uपूर्णांक16_t gfxmaxcurrent;
  uपूर्णांक8_t  gfxoffset;
  uपूर्णांक8_t  padding_telemetrygfx;

  uपूर्णांक16_t socmaxcurrent;
  uपूर्णांक8_t  socoffset;
  uपूर्णांक8_t  padding_telemetrysoc;

  uपूर्णांक16_t mem0maxcurrent;
  uपूर्णांक8_t  mem0offset;
  uपूर्णांक8_t  padding_telemetrymem0;

  uपूर्णांक16_t mem1maxcurrent;
  uपूर्णांक8_t  mem1offset;
  uपूर्णांक8_t  padding_telemetrymem1;

  uपूर्णांक8_t  acdcgpio;
  uपूर्णांक8_t  acdcpolarity;
  uपूर्णांक8_t  vr0hotgpio;
  uपूर्णांक8_t  vr0hotpolarity;

  uपूर्णांक8_t  vr1hotgpio;
  uपूर्णांक8_t  vr1hotpolarity;
  uपूर्णांक8_t  padding1;
  uपूर्णांक8_t  padding2;

  uपूर्णांक8_t  ledpin0;
  uपूर्णांक8_t  ledpin1;
  uपूर्णांक8_t  ledpin2;
  uपूर्णांक8_t  padding8_4;

  uपूर्णांक8_t  pllgfxclkspपढ़ोenabled;
  uपूर्णांक8_t  pllgfxclkspपढ़ोpercent;
  uपूर्णांक16_t pllgfxclkspपढ़ोfreq;

  uपूर्णांक8_t uclkspपढ़ोenabled;
  uपूर्णांक8_t uclkspपढ़ोpercent;
  uपूर्णांक16_t uclkspपढ़ोfreq;

  uपूर्णांक8_t fclkspपढ़ोenabled;
  uपूर्णांक8_t fclkspपढ़ोpercent;
  uपूर्णांक16_t fclkspपढ़ोfreq;

  uपूर्णांक8_t fllgfxclkspपढ़ोenabled;
  uपूर्णांक8_t fllgfxclkspपढ़ोpercent;
  uपूर्णांक16_t fllgfxclkspपढ़ोfreq;

  uपूर्णांक32_t boardreserved[10];
पूर्ण;

काष्ठा smudpm_i2ccontrollerconfig_t अणु
  uपूर्णांक32_t  enabled;
  uपूर्णांक32_t  slaveaddress;
  uपूर्णांक32_t  controllerport;
  uपूर्णांक32_t  controllername;
  uपूर्णांक32_t  thermalthrottler;
  uपूर्णांक32_t  i2cprotocol;
  uपूर्णांक32_t  i2cspeed;
पूर्ण;

काष्ठा atom_smc_dpm_info_v4_4
अणु
  काष्ठा   atom_common_table_header  table_header;
  uपूर्णांक32_t  i2c_padding[3];

  uपूर्णांक16_t maxvoltagestepgfx;
  uपूर्णांक16_t maxvoltagestepsoc;

  uपूर्णांक8_t  vddgfxvrmapping;
  uपूर्णांक8_t  vddsocvrmapping;
  uपूर्णांक8_t  vddmem0vrmapping;
  uपूर्णांक8_t  vddmem1vrmapping;

  uपूर्णांक8_t  gfxulvphasesheddingmask;
  uपूर्णांक8_t  soculvphasesheddingmask;
  uपूर्णांक8_t  बाह्यalsensorpresent;
  uपूर्णांक8_t  padding8_v;

  uपूर्णांक16_t gfxmaxcurrent;
  uपूर्णांक8_t  gfxoffset;
  uपूर्णांक8_t  padding_telemetrygfx;

  uपूर्णांक16_t socmaxcurrent;
  uपूर्णांक8_t  socoffset;
  uपूर्णांक8_t  padding_telemetrysoc;

  uपूर्णांक16_t mem0maxcurrent;
  uपूर्णांक8_t  mem0offset;
  uपूर्णांक8_t  padding_telemetrymem0;

  uपूर्णांक16_t mem1maxcurrent;
  uपूर्णांक8_t  mem1offset;
  uपूर्णांक8_t  padding_telemetrymem1;


  uपूर्णांक8_t  acdcgpio;
  uपूर्णांक8_t  acdcpolarity;
  uपूर्णांक8_t  vr0hotgpio;
  uपूर्णांक8_t  vr0hotpolarity;

  uपूर्णांक8_t  vr1hotgpio;
  uपूर्णांक8_t  vr1hotpolarity;
  uपूर्णांक8_t  padding1;
  uपूर्णांक8_t  padding2;


  uपूर्णांक8_t  ledpin0;
  uपूर्णांक8_t  ledpin1;
  uपूर्णांक8_t  ledpin2;
  uपूर्णांक8_t  padding8_4;


  uपूर्णांक8_t  pllgfxclkspपढ़ोenabled;
  uपूर्णांक8_t  pllgfxclkspपढ़ोpercent;
  uपूर्णांक16_t pllgfxclkspपढ़ोfreq;


  uपूर्णांक8_t  uclkspपढ़ोenabled;
  uपूर्णांक8_t  uclkspपढ़ोpercent;
  uपूर्णांक16_t uclkspपढ़ोfreq;


  uपूर्णांक8_t  fclkspपढ़ोenabled;
  uपूर्णांक8_t  fclkspपढ़ोpercent;
  uपूर्णांक16_t fclkspपढ़ोfreq;


  uपूर्णांक8_t  fllgfxclkspपढ़ोenabled;
  uपूर्णांक8_t  fllgfxclkspपढ़ोpercent;
  uपूर्णांक16_t fllgfxclkspपढ़ोfreq;


  काष्ठा smudpm_i2ccontrollerconfig_t  i2ccontrollers[7];


  uपूर्णांक32_t boardreserved[10];
पूर्ण;

क्रमागत smudpm_v4_5_i2ccontrollername_eअणु
    SMC_V4_5_I2C_CONTROLLER_NAME_VR_GFX = 0,
    SMC_V4_5_I2C_CONTROLLER_NAME_VR_SOC,
    SMC_V4_5_I2C_CONTROLLER_NAME_VR_VDDCI,
    SMC_V4_5_I2C_CONTROLLER_NAME_VR_MVDD,
    SMC_V4_5_I2C_CONTROLLER_NAME_LIQUID0,
    SMC_V4_5_I2C_CONTROLLER_NAME_LIQUID1,
    SMC_V4_5_I2C_CONTROLLER_NAME_PLX,
    SMC_V4_5_I2C_CONTROLLER_NAME_SPARE,
    SMC_V4_5_I2C_CONTROLLER_NAME_COUNT,
पूर्ण;

क्रमागत smudpm_v4_5_i2ccontrollerthrottler_eअणु
    SMC_V4_5_I2C_CONTROLLER_THROTTLER_TYPE_NONE = 0,
    SMC_V4_5_I2C_CONTROLLER_THROTTLER_VR_GFX,
    SMC_V4_5_I2C_CONTROLLER_THROTTLER_VR_SOC,
    SMC_V4_5_I2C_CONTROLLER_THROTTLER_VR_VDDCI,
    SMC_V4_5_I2C_CONTROLLER_THROTTLER_VR_MVDD,
    SMC_V4_5_I2C_CONTROLLER_THROTTLER_LIQUID0,
    SMC_V4_5_I2C_CONTROLLER_THROTTLER_LIQUID1,
    SMC_V4_5_I2C_CONTROLLER_THROTTLER_PLX,
    SMC_V4_5_I2C_CONTROLLER_THROTTLER_COUNT,
पूर्ण;

क्रमागत smudpm_v4_5_i2ccontrollerprotocol_eअणु
    SMC_V4_5_I2C_CONTROLLER_PROTOCOL_VR_0,
    SMC_V4_5_I2C_CONTROLLER_PROTOCOL_VR_1,
    SMC_V4_5_I2C_CONTROLLER_PROTOCOL_TMP_0,
    SMC_V4_5_I2C_CONTROLLER_PROTOCOL_TMP_1,
    SMC_V4_5_I2C_CONTROLLER_PROTOCOL_SPARE_0,
    SMC_V4_5_I2C_CONTROLLER_PROTOCOL_SPARE_1,
    SMC_V4_5_I2C_CONTROLLER_PROTOCOL_COUNT,
पूर्ण;

काष्ठा smudpm_i2c_controller_config_v2
अणु
    uपूर्णांक8_t   Enabled;
    uपूर्णांक8_t   Speed;
    uपूर्णांक8_t   Padding[2];
    uपूर्णांक32_t  SlaveAddress;
    uपूर्णांक8_t   ControllerPort;
    uपूर्णांक8_t   ControllerName;
    uपूर्णांक8_t   ThermalThrotter;
    uपूर्णांक8_t   I2cProtocol;
पूर्ण;

काष्ठा atom_smc_dpm_info_v4_5
अणु
  काष्ठा   atom_common_table_header  table_header;
    // SECTION: BOARD PARAMETERS
    // I2C Control
  काष्ठा smudpm_i2c_controller_config_v2  I2cControllers[8];

  // SVI2 Board Parameters
  uपूर्णांक16_t     MaxVoltageStepGfx; // In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken अगर voltage change exceeds this value.
  uपूर्णांक16_t     MaxVoltageStepSoc; // In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken अगर voltage change exceeds this value.

  uपूर्णांक8_t      VddGfxVrMapping;   // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddSocVrMapping;   // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddMem0VrMapping;  // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddMem1VrMapping;  // Use VR_MAPPING* bitfields

  uपूर्णांक8_t      GfxUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
  uपूर्णांक8_t      SocUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
  uपूर्णांक8_t      ExternalSensorPresent; // External RDI connected to TMON (aka TEMP IN)
  uपूर्णांक8_t      Padding8_V;

  // Telemetry Settings
  uपूर्णांक16_t     GfxMaxCurrent;   // in Amps
  uपूर्णांक8_t      GfxOffset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryGfx;
  uपूर्णांक16_t     SocMaxCurrent;   // in Amps
  uपूर्णांक8_t      SocOffset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetrySoc;

  uपूर्णांक16_t     Mem0MaxCurrent;   // in Amps
  uपूर्णांक8_t      Mem0Offset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryMem0;

  uपूर्णांक16_t     Mem1MaxCurrent;   // in Amps
  uपूर्णांक8_t      Mem1Offset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryMem1;

  // GPIO Settings
  uपूर्णांक8_t      AcDcGpio;        // GPIO pin configured क्रम AC/DC चयनing
  uपूर्णांक8_t      AcDcPolarity;    // GPIO polarity क्रम AC/DC चयनing
  uपूर्णांक8_t      VR0HotGpio;      // GPIO pin configured क्रम VR0 HOT event
  uपूर्णांक8_t      VR0HotPolarity;  // GPIO polarity क्रम VR0 HOT event

  uपूर्णांक8_t      VR1HotGpio;      // GPIO pin configured क्रम VR1 HOT event 
  uपूर्णांक8_t      VR1HotPolarity;  // GPIO polarity क्रम VR1 HOT event 
  uपूर्णांक8_t      GthrGpio;        // GPIO pin configured क्रम GTHR Event
  uपूर्णांक8_t      GthrPolarity;    // replace GPIO polarity क्रम GTHR

  // LED Display Settings
  uपूर्णांक8_t      LedPin0;         // GPIO number क्रम LedPin[0]
  uपूर्णांक8_t      LedPin1;         // GPIO number क्रम LedPin[1]
  uपूर्णांक8_t      LedPin2;         // GPIO number क्रम LedPin[2]
  uपूर्णांक8_t      padding8_4;

  // GFXCLK PLL Spपढ़ो Spectrum
  uपूर्णांक8_t      PllGfxclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      PllGfxclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     PllGfxclkSpपढ़ोFreq;      // kHz

  // GFXCLK DFLL Spपढ़ो Spectrum
  uपूर्णांक8_t      DfllGfxclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      DfllGfxclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     DfllGfxclkSpपढ़ोFreq;      // kHz

  // UCLK Spपढ़ो Spectrum
  uपूर्णांक8_t      UclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      UclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     UclkSpपढ़ोFreq;      // kHz

  // SOCCLK Spपढ़ो Spectrum
  uपूर्णांक8_t      SoclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      SocclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     SocclkSpपढ़ोFreq;      // kHz

  // Total board घातer
  uपूर्णांक16_t     TotalBoardPower;     //Only needed क्रम TCP Estimated हाल, where TCP = TGP+Total Board Power
  uपूर्णांक16_t     BoardPadding; 

  // Mvdd Svi2 Div Ratio Setting
  uपूर्णांक32_t MvddRatio; // This is used क्रम MVDD Vid workaround. It has 16 fractional bits (Q16.16)
  
  uपूर्णांक32_t     BoardReserved[9];

पूर्ण;

काष्ठा atom_smc_dpm_info_v4_6
अणु
  काष्ठा   atom_common_table_header  table_header;
  // section: board parameters
  uपूर्णांक32_t     i2c_padding[3];   // old i2c control are moved to new area

  uपूर्णांक16_t     maxvoltagestepgfx; // in mv(q2) max voltage step that smu will request. multiple steps are taken अगर voltage change exceeds this value.
  uपूर्णांक16_t     maxvoltagestepsoc; // in mv(q2) max voltage step that smu will request. multiple steps are taken अगर voltage change exceeds this value.

  uपूर्णांक8_t      vddgfxvrmapping;     // use vr_mapping* bitfields
  uपूर्णांक8_t      vddsocvrmapping;     // use vr_mapping* bitfields
  uपूर्णांक8_t      vddmemvrmapping;     // use vr_mapping* bitfields
  uपूर्णांक8_t      boardvrmapping;      // use vr_mapping* bitfields

  uपूर्णांक8_t      gfxulvphasesheddingmask; // set this to 1 to set psi0/1 to 1 in ulv mode
  uपूर्णांक8_t      बाह्यalsensorpresent; // बाह्यal rdi connected to पंचांगon (aka temp in)
  uपूर्णांक8_t      padding8_v[2];

  // telemetry settings
  uपूर्णांक16_t     gfxmaxcurrent;   // in amps
  uपूर्णांक8_t      gfxoffset;       // in amps
  uपूर्णांक8_t      padding_telemetrygfx;

  uपूर्णांक16_t     socmaxcurrent;   // in amps
  uपूर्णांक8_t      socoffset;       // in amps
  uपूर्णांक8_t      padding_telemetrysoc;

  uपूर्णांक16_t     memmaxcurrent;   // in amps
  uपूर्णांक8_t      memoffset;       // in amps
  uपूर्णांक8_t      padding_telemetrymem;

  uपूर्णांक16_t     boardmaxcurrent;   // in amps
  uपूर्णांक8_t      boarकरोffset;       // in amps
  uपूर्णांक8_t      padding_telemetryboardinput;

  // gpio settings
  uपूर्णांक8_t      vr0hotgpio;      // gpio pin configured क्रम vr0 hot event
  uपूर्णांक8_t      vr0hotpolarity;  // gpio polarity क्रम vr0 hot event
  uपूर्णांक8_t      vr1hotgpio;      // gpio pin configured क्रम vr1 hot event
  uपूर्णांक8_t      vr1hotpolarity;  // gpio polarity क्रम vr1 hot event

 // gfxclk pll spपढ़ो spectrum
  uपूर्णांक8_t	   pllgfxclkspपढ़ोenabled;	// on or off
  uपूर्णांक8_t	   pllgfxclkspपढ़ोpercent;	// q4.4
  uपूर्णांक16_t	   pllgfxclkspपढ़ोfreq;		// khz

 // uclk spपढ़ो spectrum
  uपूर्णांक8_t	   uclkspपढ़ोenabled;   // on or off
  uपूर्णांक8_t	   uclkspपढ़ोpercent;   // q4.4
  uपूर्णांक16_t	   uclkspपढ़ोfreq;	   // khz

 // fclk spपढ़ो spectrum
  uपूर्णांक8_t	   fclkspपढ़ोenabled;   // on or off
  uपूर्णांक8_t	   fclkspपढ़ोpercent;   // q4.4
  uपूर्णांक16_t	   fclkspपढ़ोfreq;	   // khz


  // gfxclk fll spपढ़ो spectrum
  uपूर्णांक8_t      fllgfxclkspपढ़ोenabled;   // on or off
  uपूर्णांक8_t      fllgfxclkspपढ़ोpercent;   // q4.4
  uपूर्णांक16_t     fllgfxclkspपढ़ोfreq;      // khz

  // i2c controller काष्ठाure
  काष्ठा smudpm_i2c_controller_config_v2 i2ccontrollers[8];

  // memory section
  uपूर्णांक32_t	 memorychannelenabled; // क्रम dram use only, max 32 channels enabled bit mask.

  uपूर्णांक8_t 	 drambitwidth; // क्रम dram use only.  see dram bit width type defines
  uपूर्णांक8_t 	 paddingmem[3];

	// total board घातer
  uपूर्णांक16_t	 totalboardघातer;	  //only needed क्रम tcp estimated हाल, where tcp = tgp+total board घातer
  uपूर्णांक16_t	 boardpadding;

	// section: xgmi training
  uपूर्णांक8_t 	 xgmilinkspeed[4];
  uपूर्णांक8_t 	 xgmilinkwidth[4];

  uपूर्णांक16_t	 xgmअगरclkfreq[4];
  uपूर्णांक16_t	 xgmisocvoltage[4];

  // reserved
  uपूर्णांक32_t   boardreserved[10];
पूर्ण;

काष्ठा atom_smc_dpm_info_v4_7
अणु
  काष्ठा   atom_common_table_header  table_header;
    // SECTION: BOARD PARAMETERS
    // I2C Control
  काष्ठा smudpm_i2c_controller_config_v2  I2cControllers[8];

  // SVI2 Board Parameters
  uपूर्णांक16_t     MaxVoltageStepGfx; // In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken अगर voltage change exceeds this value.
  uपूर्णांक16_t     MaxVoltageStepSoc; // In mV(Q2) Max voltage step that SMU will request. Multiple steps are taken अगर voltage change exceeds this value.

  uपूर्णांक8_t      VddGfxVrMapping;   // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddSocVrMapping;   // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddMem0VrMapping;  // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddMem1VrMapping;  // Use VR_MAPPING* bitfields

  uपूर्णांक8_t      GfxUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
  uपूर्णांक8_t      SocUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
  uपूर्णांक8_t      ExternalSensorPresent; // External RDI connected to TMON (aka TEMP IN)
  uपूर्णांक8_t      Padding8_V;

  // Telemetry Settings
  uपूर्णांक16_t     GfxMaxCurrent;   // in Amps
  uपूर्णांक8_t      GfxOffset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryGfx;
  uपूर्णांक16_t     SocMaxCurrent;   // in Amps
  uपूर्णांक8_t      SocOffset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetrySoc;

  uपूर्णांक16_t     Mem0MaxCurrent;   // in Amps
  uपूर्णांक8_t      Mem0Offset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryMem0;

  uपूर्णांक16_t     Mem1MaxCurrent;   // in Amps
  uपूर्णांक8_t      Mem1Offset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryMem1;

  // GPIO Settings
  uपूर्णांक8_t      AcDcGpio;        // GPIO pin configured क्रम AC/DC चयनing
  uपूर्णांक8_t      AcDcPolarity;    // GPIO polarity क्रम AC/DC चयनing
  uपूर्णांक8_t      VR0HotGpio;      // GPIO pin configured क्रम VR0 HOT event
  uपूर्णांक8_t      VR0HotPolarity;  // GPIO polarity क्रम VR0 HOT event

  uपूर्णांक8_t      VR1HotGpio;      // GPIO pin configured क्रम VR1 HOT event
  uपूर्णांक8_t      VR1HotPolarity;  // GPIO polarity क्रम VR1 HOT event
  uपूर्णांक8_t      GthrGpio;        // GPIO pin configured क्रम GTHR Event
  uपूर्णांक8_t      GthrPolarity;    // replace GPIO polarity क्रम GTHR

  // LED Display Settings
  uपूर्णांक8_t      LedPin0;         // GPIO number क्रम LedPin[0]
  uपूर्णांक8_t      LedPin1;         // GPIO number क्रम LedPin[1]
  uपूर्णांक8_t      LedPin2;         // GPIO number क्रम LedPin[2]
  uपूर्णांक8_t      padding8_4;

  // GFXCLK PLL Spपढ़ो Spectrum
  uपूर्णांक8_t      PllGfxclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      PllGfxclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     PllGfxclkSpपढ़ोFreq;      // kHz

  // GFXCLK DFLL Spपढ़ो Spectrum
  uपूर्णांक8_t      DfllGfxclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      DfllGfxclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     DfllGfxclkSpपढ़ोFreq;      // kHz

  // UCLK Spपढ़ो Spectrum
  uपूर्णांक8_t      UclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      UclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     UclkSpपढ़ोFreq;      // kHz

  // SOCCLK Spपढ़ो Spectrum
  uपूर्णांक8_t      SoclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      SocclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     SocclkSpपढ़ोFreq;      // kHz

  // Total board घातer
  uपूर्णांक16_t     TotalBoardPower;     //Only needed क्रम TCP Estimated हाल, where TCP = TGP+Total Board Power
  uपूर्णांक16_t     BoardPadding;

  // Mvdd Svi2 Div Ratio Setting
  uपूर्णांक32_t     MvddRatio; // This is used क्रम MVDD Vid workaround. It has 16 fractional bits (Q16.16)

  // GPIO pins क्रम I2C communications with 2nd controller क्रम Input Telemetry Sequence
  uपूर्णांक8_t      GpioI2cScl;          // Serial Clock
  uपूर्णांक8_t      GpioI2cSda;          // Serial Data
  uपूर्णांक16_t     GpioPadding;

  // Additional LED Display Settings
  uपूर्णांक8_t      LedPin3;         // GPIO number क्रम LedPin[3] - PCIE GEN Speed
  uपूर्णांक8_t      LedPin4;         // GPIO number क्रम LedPin[4] - PMFW Error Status
  uपूर्णांक16_t     LedEnableMask;

  // Power Limit Scalars
  uपूर्णांक8_t      PowerLimitScalar[4];    //[PPT_THROTTLER_COUNT]

  uपूर्णांक8_t      MvddUlvPhaseSheddingMask;
  uपूर्णांक8_t      VddciUlvPhaseSheddingMask;
  uपूर्णांक8_t      Padding8_Psi1;
  uपूर्णांक8_t      Padding8_Psi2;

  uपूर्णांक32_t     BoardReserved[5];
पूर्ण;

काष्ठा smudpm_i2c_controller_config_v3
अणु
  uपूर्णांक8_t   Enabled;
  uपूर्णांक8_t   Speed;
  uपूर्णांक8_t   SlaveAddress;
  uपूर्णांक8_t   ControllerPort;
  uपूर्णांक8_t   ControllerName;
  uपूर्णांक8_t   ThermalThrotter;
  uपूर्णांक8_t   I2cProtocol;
  uपूर्णांक8_t   PaddingConfig;
पूर्ण;

काष्ठा atom_smc_dpm_info_v4_9
अणु
  काष्ठा   atom_common_table_header  table_header;

  //SECTION: Gaming Clocks
  //uपूर्णांक32_t     GamingClk[6];

  // SECTION: I2C Control
  काष्ठा smudpm_i2c_controller_config_v3  I2cControllers[16];     

  uपूर्णांक8_t      GpioScl;  // GPIO Number क्रम SCL Line, used only क्रम CKSVII2C1
  uपूर्णांक8_t      GpioSda;  // GPIO Number क्रम SDA Line, used only क्रम CKSVII2C1
  uपूर्णांक8_t      FchUsbPdSlaveAddr; //For requesting USB PD controller S-states via FCH I2C when entering PME turn off
  uपूर्णांक8_t      I2cSpare;

  // SECTION: SVI2 Board Parameters
  uपूर्णांक8_t      VddGfxVrMapping;   // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddSocVrMapping;   // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddMem0VrMapping;  // Use VR_MAPPING* bitfields
  uपूर्णांक8_t      VddMem1VrMapping;  // Use VR_MAPPING* bitfields

  uपूर्णांक8_t      GfxUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
  uपूर्णांक8_t      SocUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
  uपूर्णांक8_t      VddciUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode
  uपूर्णांक8_t      MvddUlvPhaseSheddingMask; // set this to 1 to set PSI0/1 to 1 in ULV mode

  // SECTION: Telemetry Settings
  uपूर्णांक16_t     GfxMaxCurrent;   // in Amps
  uपूर्णांक8_t      GfxOffset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryGfx;

  uपूर्णांक16_t     SocMaxCurrent;   // in Amps
  uपूर्णांक8_t      SocOffset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetrySoc;

  uपूर्णांक16_t     Mem0MaxCurrent;   // in Amps
  uपूर्णांक8_t      Mem0Offset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryMem0;
  
  uपूर्णांक16_t     Mem1MaxCurrent;   // in Amps
  uपूर्णांक8_t      Mem1Offset;       // in Amps
  uपूर्णांक8_t      Padding_TelemetryMem1;

  uपूर्णांक32_t     MvddRatio; // This is used क्रम MVDD  Svi2 Div Ratio workaround. It has 16 fractional bits (Q16.16)
  
  // SECTION: GPIO Settings
  uपूर्णांक8_t      AcDcGpio;        // GPIO pin configured क्रम AC/DC चयनing
  uपूर्णांक8_t      AcDcPolarity;    // GPIO polarity क्रम AC/DC चयनing
  uपूर्णांक8_t      VR0HotGpio;      // GPIO pin configured क्रम VR0 HOT event
  uपूर्णांक8_t      VR0HotPolarity;  // GPIO polarity क्रम VR0 HOT event

  uपूर्णांक8_t      VR1HotGpio;      // GPIO pin configured क्रम VR1 HOT event 
  uपूर्णांक8_t      VR1HotPolarity;  // GPIO polarity क्रम VR1 HOT event 
  uपूर्णांक8_t      GthrGpio;        // GPIO pin configured क्रम GTHR Event
  uपूर्णांक8_t      GthrPolarity;    // replace GPIO polarity क्रम GTHR

  // LED Display Settings
  uपूर्णांक8_t      LedPin0;         // GPIO number क्रम LedPin[0]
  uपूर्णांक8_t      LedPin1;         // GPIO number क्रम LedPin[1]
  uपूर्णांक8_t      LedPin2;         // GPIO number क्रम LedPin[2]
  uपूर्णांक8_t      LedEnableMask;

  uपूर्णांक8_t      LedPcie;        // GPIO number क्रम PCIE results
  uपूर्णांक8_t      LedError;       // GPIO number क्रम Error Cases
  uपूर्णांक8_t      LedSpare1[2];

  // SECTION: Clock Spपढ़ो Spectrum
  
  // GFXCLK PLL Spपढ़ो Spectrum
  uपूर्णांक8_t      PllGfxclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      PllGfxclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     PllGfxclkSpपढ़ोFreq;      // kHz

  // GFXCLK DFLL Spपढ़ो Spectrum
  uपूर्णांक8_t      DfllGfxclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      DfllGfxclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     DfllGfxclkSpपढ़ोFreq;      // kHz
  
  // UCLK Spपढ़ो Spectrum
  uपूर्णांक8_t      UclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      UclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     UclkSpपढ़ोFreq;      // kHz

  // FCLK Spपढ़ो Spectrum
  uपूर्णांक8_t      FclkSpपढ़ोEnabled;   // on or off
  uपूर्णांक8_t      FclkSpपढ़ोPercent;   // Q4.4
  uपूर्णांक16_t     FclkSpपढ़ोFreq;      // kHz
  
  // Section: Memory Config
  uपूर्णांक32_t     MemoryChannelEnabled; // For DRAM use only, Max 32 channels enabled bit mask. 
  
  uपूर्णांक8_t      DramBitWidth; // For DRAM use only.  See Dram Bit width type defines
  uपूर्णांक8_t      PaddingMem1[3];

  // Section: Total Board Power
  uपूर्णांक16_t     TotalBoardPower;     //Only needed क्रम TCP Estimated हाल, where TCP = TGP+Total Board Power
  uपूर्णांक16_t     BoardPowerPadding; 
  
  // SECTION: XGMI Training
  uपूर्णांक8_t      XgmiLinkSpeed   [4];
  uपूर्णांक8_t      XgmiLinkWidth   [4];

  uपूर्णांक16_t     XgmiFclkFreq    [4];
  uपूर्णांक16_t     XgmiSocVoltage  [4];

  // SECTION: Board Reserved

  uपूर्णांक32_t     BoardReserved[16];

पूर्ण;

काष्ठा atom_smc_dpm_info_v4_10
अणु
  काष्ठा   atom_common_table_header  table_header;

  // SECTION: BOARD PARAMETERS
  // Telemetry Settings
  uपूर्णांक16_t GfxMaxCurrent; // in Amps
  uपूर्णांक8_t   GfxOffset;     // in Amps
  uपूर्णांक8_t  Padding_TelemetryGfx;

  uपूर्णांक16_t SocMaxCurrent; // in Amps
  uपूर्णांक8_t   SocOffset;     // in Amps
  uपूर्णांक8_t  Padding_TelemetrySoc;

  uपूर्णांक16_t MemMaxCurrent; // in Amps
  uपूर्णांक8_t   MemOffset;     // in Amps
  uपूर्णांक8_t  Padding_TelemetryMem;

  uपूर्णांक16_t BoardMaxCurrent; // in Amps
  uपूर्णांक8_t   BoardOffset;     // in Amps
  uपूर्णांक8_t  Padding_TelemetryBoardInput;

  // Platक्रमm input telemetry voltage coefficient
  uपूर्णांक32_t BoardVoltageCoeffA; // decode by /1000
  uपूर्णांक32_t BoardVoltageCoeffB; // decode by /1000

  // GPIO Settings
  uपूर्णांक8_t  VR0HotGpio;     // GPIO pin configured क्रम VR0 HOT event
  uपूर्णांक8_t  VR0HotPolarity; // GPIO polarity क्रम VR0 HOT event
  uपूर्णांक8_t  VR1HotGpio;     // GPIO pin configured क्रम VR1 HOT event
  uपूर्णांक8_t  VR1HotPolarity; // GPIO polarity क्रम VR1 HOT event

  // UCLK Spपढ़ो Spectrum
  uपूर्णांक8_t  UclkSpपढ़ोEnabled; // on or off
  uपूर्णांक8_t  UclkSpपढ़ोPercent; // Q4.4
  uपूर्णांक16_t UclkSpपढ़ोFreq;    // kHz

  // FCLK Spपढ़ो Spectrum
  uपूर्णांक8_t  FclkSpपढ़ोEnabled; // on or off
  uपूर्णांक8_t  FclkSpपढ़ोPercent; // Q4.4
  uपूर्णांक16_t FclkSpपढ़ोFreq;    // kHz

  // I2C Controller Structure
  काष्ठा smudpm_i2c_controller_config_v3  I2cControllers[8];

  // GPIO pins क्रम I2C communications with 2nd controller क्रम Input Telemetry Sequence
  uपूर्णांक8_t  GpioI2cScl; // Serial Clock
  uपूर्णांक8_t  GpioI2cSda; // Serial Data
  uपूर्णांक16_t spare5;

  uपूर्णांक32_t reserved[16];
पूर्ण;

/* 
  ***************************************************************************
    Data Table asic_profiling_info  काष्ठाure
  ***************************************************************************
*/
काष्ठा  atom_asic_profiling_info_v4_1
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक32_t  maxvddc;                 
  uपूर्णांक32_t  minvddc;               
  uपूर्णांक32_t  avfs_meannsigma_acontant0;
  uपूर्णांक32_t  avfs_meannsigma_acontant1;
  uपूर्णांक32_t  avfs_meannsigma_acontant2;
  uपूर्णांक16_t  avfs_meannsigma_dc_tol_sigma;
  uपूर्णांक16_t  avfs_meannsigma_platक्रमm_mean;
  uपूर्णांक16_t  avfs_meannsigma_platक्रमm_sigma;
  uपूर्णांक32_t  gb_vdroop_table_cksoff_a0;
  uपूर्णांक32_t  gb_vdroop_table_cksoff_a1;
  uपूर्णांक32_t  gb_vdroop_table_cksoff_a2;
  uपूर्णांक32_t  gb_vdroop_table_ckson_a0;
  uपूर्णांक32_t  gb_vdroop_table_ckson_a1;
  uपूर्णांक32_t  gb_vdroop_table_ckson_a2;
  uपूर्णांक32_t  avfsgb_fuse_table_cksoff_m1;
  uपूर्णांक32_t  avfsgb_fuse_table_cksoff_m2;
  uपूर्णांक32_t  avfsgb_fuse_table_cksoff_b;
  uपूर्णांक32_t  avfsgb_fuse_table_ckson_m1;	
  uपूर्णांक32_t  avfsgb_fuse_table_ckson_m2;
  uपूर्णांक32_t  avfsgb_fuse_table_ckson_b;
  uपूर्णांक16_t  max_voltage_0_25mv;
  uपूर्णांक8_t   enable_gb_vdroop_table_cksoff;
  uपूर्णांक8_t   enable_gb_vdroop_table_ckson;
  uपूर्णांक8_t   enable_gb_fuse_table_cksoff;
  uपूर्णांक8_t   enable_gb_fuse_table_ckson;
  uपूर्णांक16_t  psm_age_comfactor;
  uपूर्णांक8_t   enable_apply_avfs_cksoff_voltage;
  uपूर्णांक8_t   reserved;
  uपूर्णांक32_t  dispclk2gfxclk_a;
  uपूर्णांक32_t  dispclk2gfxclk_b;
  uपूर्णांक32_t  dispclk2gfxclk_c;
  uपूर्णांक32_t  pixclk2gfxclk_a;
  uपूर्णांक32_t  pixclk2gfxclk_b;
  uपूर्णांक32_t  pixclk2gfxclk_c;
  uपूर्णांक32_t  dcefclk2gfxclk_a;
  uपूर्णांक32_t  dcefclk2gfxclk_b;
  uपूर्णांक32_t  dcefclk2gfxclk_c;
  uपूर्णांक32_t  phyclk2gfxclk_a;
  uपूर्णांक32_t  phyclk2gfxclk_b;
  uपूर्णांक32_t  phyclk2gfxclk_c;
पूर्ण;

काष्ठा  atom_asic_profiling_info_v4_2 अणु
	काष्ठा  atom_common_table_header  table_header;
	uपूर्णांक32_t  maxvddc;
	uपूर्णांक32_t  minvddc;
	uपूर्णांक32_t  avfs_meannsigma_acontant0;
	uपूर्णांक32_t  avfs_meannsigma_acontant1;
	uपूर्णांक32_t  avfs_meannsigma_acontant2;
	uपूर्णांक16_t  avfs_meannsigma_dc_tol_sigma;
	uपूर्णांक16_t  avfs_meannsigma_platक्रमm_mean;
	uपूर्णांक16_t  avfs_meannsigma_platक्रमm_sigma;
	uपूर्णांक32_t  gb_vdroop_table_cksoff_a0;
	uपूर्णांक32_t  gb_vdroop_table_cksoff_a1;
	uपूर्णांक32_t  gb_vdroop_table_cksoff_a2;
	uपूर्णांक32_t  gb_vdroop_table_ckson_a0;
	uपूर्णांक32_t  gb_vdroop_table_ckson_a1;
	uपूर्णांक32_t  gb_vdroop_table_ckson_a2;
	uपूर्णांक32_t  avfsgb_fuse_table_cksoff_m1;
	uपूर्णांक32_t  avfsgb_fuse_table_cksoff_m2;
	uपूर्णांक32_t  avfsgb_fuse_table_cksoff_b;
	uपूर्णांक32_t  avfsgb_fuse_table_ckson_m1;
	uपूर्णांक32_t  avfsgb_fuse_table_ckson_m2;
	uपूर्णांक32_t  avfsgb_fuse_table_ckson_b;
	uपूर्णांक16_t  max_voltage_0_25mv;
	uपूर्णांक8_t   enable_gb_vdroop_table_cksoff;
	uपूर्णांक8_t   enable_gb_vdroop_table_ckson;
	uपूर्णांक8_t   enable_gb_fuse_table_cksoff;
	uपूर्णांक8_t   enable_gb_fuse_table_ckson;
	uपूर्णांक16_t  psm_age_comfactor;
	uपूर्णांक8_t   enable_apply_avfs_cksoff_voltage;
	uपूर्णांक8_t   reserved;
	uपूर्णांक32_t  dispclk2gfxclk_a;
	uपूर्णांक32_t  dispclk2gfxclk_b;
	uपूर्णांक32_t  dispclk2gfxclk_c;
	uपूर्णांक32_t  pixclk2gfxclk_a;
	uपूर्णांक32_t  pixclk2gfxclk_b;
	uपूर्णांक32_t  pixclk2gfxclk_c;
	uपूर्णांक32_t  dcefclk2gfxclk_a;
	uपूर्णांक32_t  dcefclk2gfxclk_b;
	uपूर्णांक32_t  dcefclk2gfxclk_c;
	uपूर्णांक32_t  phyclk2gfxclk_a;
	uपूर्णांक32_t  phyclk2gfxclk_b;
	uपूर्णांक32_t  phyclk2gfxclk_c;
	uपूर्णांक32_t  acg_gb_vdroop_table_a0;
	uपूर्णांक32_t  acg_gb_vdroop_table_a1;
	uपूर्णांक32_t  acg_gb_vdroop_table_a2;
	uपूर्णांक32_t  acg_avfsgb_fuse_table_m1;
	uपूर्णांक32_t  acg_avfsgb_fuse_table_m2;
	uपूर्णांक32_t  acg_avfsgb_fuse_table_b;
	uपूर्णांक8_t   enable_acg_gb_vdroop_table;
	uपूर्णांक8_t   enable_acg_gb_fuse_table;
	uपूर्णांक32_t  acg_dispclk2gfxclk_a;
	uपूर्णांक32_t  acg_dispclk2gfxclk_b;
	uपूर्णांक32_t  acg_dispclk2gfxclk_c;
	uपूर्णांक32_t  acg_pixclk2gfxclk_a;
	uपूर्णांक32_t  acg_pixclk2gfxclk_b;
	uपूर्णांक32_t  acg_pixclk2gfxclk_c;
	uपूर्णांक32_t  acg_dcefclk2gfxclk_a;
	uपूर्णांक32_t  acg_dcefclk2gfxclk_b;
	uपूर्णांक32_t  acg_dcefclk2gfxclk_c;
	uपूर्णांक32_t  acg_phyclk2gfxclk_a;
	uपूर्णांक32_t  acg_phyclk2gfxclk_b;
	uपूर्णांक32_t  acg_phyclk2gfxclk_c;
पूर्ण;

/* 
  ***************************************************************************
    Data Table mulसमयdia_info  काष्ठाure
  ***************************************************************************
*/
काष्ठा atom_mulसमयdia_info_v2_1
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक8_t uvdip_min_ver;
  uपूर्णांक8_t uvdip_max_ver;
  uपूर्णांक8_t vceip_min_ver;
  uपूर्णांक8_t vceip_max_ver;
  uपूर्णांक16_t uvd_enc_max_input_width_pixels;
  uपूर्णांक16_t uvd_enc_max_input_height_pixels;
  uपूर्णांक16_t vce_enc_max_input_width_pixels;
  uपूर्णांक16_t vce_enc_max_input_height_pixels; 
  uपूर्णांक32_t uvd_enc_max_bandwidth;           // 16x16 pixels/sec, codec independent
  uपूर्णांक32_t vce_enc_max_bandwidth;           // 16x16 pixels/sec, codec independent
पूर्ण;


/* 
  ***************************************************************************
    Data Table umc_info  काष्ठाure
  ***************************************************************************
*/
काष्ठा atom_umc_info_v3_1
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक32_t ucode_version;
  uपूर्णांक32_t ucode_rom_startaddr;
  uपूर्णांक32_t ucode_length;
  uपूर्णांक16_t umc_reg_init_offset;
  uपूर्णांक16_t customer_ucode_name_offset;
  uपूर्णांक16_t mclk_ss_percentage;
  uपूर्णांक16_t mclk_ss_rate_10hz;
  uपूर्णांक8_t umcip_min_ver;
  uपूर्णांक8_t umcip_max_ver;
  uपूर्णांक8_t vram_type;              //क्रमागत of atom_dgpu_vram_type
  uपूर्णांक8_t umc_config;
  uपूर्णांक32_t mem_refclk_10khz;
पूर्ण;

// umc_info.umc_config
क्रमागत atom_umc_config_def अणु
  UMC_CONFIG__ENABLE_1KB_INTERLEAVE_MODE  =   0x00000001,
  UMC_CONFIG__DEFAULT_MEM_ECC_ENABLE      =   0x00000002,
  UMC_CONFIG__ENABLE_HBM_LANE_REPAIR      =   0x00000004,
  UMC_CONFIG__ENABLE_BANK_HARVESTING      =   0x00000008,
  UMC_CONFIG__ENABLE_PHY_REINIT           =   0x00000010,
  UMC_CONFIG__DISABLE_UCODE_CHKSTATUS     =   0x00000020,
पूर्ण;

काष्ठा atom_umc_info_v3_2
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक32_t ucode_version;
  uपूर्णांक32_t ucode_rom_startaddr;
  uपूर्णांक32_t ucode_length;
  uपूर्णांक16_t umc_reg_init_offset;
  uपूर्णांक16_t customer_ucode_name_offset;
  uपूर्णांक16_t mclk_ss_percentage;
  uपूर्णांक16_t mclk_ss_rate_10hz;
  uपूर्णांक8_t umcip_min_ver;
  uपूर्णांक8_t umcip_max_ver;
  uपूर्णांक8_t vram_type;              //क्रमागत of atom_dgpu_vram_type
  uपूर्णांक8_t umc_config;
  uपूर्णांक32_t mem_refclk_10khz;
  uपूर्णांक32_t pstate_uclk_10khz[4];
  uपूर्णांक16_t umcgoldenoffset;
  uपूर्णांक16_t densitygoldenoffset;
पूर्ण;

काष्ठा atom_umc_info_v3_3
अणु
  काष्ठा  atom_common_table_header  table_header;
  uपूर्णांक32_t ucode_reserved;
  uपूर्णांक32_t ucode_rom_startaddr;
  uपूर्णांक32_t ucode_length;
  uपूर्णांक16_t umc_reg_init_offset;
  uपूर्णांक16_t customer_ucode_name_offset;
  uपूर्णांक16_t mclk_ss_percentage;
  uपूर्णांक16_t mclk_ss_rate_10hz;
  uपूर्णांक8_t umcip_min_ver;
  uपूर्णांक8_t umcip_max_ver;
  uपूर्णांक8_t vram_type;              //क्रमागत of atom_dgpu_vram_type
  uपूर्णांक8_t umc_config;
  uपूर्णांक32_t mem_refclk_10khz;
  uपूर्णांक32_t pstate_uclk_10khz[4];
  uपूर्णांक16_t umcgoldenoffset;
  uपूर्णांक16_t densitygoldenoffset;
  uपूर्णांक32_t umc_config1;
  uपूर्णांक32_t bist_data_startaddr;
  uपूर्णांक32_t reserved[2];
पूर्ण;

क्रमागत atom_umc_config1_def अणु
	UMC_CONFIG1__ENABLE_PSTATE_PHASE_STORE_TRAIN = 0x00000001,
	UMC_CONFIG1__ENABLE_AUTO_FRAMING = 0x00000002,
	UMC_CONFIG1__ENABLE_RESTORE_BIST_DATA = 0x00000004,
	UMC_CONFIG1__DISABLE_STROBE_MODE = 0x00000008,
	UMC_CONFIG1__DEBUG_DATA_PARITY_EN = 0x00000010,
	UMC_CONFIG1__ENABLE_ECC_CAPABLE = 0x00010000,
पूर्ण;

/* 
  ***************************************************************************
    Data Table vram_info  काष्ठाure
  ***************************************************************************
*/
काष्ठा atom_vram_module_v9 अणु
  // Design Specअगरic Values
  uपूर्णांक32_t  memory_size;                   // Total memory size in unit of MB क्रम CONFIG_MEMSIZE zeros
  uपूर्णांक32_t  channel_enable;                // bit vector, each bit indicate specअगरic channel enable or not
  uपूर्णांक32_t  max_mem_clk;                   // max memory घड़ी of this memory in unit of 10kHz, =0 means it is not defined
  uपूर्णांक16_t  reserved[3];
  uपूर्णांक16_t  mem_voltage;                   // mem_voltage
  uपूर्णांक16_t  vram_module_size;              // Size of atom_vram_module_v9
  uपूर्णांक8_t   ext_memory_id;                 // Current memory module ID
  uपूर्णांक8_t   memory_type;                   // क्रमागत of atom_dgpu_vram_type
  uपूर्णांक8_t   channel_num;                   // Number of mem. channels supported in this module
  uपूर्णांक8_t   channel_width;                 // CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT
  uपूर्णांक8_t   density;                       // _8Mx32, _16Mx32, _16Mx16, _32Mx16
  uपूर्णांक8_t   tunningset_id;                 // MC phy रेजिस्टरs set per. 
  uपूर्णांक8_t   vender_rev_id;                 // [7:4] Revision, [3:0] Venकरोr code
  uपूर्णांक8_t   refreshrate;                   // [1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)
  uपूर्णांक8_t   hbm_ven_rev_id;		   // hbm_ven_rev_id
  uपूर्णांक8_t   vram_rsd2;			   // reserved
  अक्षर    dram_pnstring[20];               // part number end with '0'. 
पूर्ण;

काष्ठा atom_vram_info_header_v2_3 अणु
  काष्ठा   atom_common_table_header table_header;
  uपूर्णांक16_t mem_adjust_tbloffset;                         // offset of atom_umc_init_reg_block काष्ठाure क्रम memory venकरोr specअगरic UMC adjust setting
  uपूर्णांक16_t mem_clk_patch_tbloffset;                      // offset of atom_umc_init_reg_block काष्ठाure क्रम memory घड़ी specअगरic UMC setting
  uपूर्णांक16_t mc_adjust_pertile_tbloffset;                  // offset of atom_umc_init_reg_block काष्ठाure क्रम Per Byte Offset Preset Settings
  uपूर्णांक16_t mc_phyinit_tbloffset;                         // offset of atom_umc_init_reg_block काष्ठाure क्रम MC phy init set
  uपूर्णांक16_t dram_data_remap_tbloffset;                    // reserved क्रम now
  uपूर्णांक16_t पंचांगrs_seq_offset;                              // offset of HBM पंचांगrs
  uपूर्णांक16_t post_ucode_init_offset;                       // offset of atom_umc_init_reg_block काष्ठाure क्रम MC phy init after MC uCode complete umc init
  uपूर्णांक16_t vram_rsd2;
  uपूर्णांक8_t  vram_module_num;                              // indicate number of VRAM module
  uपूर्णांक8_t  umcip_min_ver;
  uपूर्णांक8_t  umcip_max_ver;
  uपूर्णांक8_t  mc_phy_tile_num;                              // indicate the MCD tile number which use in DramDataRemapTbl and usMcAdjustPerTileTblOffset
  काष्ठा   atom_vram_module_v9  vram_module[16];         // just क्रम allocation, real number of blocks is in ucNumOfVRAMModule;
पूर्ण;

काष्ठा atom_umc_रेजिस्टर_addr_infoअणु
  uपूर्णांक32_t  umc_रेजिस्टर_addr:24;
  uपूर्णांक32_t  umc_reg_type_ind:1;
  uपूर्णांक32_t  umc_reg_rsvd:7;
पूर्ण;

//atom_umc_रेजिस्टर_addr_info.
क्रमागत atom_umc_रेजिस्टर_addr_info_flagअणु
  b3ATOM_UMC_REG_ADD_INFO_INसूचीECT_ACCESS  =0x01,
पूर्ण;

जोड़ atom_umc_रेजिस्टर_addr_info_access
अणु
  काष्ठा atom_umc_रेजिस्टर_addr_info umc_reg_addr;
  uपूर्णांक32_t u32umc_reg_addr;
पूर्ण;

काष्ठा atom_umc_reg_setting_id_configअणु
  uपूर्णांक32_t memघड़ीrange:24;
  uपूर्णांक32_t mem_blk_id:8;
पूर्ण;

जोड़ atom_umc_reg_setting_id_config_access
अणु
  काष्ठा atom_umc_reg_setting_id_config umc_id_access;
  uपूर्णांक32_t  u32umc_id_access;
पूर्ण;

काष्ठा atom_umc_reg_setting_data_blockअणु
  जोड़ atom_umc_reg_setting_id_config_access  block_id;
  uपूर्णांक32_t u32umc_reg_data[1];                       
पूर्ण;

काष्ठा atom_umc_init_reg_blockअणु
  uपूर्णांक16_t umc_reg_num;
  uपूर्णांक16_t reserved;    
  जोड़ atom_umc_रेजिस्टर_addr_info_access umc_reg_list[1];     //क्रम allocation purpose, the real number come from umc_reg_num;
  काष्ठा atom_umc_reg_setting_data_block umc_reg_setting_list[1];
पूर्ण;

काष्ठा atom_vram_module_v10 अणु
  // Design Specअगरic Values
  uपूर्णांक32_t  memory_size;                   // Total memory size in unit of MB क्रम CONFIG_MEMSIZE zeros
  uपूर्णांक32_t  channel_enable;                // bit vector, each bit indicate specअगरic channel enable or not
  uपूर्णांक32_t  max_mem_clk;                   // max memory घड़ी of this memory in unit of 10kHz, =0 means it is not defined
  uपूर्णांक16_t  reserved[3];
  uपूर्णांक16_t  mem_voltage;                   // mem_voltage
  uपूर्णांक16_t  vram_module_size;              // Size of atom_vram_module_v9
  uपूर्णांक8_t   ext_memory_id;                 // Current memory module ID
  uपूर्णांक8_t   memory_type;                   // क्रमागत of atom_dgpu_vram_type
  uपूर्णांक8_t   channel_num;                   // Number of mem. channels supported in this module
  uपूर्णांक8_t   channel_width;                 // CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT
  uपूर्णांक8_t   density;                       // _8Mx32, _16Mx32, _16Mx16, _32Mx16
  uपूर्णांक8_t   tunningset_id;                 // MC phy रेजिस्टरs set per
  uपूर्णांक8_t   vender_rev_id;                 // [7:4] Revision, [3:0] Venकरोr code
  uपूर्णांक8_t   refreshrate;                   // [1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)
  uपूर्णांक8_t   vram_flags;			   // bit0= bankgroup enable
  uपूर्णांक8_t   vram_rsd2;			   // reserved
  uपूर्णांक16_t  gddr6_mr10;                    // gddr6 mode रेजिस्टर10 value
  uपूर्णांक16_t  gddr6_mr1;                     // gddr6 mode रेजिस्टर1 value
  uपूर्णांक16_t  gddr6_mr2;                     // gddr6 mode रेजिस्टर2 value
  uपूर्णांक16_t  gddr6_mr7;                     // gddr6 mode रेजिस्टर7 value
  अक्षर    dram_pnstring[20];               // part number end with '0'
पूर्ण;

काष्ठा atom_vram_info_header_v2_4 अणु
  काष्ठा   atom_common_table_header table_header;
  uपूर्णांक16_t mem_adjust_tbloffset;                         // offset of atom_umc_init_reg_block काष्ठाure क्रम memory venकरोr specअगरic UMC adjust setting
  uपूर्णांक16_t mem_clk_patch_tbloffset;                      // offset of atom_umc_init_reg_block काष्ठाure क्रम memory घड़ी specअगरic UMC setting
  uपूर्णांक16_t mc_adjust_pertile_tbloffset;                  // offset of atom_umc_init_reg_block काष्ठाure क्रम Per Byte Offset Preset Settings
  uपूर्णांक16_t mc_phyinit_tbloffset;                         // offset of atom_umc_init_reg_block काष्ठाure क्रम MC phy init set
  uपूर्णांक16_t dram_data_remap_tbloffset;                    // reserved क्रम now
  uपूर्णांक16_t reserved;                                     // offset of reserved
  uपूर्णांक16_t post_ucode_init_offset;                       // offset of atom_umc_init_reg_block काष्ठाure क्रम MC phy init after MC uCode complete umc init
  uपूर्णांक16_t vram_rsd2;
  uपूर्णांक8_t  vram_module_num;                              // indicate number of VRAM module
  uपूर्णांक8_t  umcip_min_ver;
  uपूर्णांक8_t  umcip_max_ver;
  uपूर्णांक8_t  mc_phy_tile_num;                              // indicate the MCD tile number which use in DramDataRemapTbl and usMcAdjustPerTileTblOffset
  काष्ठा   atom_vram_module_v10  vram_module[16];        // just क्रम allocation, real number of blocks is in ucNumOfVRAMModule;
पूर्ण;

काष्ठा atom_vram_module_v11 अणु
	// Design Specअगरic Values
	uपूर्णांक32_t  memory_size;                   // Total memory size in unit of MB क्रम CONFIG_MEMSIZE zeros
	uपूर्णांक32_t  channel_enable;                // bit vector, each bit indicate specअगरic channel enable or not
	uपूर्णांक16_t  mem_voltage;                   // mem_voltage
	uपूर्णांक16_t  vram_module_size;              // Size of atom_vram_module_v9
	uपूर्णांक8_t   ext_memory_id;                 // Current memory module ID
	uपूर्णांक8_t   memory_type;                   // क्रमागत of atom_dgpu_vram_type
	uपूर्णांक8_t   channel_num;                   // Number of mem. channels supported in this module
	uपूर्णांक8_t   channel_width;                 // CHANNEL_16BIT/CHANNEL_32BIT/CHANNEL_64BIT
	uपूर्णांक8_t   density;                       // _8Mx32, _16Mx32, _16Mx16, _32Mx16
	uपूर्णांक8_t   tunningset_id;                 // MC phy रेजिस्टरs set per.
	uपूर्णांक16_t  reserved[4];                   // reserved
	uपूर्णांक8_t   vender_rev_id;                 // [7:4] Revision, [3:0] Venकरोr code
	uपूर्णांक8_t   refreshrate;			 // [1:0]=RefreshFactor (00=8ms, 01=16ms, 10=32ms,11=64ms)
	uपूर्णांक8_t   vram_flags;			 // bit0= bankgroup enable
	uपूर्णांक8_t   vram_rsd2;			 // reserved
	uपूर्णांक16_t  gddr6_mr10;                    // gddr6 mode रेजिस्टर10 value
	uपूर्णांक16_t  gddr6_mr0;                     // gddr6 mode रेजिस्टर0 value
	uपूर्णांक16_t  gddr6_mr1;                     // gddr6 mode रेजिस्टर1 value
	uपूर्णांक16_t  gddr6_mr2;                     // gddr6 mode रेजिस्टर2 value
	uपूर्णांक16_t  gddr6_mr4;                     // gddr6 mode रेजिस्टर4 value
	uपूर्णांक16_t  gddr6_mr7;                     // gddr6 mode रेजिस्टर7 value
	uपूर्णांक16_t  gddr6_mr8;                     // gddr6 mode रेजिस्टर8 value
	अक्षर    dram_pnstring[40];               // part number end with '0'.
पूर्ण;

काष्ठा atom_gddr6_ac_timing_v2_5 अणु
	uपूर्णांक32_t  u32umc_id_access;
	uपूर्णांक8_t  RL;
	uपूर्णांक8_t  WL;
	uपूर्णांक8_t  tRAS;
	uपूर्णांक8_t  tRC;

	uपूर्णांक16_t  tREFI;
	uपूर्णांक8_t  tRFC;
	uपूर्णांक8_t  tRFCpb;

	uपूर्णांक8_t  tRREFD;
	uपूर्णांक8_t  tRCDRD;
	uपूर्णांक8_t  tRCDWR;
	uपूर्णांक8_t  tRP;

	uपूर्णांक8_t  tRRDS;
	uपूर्णांक8_t  tRRDL;
	uपूर्णांक8_t  tWR;
	uपूर्णांक8_t  tWTRS;

	uपूर्णांक8_t  tWTRL;
	uपूर्णांक8_t  tFAW;
	uपूर्णांक8_t  tCCDS;
	uपूर्णांक8_t  tCCDL;

	uपूर्णांक8_t  tCRCRL;
	uपूर्णांक8_t  tCRCWL;
	uपूर्णांक8_t  tCKE;
	uपूर्णांक8_t  tCKSRE;

	uपूर्णांक8_t  tCKSRX;
	uपूर्णांक8_t  tRTPS;
	uपूर्णांक8_t  tRTPL;
	uपूर्णांक8_t  tMRD;

	uपूर्णांक8_t  tMOD;
	uपूर्णांक8_t  tXS;
	uपूर्णांक8_t  tXHP;
	uपूर्णांक8_t  tXSMRS;

	uपूर्णांक32_t  tXSH;

	uपूर्णांक8_t  tPD;
	uपूर्णांक8_t  tXP;
	uपूर्णांक8_t  tCPDED;
	uपूर्णांक8_t  tACTPDE;

	uपूर्णांक8_t  tPREPDE;
	uपूर्णांक8_t  tREFPDE;
	uपूर्णांक8_t  tMRSPDEN;
	uपूर्णांक8_t  tRDSRE;

	uपूर्णांक8_t  tWRSRE;
	uपूर्णांक8_t  tPPD;
	uपूर्णांक8_t  tCCDMW;
	uपूर्णांक8_t  tWTRTR;

	uपूर्णांक8_t  tLTLTR;
	uपूर्णांक8_t  tREFTR;
	uपूर्णांक8_t  VNDR;
	uपूर्णांक8_t  reserved[9];
पूर्ण;

काष्ठा atom_gddr6_bit_byte_remap अणु
	uपूर्णांक32_t dphy_byteremap;    //mmUMC_DPHY_ByteRemap
	uपूर्णांक32_t dphy_bitremap0;    //mmUMC_DPHY_BitRemap0
	uपूर्णांक32_t dphy_bitremap1;    //mmUMC_DPHY_BitRemap1
	uपूर्णांक32_t dphy_bitremap2;    //mmUMC_DPHY_BitRemap2
	uपूर्णांक32_t aphy_bitremap0;    //mmUMC_APHY_BitRemap0
	uपूर्णांक32_t aphy_bitremap1;    //mmUMC_APHY_BitRemap1
	uपूर्णांक32_t phy_dram;          //mmUMC_PHY_DRAM
पूर्ण;

काष्ठा atom_gddr6_dram_data_remap अणु
	uपूर्णांक32_t table_size;
	uपूर्णांक8_t phyपूर्णांकf_ck_inverted[8];     //UMC_PHY_PHYINTF_CNTL.INV_CK
	काष्ठा atom_gddr6_bit_byte_remap bit_byte_remap[16];
पूर्ण;

काष्ठा atom_vram_info_header_v2_5 अणु
	काष्ठा   atom_common_table_header table_header;
	uपूर्णांक16_t mem_adjust_tbloffset;                         // offset of atom_umc_init_reg_block काष्ठाure क्रम memory venकरोr specअगरic UMC adjust settings
	uपूर्णांक16_t gddr6_ac_timing_offset;                     // offset of atom_gddr6_ac_timing_v2_5 काष्ठाure क्रम memory घड़ी specअगरic UMC settings
	uपूर्णांक16_t mc_adjust_pertile_tbloffset;                  // offset of atom_umc_init_reg_block काष्ठाure क्रम Per Byte Offset Preset Settings
	uपूर्णांक16_t mc_phyinit_tbloffset;                         // offset of atom_umc_init_reg_block काष्ठाure क्रम MC phy init set
	uपूर्णांक16_t dram_data_remap_tbloffset;                    // offset of atom_gddr6_dram_data_remap array to indicate DRAM data lane to GPU mapping
	uपूर्णांक16_t reserved;                                     // offset of reserved
	uपूर्णांक16_t post_ucode_init_offset;                       // offset of atom_umc_init_reg_block काष्ठाure क्रम MC phy init after MC uCode complete umc init
	uपूर्णांक16_t strobe_mode_patch_tbloffset;                  // offset of atom_umc_init_reg_block काष्ठाure क्रम Strobe Mode memory घड़ी specअगरic UMC settings
	uपूर्णांक8_t  vram_module_num;                              // indicate number of VRAM module
	uपूर्णांक8_t  umcip_min_ver;
	uपूर्णांक8_t  umcip_max_ver;
	uपूर्णांक8_t  mc_phy_tile_num;                              // indicate the MCD tile number which use in DramDataRemapTbl and usMcAdjustPerTileTblOffset
	काष्ठा   atom_vram_module_v11  vram_module[16];        // just क्रम allocation, real number of blocks is in ucNumOfVRAMModule;
पूर्ण;

काष्ठा atom_vram_info_header_v2_6 अणु
	काष्ठा atom_common_table_header table_header;
	uपूर्णांक16_t mem_adjust_tbloffset;
	uपूर्णांक16_t mem_clk_patch_tbloffset;
	uपूर्णांक16_t mc_adjust_pertile_tbloffset;
	uपूर्णांक16_t mc_phyinit_tbloffset;
	uपूर्णांक16_t dram_data_remap_tbloffset;
	uपूर्णांक16_t पंचांगrs_seq_offset;
	uपूर्णांक16_t post_ucode_init_offset;
	uपूर्णांक16_t vram_rsd2;
	uपूर्णांक8_t  vram_module_num;
	uपूर्णांक8_t  umcip_min_ver;
	uपूर्णांक8_t  umcip_max_ver;
	uपूर्णांक8_t  mc_phy_tile_num;
	काष्ठा atom_vram_module_v9 vram_module[16];
पूर्ण;
/* 
  ***************************************************************************
    Data Table voltageobject_info  काष्ठाure
  ***************************************************************************
*/
काष्ठा  atom_i2c_data_entry
अणु
  uपूर्णांक16_t  i2c_reg_index;               // i2c रेजिस्टर address, can be up to 16bit
  uपूर्णांक16_t  i2c_reg_data;                // i2c रेजिस्टर data, can be up to 16bit
पूर्ण;

काष्ठा atom_voltage_object_header_v4अणु
  uपूर्णांक8_t    voltage_type;                           //क्रमागत atom_voltage_type
  uपूर्णांक8_t    voltage_mode;                           //क्रमागत atom_voltage_object_mode 
  uपूर्णांक16_t   object_size;                            //Size of Object
पूर्ण;

// atom_voltage_object_header_v4.voltage_mode
क्रमागत atom_voltage_object_mode 
अणु
   VOLTAGE_OBJ_GPIO_LUT              =  0,        //VOLTAGE and GPIO Lookup table ->atom_gpio_voltage_object_v4
   VOLTAGE_OBJ_VR_I2C_INIT_SEQ       =  3,        //VOLTAGE REGULATOR INIT sequece through I2C -> atom_i2c_voltage_object_v4
   VOLTAGE_OBJ_PHASE_LUT             =  4,        //Set Vregulator Phase lookup table ->atom_gpio_voltage_object_v4
   VOLTAGE_OBJ_SVID2                 =  7,        //Indicate voltage control by SVID2 ->atom_svid2_voltage_object_v4
   VOLTAGE_OBJ_EVV                   =  8, 
   VOLTAGE_OBJ_MERGED_POWER          =  9,
पूर्ण;

काष्ठा  atom_i2c_voltage_object_v4
अणु
   काष्ठा atom_voltage_object_header_v4 header;  // voltage mode = VOLTAGE_OBJ_VR_I2C_INIT_SEQ
   uपूर्णांक8_t  regulator_id;                        //Indicate Voltage Regulator Id
   uपूर्णांक8_t  i2c_id;
   uपूर्णांक8_t  i2c_slave_addr;
   uपूर्णांक8_t  i2c_control_offset;       
   uपूर्णांक8_t  i2c_flag;                            // Bit0: 0 - One byte data; 1 - Two byte data
   uपूर्णांक8_t  i2c_speed;                           // =0, use शेष i2c speed, otherwise use it in unit of kHz. 
   uपूर्णांक8_t  reserved[2];
   काष्ठा atom_i2c_data_entry i2cdatalut[1];     // end with 0xff
पूर्ण;

// ATOM_I2C_VOLTAGE_OBJECT_V3.ucVoltageControlFlag
क्रमागत atom_i2c_voltage_control_flag
अणु
   VOLTAGE_DATA_ONE_BYTE = 0,
   VOLTAGE_DATA_TWO_BYTE = 1,
पूर्ण;


काष्ठा atom_voltage_gpio_map_lut
अणु
  uपूर्णांक32_t  voltage_gpio_reg_val;              // The Voltage ID which is used to program GPIO रेजिस्टर
  uपूर्णांक16_t  voltage_level_mv;                  // The corresponding Voltage Value, in mV
पूर्ण;

काष्ठा atom_gpio_voltage_object_v4
अणु
   काष्ठा atom_voltage_object_header_v4 header;  // voltage mode = VOLTAGE_OBJ_GPIO_LUT or VOLTAGE_OBJ_PHASE_LUT
   uपूर्णांक8_t  gpio_control_id;                     // शेष is 0 which indicate control through CG VID mode 
   uपूर्णांक8_t  gpio_entry_num;                      // indiate the entry numbers of Votlage/Gpio value Look up table
   uपूर्णांक8_t  phase_delay_us;                      // phase delay in unit of micro second
   uपूर्णांक8_t  reserved;   
   uपूर्णांक32_t gpio_mask_val;                         // GPIO Mask value
   काष्ठा atom_voltage_gpio_map_lut voltage_gpio_lut[1];
पूर्ण;

काष्ठा  atom_svid2_voltage_object_v4
अणु
   काष्ठा atom_voltage_object_header_v4 header;  // voltage mode = VOLTAGE_OBJ_SVID2
   uपूर्णांक8_t loadline_psi1;                        // bit4:0= loadline setting ( Core Loadline trim and offset trim ), bit5=0:PSI1_L disable =1: PSI1_L enable
   uपूर्णांक8_t psi0_l_vid_thresd;                    // VR PSI0_L VID threshold
   uपूर्णांक8_t psi0_enable;                          // 
   uपूर्णांक8_t maxvstep;
   uपूर्णांक8_t telemetry_offset;
   uपूर्णांक8_t telemetry_gain; 
   uपूर्णांक16_t reserved1;
पूर्ण;

काष्ठा atom_merged_voltage_object_v4
अणु
  काष्ठा atom_voltage_object_header_v4 header;  // voltage mode = VOLTAGE_OBJ_MERGED_POWER
  uपूर्णांक8_t  merged_घातerrail_type;               //क्रमागत atom_voltage_type
  uपूर्णांक8_t  reserved[3];
पूर्ण;

जोड़ atom_voltage_object_v4अणु
  काष्ठा atom_gpio_voltage_object_v4 gpio_voltage_obj;
  काष्ठा atom_i2c_voltage_object_v4 i2c_voltage_obj;
  काष्ठा atom_svid2_voltage_object_v4 svid2_voltage_obj;
  काष्ठा atom_merged_voltage_object_v4 merged_voltage_obj;
पूर्ण;

काष्ठा  atom_voltage_objects_info_v4_1
अणु
  काष्ठा atom_common_table_header table_header; 
  जोड़ atom_voltage_object_v4 voltage_object[1];   //Info क्रम Voltage control
पूर्ण;


/* 
  ***************************************************************************
              All Command Function काष्ठाure definition 
  *************************************************************************** 
*/   

/* 
  ***************************************************************************
              Structures used by asic_init
  *************************************************************************** 
*/   

काष्ठा asic_init_engine_parameters
अणु
  uपूर्णांक32_t sclkfreqin10khz:24;
  uपूर्णांक32_t engineflag:8;              /* क्रमागत atom_asic_init_engine_flag  */
पूर्ण;

काष्ठा asic_init_mem_parameters
अणु
  uपूर्णांक32_t mclkfreqin10khz:24;
  uपूर्णांक32_t memflag:8;                 /* क्रमागत atom_asic_init_mem_flag  */
पूर्ण;

काष्ठा asic_init_parameters_v2_1
अणु
  काष्ठा asic_init_engine_parameters engineparam;
  काष्ठा asic_init_mem_parameters memparam;
पूर्ण;

काष्ठा asic_init_ps_allocation_v2_1
अणु
  काष्ठा asic_init_parameters_v2_1 param;
  uपूर्णांक32_t reserved[16];
पूर्ण;


क्रमागत atom_asic_init_engine_flag
अणु
  b3NORMAL_ENGINE_INIT = 0,
  b3SRIOV_SKIP_ASIC_INIT = 0x02,
  b3SRIOV_LOAD_UCODE = 0x40,
पूर्ण;

क्रमागत atom_asic_init_mem_flag
अणु
  b3NORMAL_MEM_INIT = 0,
  b3DRAM_SELF_REFRESH_EXIT =0x20,
पूर्ण;

/* 
  ***************************************************************************
              Structures used by setengineघड़ी
  *************************************************************************** 
*/   

काष्ठा set_engine_घड़ी_parameters_v2_1
अणु
  uपूर्णांक32_t sclkfreqin10khz:24;
  uपूर्णांक32_t sclkflag:8;              /* क्रमागत atom_set_engine_mem_घड़ी_flag,  */
  uपूर्णांक32_t reserved[10];
पूर्ण;

काष्ठा set_engine_घड़ी_ps_allocation_v2_1
अणु
  काष्ठा set_engine_घड़ी_parameters_v2_1 घड़ीinfo;
  uपूर्णांक32_t reserved[10];
पूर्ण;


क्रमागत atom_set_engine_mem_घड़ी_flag
अणु
  b3NORMAL_CHANGE_CLOCK = 0,
  b3FIRST_TIME_CHANGE_CLOCK = 0x08,
  b3STORE_DPM_TRAINGING = 0x40,         //Applicable to memory घड़ी change,when set, it store specअगरic DPM mode training result
पूर्ण;

/* 
  ***************************************************************************
              Structures used by getengineघड़ी
  *************************************************************************** 
*/   
काष्ठा get_engine_घड़ी_parameter
अणु
  uपूर्णांक32_t sclk_10khz;          // current engine speed in 10KHz unit
  uपूर्णांक32_t reserved;
पूर्ण;

/* 
  ***************************************************************************
              Structures used by seपंचांगemoryघड़ी
  *************************************************************************** 
*/   
काष्ठा set_memory_घड़ी_parameters_v2_1
अणु
  uपूर्णांक32_t mclkfreqin10khz:24;
  uपूर्णांक32_t mclkflag:8;              /* क्रमागत atom_set_engine_mem_घड़ी_flag,  */
  uपूर्णांक32_t reserved[10];
पूर्ण;

काष्ठा set_memory_घड़ी_ps_allocation_v2_1
अणु
  काष्ठा set_memory_घड़ी_parameters_v2_1 घड़ीinfo;
  uपूर्णांक32_t reserved[10];
पूर्ण;


/* 
  ***************************************************************************
              Structures used by geपंचांगemoryघड़ी
  *************************************************************************** 
*/   
काष्ठा get_memory_घड़ी_parameter
अणु
  uपूर्णांक32_t mclk_10khz;          // current engine speed in 10KHz unit
  uपूर्णांक32_t reserved;
पूर्ण;



/* 
  ***************************************************************************
              Structures used by setvoltage
  *************************************************************************** 
*/   

काष्ठा set_voltage_parameters_v1_4
अणु
  uपूर्णांक8_t  voltagetype;                /* क्रमागत atom_voltage_type */
  uपूर्णांक8_t  command;                    /* Indicate action: Set voltage level, क्रमागत atom_set_voltage_command */
  uपूर्णांक16_t vlevel_mv;                  /* real voltage level in unit of mv or Voltage Phase (0, 1, 2, .. ) */
पूर्ण;

//set_voltage_parameters_v2_1.voltagemode
क्रमागत atom_set_voltage_commandअणु
  ATOM_SET_VOLTAGE  = 0,
  ATOM_INIT_VOLTAGE_REGULATOR = 3,
  ATOM_SET_VOLTAGE_PHASE = 4,
  ATOM_GET_LEAKAGE_ID    = 8,
पूर्ण;

काष्ठा set_voltage_ps_allocation_v1_4
अणु
  काष्ठा set_voltage_parameters_v1_4 setvoltageparam;
  uपूर्णांक32_t reserved[10];
पूर्ण;


/* 
  ***************************************************************************
              Structures used by computegpuघड़ीparam
  *************************************************************************** 
*/   

//ATOM_COMPUTE_CLOCK_FREQ.ulComputeClockFlag
क्रमागत atom_gpu_घड़ी_प्रकारype 
अणु
  COMPUTE_GPUCLK_INPUT_FLAG_DEFAULT_GPUCLK =0x00,
  COMPUTE_GPUCLK_INPUT_FLAG_GFXCLK =0x01,
  COMPUTE_GPUCLK_INPUT_FLAG_UCLK =0x02,
पूर्ण;

काष्ठा compute_gpu_घड़ी_input_parameter_v1_8
अणु
  uपूर्णांक32_t  gpuघड़ी_10khz:24;         //Input= target घड़ी, output = actual घड़ी 
  uपूर्णांक32_t  gpu_घड़ी_प्रकारype:8;          //Input indicate घड़ी type: क्रमागत atom_gpu_घड़ी_प्रकारype
  uपूर्णांक32_t  reserved[5];
पूर्ण;


काष्ठा compute_gpu_घड़ी_output_parameter_v1_8
अणु
  uपूर्णांक32_t  gpuघड़ी_10khz:24;              //Input= target घड़ी, output = actual घड़ी 
  uपूर्णांक32_t  dfs_did:8;                      //वापस parameter: DFS भागider which is used to program to रेजिस्टर directly
  uपूर्णांक32_t  pll_fb_mult;                    //Feedback Multiplier, bit 8:0 पूर्णांक, bit 15:12 post_भाग, bit 31:16 frac
  uपूर्णांक32_t  pll_ss_fbsmult;                 // Spपढ़ो FB Mult: bit 8:0 पूर्णांक, bit 31:16 frac
  uपूर्णांक16_t  pll_ss_slew_frac;
  uपूर्णांक8_t   pll_ss_enable;
  uपूर्णांक8_t   reserved;
  uपूर्णांक32_t  reserved1[2];
पूर्ण;



/* 
  ***************************************************************************
              Structures used by ReadEfuseValue
  *************************************************************************** 
*/   

काष्ठा पढ़ो_efuse_input_parameters_v3_1
अणु
  uपूर्णांक16_t efuse_start_index;
  uपूर्णांक8_t  reserved;
  uपूर्णांक8_t  bitslen;
पूर्ण;

// ReadEfuseValue input/output parameter
जोड़ पढ़ो_efuse_value_parameters_v3_1
अणु
  काष्ठा पढ़ो_efuse_input_parameters_v3_1 efuse_info;
  uपूर्णांक32_t efusevalue;
पूर्ण;


/* 
  ***************************************************************************
              Structures used by माला_लोmuघड़ीinfo
  *************************************************************************** 
*/   
काष्ठा atom_get_smu_घड़ी_info_parameters_v3_1
अणु
  uपूर्णांक8_t syspll_id;          // 0= syspll0, 1=syspll1, 2=syspll2                
  uपूर्णांक8_t clk_id;             // atom_smu9_syspll0_घड़ी_id  (only valid when command == GET_SMU_CLOCK_INFO_V3_1_GET_CLOCK_FREQ )
  uपूर्णांक8_t command;            // क्रमागत of atom_get_smu_घड़ी_info_command
  uपूर्णांक8_t dfsdid;             // =0: get DFS DID from रेजिस्टर, >0, give DFS भागider, (only valid when command == GET_SMU_CLOCK_INFO_V3_1_GET_CLOCK_FREQ )
पूर्ण;

क्रमागत atom_get_smu_घड़ी_info_command 
अणु
  GET_SMU_CLOCK_INFO_V3_1_GET_CLOCK_FREQ       = 0,
  GET_SMU_CLOCK_INFO_V3_1_GET_PLLVCO_FREQ      = 1,
  GET_SMU_CLOCK_INFO_V3_1_GET_PLLREFCLK_FREQ   = 2,
पूर्ण;

क्रमागत atom_smu9_syspll0_घड़ी_id
अणु
  SMU9_SYSPLL0_SMNCLK_ID   = 0,       //  SMNCLK
  SMU9_SYSPLL0_SOCCLK_ID   = 1,       //	SOCCLK (FCLK)
  SMU9_SYSPLL0_MP0CLK_ID   = 2,       //	MP0CLK
  SMU9_SYSPLL0_MP1CLK_ID   = 3,       //	MP1CLK
  SMU9_SYSPLL0_LCLK_ID     = 4,       //	LCLK
  SMU9_SYSPLL0_DCLK_ID     = 5,       //	DCLK
  SMU9_SYSPLL0_VCLK_ID     = 6,       //	VCLK
  SMU9_SYSPLL0_ECLK_ID     = 7,       //	ECLK
  SMU9_SYSPLL0_DCEFCLK_ID  = 8,       //	DCEFCLK
  SMU9_SYSPLL0_DPREFCLK_ID = 10,      //	DPREFCLK
  SMU9_SYSPLL0_DISPCLK_ID  = 11,      //	DISPCLK
पूर्ण;

क्रमागत atom_smu11_syspll_id अणु
  SMU11_SYSPLL0_ID            = 0,
  SMU11_SYSPLL1_0_ID          = 1,
  SMU11_SYSPLL1_1_ID          = 2,
  SMU11_SYSPLL1_2_ID          = 3,
  SMU11_SYSPLL2_ID            = 4,
  SMU11_SYSPLL3_0_ID          = 5,
  SMU11_SYSPLL3_1_ID          = 6,
पूर्ण;

क्रमागत atom_smu11_syspll0_घड़ी_id अणु
  SMU11_SYSPLL0_ECLK_ID     = 0,       //	ECLK
  SMU11_SYSPLL0_SOCCLK_ID   = 1,       //	SOCCLK
  SMU11_SYSPLL0_MP0CLK_ID   = 2,       //	MP0CLK
  SMU11_SYSPLL0_DCLK_ID     = 3,       //	DCLK
  SMU11_SYSPLL0_VCLK_ID     = 4,       //	VCLK
  SMU11_SYSPLL0_DCEFCLK_ID  = 5,       //	DCEFCLK
पूर्ण;

क्रमागत atom_smu11_syspll1_0_घड़ी_id अणु
  SMU11_SYSPLL1_0_UCLKA_ID   = 0,       // UCLK_a
पूर्ण;

क्रमागत atom_smu11_syspll1_1_घड़ी_id अणु
  SMU11_SYSPLL1_0_UCLKB_ID   = 0,       // UCLK_b
पूर्ण;

क्रमागत atom_smu11_syspll1_2_घड़ी_id अणु
  SMU11_SYSPLL1_0_FCLK_ID   = 0,        // FCLK
पूर्ण;

क्रमागत atom_smu11_syspll2_घड़ी_id अणु
  SMU11_SYSPLL2_GFXCLK_ID   = 0,        // GFXCLK
पूर्ण;

क्रमागत atom_smu11_syspll3_0_घड़ी_id अणु
  SMU11_SYSPLL3_0_WAFCLK_ID = 0,       //	WAFCLK
  SMU11_SYSPLL3_0_DISPCLK_ID = 1,      //	DISPCLK
  SMU11_SYSPLL3_0_DPREFCLK_ID = 2,     //	DPREFCLK
पूर्ण;

क्रमागत atom_smu11_syspll3_1_घड़ी_id अणु
  SMU11_SYSPLL3_1_MP1CLK_ID = 0,       //	MP1CLK
  SMU11_SYSPLL3_1_SMNCLK_ID = 1,       //	SMNCLK
  SMU11_SYSPLL3_1_LCLK_ID = 2,         //	LCLK
पूर्ण;

क्रमागत atom_smu12_syspll_id अणु
  SMU12_SYSPLL0_ID          = 0,
  SMU12_SYSPLL1_ID          = 1,
  SMU12_SYSPLL2_ID          = 2,
  SMU12_SYSPLL3_0_ID        = 3,
  SMU12_SYSPLL3_1_ID        = 4,
पूर्ण;

क्रमागत atom_smu12_syspll0_घड़ी_id अणु
  SMU12_SYSPLL0_SMNCLK_ID   = 0,			//	SOCCLK
  SMU12_SYSPLL0_SOCCLK_ID   = 1,			//	SOCCLK
  SMU12_SYSPLL0_MP0CLK_ID   = 2,			//	MP0CLK
  SMU12_SYSPLL0_MP1CLK_ID   = 3,			//	MP1CLK
  SMU12_SYSPLL0_MP2CLK_ID   = 4,			//	MP2CLK
  SMU12_SYSPLL0_VCLK_ID     = 5,			//	VCLK
  SMU12_SYSPLL0_LCLK_ID     = 6,			//	LCLK
  SMU12_SYSPLL0_DCLK_ID     = 7,			//	DCLK
  SMU12_SYSPLL0_ACLK_ID     = 8,			//	ACLK
  SMU12_SYSPLL0_ISPCLK_ID   = 9,			//	ISPCLK
  SMU12_SYSPLL0_SHUBCLK_ID  = 10,			//	SHUBCLK
पूर्ण;

क्रमागत atom_smu12_syspll1_घड़ी_id अणु
  SMU12_SYSPLL1_DISPCLK_ID  = 0,      //	DISPCLK
  SMU12_SYSPLL1_DPPCLK_ID   = 1,      //	DPPCLK
  SMU12_SYSPLL1_DPREFCLK_ID = 2,      //	DPREFCLK
  SMU12_SYSPLL1_DCFCLK_ID   = 3,      //	DCFCLK
पूर्ण;

क्रमागत atom_smu12_syspll2_घड़ी_id अणु
  SMU12_SYSPLL2_Pre_GFXCLK_ID = 0,   // Pre_GFXCLK
पूर्ण;

क्रमागत atom_smu12_syspll3_0_घड़ी_id अणु
  SMU12_SYSPLL3_0_FCLK_ID = 0,      //	FCLK
पूर्ण;

क्रमागत atom_smu12_syspll3_1_घड़ी_id अणु
  SMU12_SYSPLL3_1_UMCCLK_ID = 0,    //	UMCCLK
पूर्ण;

काष्ठा  atom_get_smu_घड़ी_info_output_parameters_v3_1
अणु
  जोड़ अणु
    uपूर्णांक32_t smu_घड़ी_freq_hz;
    uपूर्णांक32_t syspllvcofreq_10khz;
    uपूर्णांक32_t sysspllrefclk_10khz;
  पूर्णatom_smu_outअ_दोlkfreq;
पूर्ण;



/* 
  ***************************************************************************
              Structures used by dynamicmemorysettings
  *************************************************************************** 
*/   

क्रमागत atom_dynamic_memory_setting_command 
अणु
  COMPUTE_MEMORY_PLL_PARAM = 1,
  COMPUTE_ENGINE_PLL_PARAM = 2,
  ADJUST_MC_SETTING_PARAM = 3,
पूर्ण;

/* when command = COMPUTE_MEMORY_PLL_PARAM or ADJUST_MC_SETTING_PARAM */
काष्ठा dynamic_mclk_settings_parameters_v2_1
अणु
  uपूर्णांक32_t  mclk_10khz:24;         //Input= target mclk
  uपूर्णांक32_t  command:8;             //command क्रमागत of atom_dynamic_memory_setting_command
  uपूर्णांक32_t  reserved;
पूर्ण;

/* when command = COMPUTE_ENGINE_PLL_PARAM */
काष्ठा dynamic_sclk_settings_parameters_v2_1
अणु
  uपूर्णांक32_t  sclk_10khz:24;         //Input= target mclk
  uपूर्णांक32_t  command:8;             //command क्रमागत of atom_dynamic_memory_setting_command
  uपूर्णांक32_t  mclk_10khz;
  uपूर्णांक32_t  reserved;
पूर्ण;

जोड़ dynamic_memory_settings_parameters_v2_1
अणु
  काष्ठा dynamic_mclk_settings_parameters_v2_1 mclk_setting;
  काष्ठा dynamic_sclk_settings_parameters_v2_1 sclk_setting;
पूर्ण;



/* 
  ***************************************************************************
              Structures used by memorytraining
  *************************************************************************** 
*/   

क्रमागत atom_umc6_0_ucode_function_call_क्रमागत_id
अणु
  UMC60_UCODE_FUNC_ID_REINIT                 = 0,
  UMC60_UCODE_FUNC_ID_ENTER_SELFREFRESH      = 1,
  UMC60_UCODE_FUNC_ID_EXIT_SELFREFRESH       = 2,
पूर्ण;


काष्ठा memory_training_parameters_v2_1
अणु
  uपूर्णांक8_t ucode_func_id;
  uपूर्णांक8_t ucode_reserved[3];
  uपूर्णांक32_t reserved[5];
पूर्ण;


/* 
  ***************************************************************************
              Structures used by setpixelघड़ी
  *************************************************************************** 
*/   

काष्ठा set_pixel_घड़ी_parameter_v1_7
अणु
    uपूर्णांक32_t pixclk_100hz;               // target the pixel घड़ी to drive the CRTC timing in unit of 100Hz. 

    uपूर्णांक8_t  pll_id;                     // ATOM_PHY_PLL0/ATOM_PHY_PLL1/ATOM_PPLL0
    uपूर्णांक8_t  encoderobjid;               // ASIC encoder id defined in objectId.h, 
                                         // indicate which graphic encoder will be used. 
    uपूर्णांक8_t  encoder_mode;               // Encoder mode: 
    uपूर्णांक8_t  miscinfo;                   // क्रमागत atom_set_pixel_घड़ी_v1_7_misc_info
    uपूर्णांक8_t  crtc_id;                    // क्रमागत of atom_crtc_def
    uपूर्णांक8_t  deep_color_ratio;           // HDMI panel bit depth: क्रमागत atom_set_pixel_घड़ी_v1_7_deepcolor_ratio
    uपूर्णांक8_t  reserved1[2];    
    uपूर्णांक32_t reserved2;
पूर्ण;

//ucMiscInfo
क्रमागत atom_set_pixel_घड़ी_v1_7_misc_info
अणु
  PIXEL_CLOCK_V7_MISC_FORCE_PROG_PPLL         = 0x01,
  PIXEL_CLOCK_V7_MISC_PROG_PHYPLL             = 0x02,
  PIXEL_CLOCK_V7_MISC_YUV420_MODE             = 0x04,
  PIXEL_CLOCK_V7_MISC_DVI_DUALLINK_EN         = 0x08,
  PIXEL_CLOCK_V7_MISC_REF_DIV_SRC             = 0x30,
  PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_XTALIN      = 0x00,
  PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_PCIE        = 0x10,
  PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_GENLK       = 0x20,
  PIXEL_CLOCK_V7_MISC_REF_DIV_SRC_REFPAD      = 0x30, 
  PIXEL_CLOCK_V7_MISC_ATOMIC_UPDATE           = 0x40,
  PIXEL_CLOCK_V7_MISC_FORCE_SS_DIS            = 0x80,
पूर्ण;

/* deep_color_ratio */
क्रमागत atom_set_pixel_घड़ी_v1_7_deepcolor_ratio
अणु
  PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_DIS          = 0x00,      //00 - DCCG_DEEP_COLOR_DTO_DISABLE: Disable Deep Color DTO 
  PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_5_4          = 0x01,      //01 - DCCG_DEEP_COLOR_DTO_5_4_RATIO: Set Deep Color DTO to 5:4 
  PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_3_2          = 0x02,      //02 - DCCG_DEEP_COLOR_DTO_3_2_RATIO: Set Deep Color DTO to 3:2 
  PIXEL_CLOCK_V7_DEEPCOLOR_RATIO_2_1          = 0x03,      //03 - DCCG_DEEP_COLOR_DTO_2_1_RATIO: Set Deep Color DTO to 2:1 
पूर्ण;

/* 
  ***************************************************************************
              Structures used by setdceघड़ी
  *************************************************************************** 
*/   

// SetDCEClock input parameter क्रम DCE11.2( ELM and BF ) and above 
काष्ठा set_dce_घड़ी_parameters_v2_1
अणु
  uपूर्णांक32_t dceclk_10khz;                               // target DCE frequency in unit of 10KHZ, वापस real DISPCLK/DPREFCLK frequency. 
  uपूर्णांक8_t  dceclktype;                                 // =0: DISPCLK  =1: DPREFCLK  =2: PIXCLK
  uपूर्णांक8_t  dceclksrc;                                  // ATOM_PLL0 or ATOM_GCK_DFS or ATOM_FCH_CLK or ATOM_COMBOPHY_PLLx
  uपूर्णांक8_t  dceclkflag;                                 // Bit [1:0] = PPLL ref घड़ी source ( when ucDCEClkSrc= ATOM_PPLL0 )
  uपूर्णांक8_t  crtc_id;                                    // ucDisp Pipe Id, ATOM_CRTC0/1/2/..., use only when ucDCEClkType = PIXCLK
पूर्ण;

//ucDCEClkType
क्रमागत atom_set_dce_घड़ी_घड़ी_प्रकारype
अणु
  DCE_CLOCK_TYPE_DISPCLK                      = 0,
  DCE_CLOCK_TYPE_DPREFCLK                     = 1,
  DCE_CLOCK_TYPE_PIXELCLK                     = 2,        // used by VBIOS पूर्णांकernally, called by SetPixelClock 
पूर्ण;

//ucDCEClkFlag when ucDCEClkType == DPREFCLK 
क्रमागत atom_set_dce_घड़ी_dprefclk_flag
अणु
  DCE_CLOCK_FLAG_PLL_REFCLK_SRC_MASK          = 0x03,
  DCE_CLOCK_FLAG_PLL_REFCLK_SRC_GENERICA      = 0x00,
  DCE_CLOCK_FLAG_PLL_REFCLK_SRC_GENLK         = 0x01,
  DCE_CLOCK_FLAG_PLL_REFCLK_SRC_PCIE          = 0x02,
  DCE_CLOCK_FLAG_PLL_REFCLK_SRC_XTALIN        = 0x03,
पूर्ण;

//ucDCEClkFlag when ucDCEClkType == PIXCLK 
क्रमागत atom_set_dce_घड़ी_pixclk_flag
अणु
  DCE_CLOCK_FLAG_PCLK_DEEPCOLOR_RATIO_MASK    = 0x03,
  DCE_CLOCK_FLAG_PCLK_DEEPCOLOR_RATIO_DIS     = 0x00,      //00 - DCCG_DEEP_COLOR_DTO_DISABLE: Disable Deep Color DTO 
  DCE_CLOCK_FLAG_PCLK_DEEPCOLOR_RATIO_5_4     = 0x01,      //01 - DCCG_DEEP_COLOR_DTO_5_4_RATIO: Set Deep Color DTO to 5:4 
  DCE_CLOCK_FLAG_PCLK_DEEPCOLOR_RATIO_3_2     = 0x02,      //02 - DCCG_DEEP_COLOR_DTO_3_2_RATIO: Set Deep Color DTO to 3:2 
  DCE_CLOCK_FLAG_PCLK_DEEPCOLOR_RATIO_2_1     = 0x03,      //03 - DCCG_DEEP_COLOR_DTO_2_1_RATIO: Set Deep Color DTO to 2:1 
  DCE_CLOCK_FLAG_PIXCLK_YUV420_MODE           = 0x04,
पूर्ण;

काष्ठा set_dce_घड़ी_ps_allocation_v2_1
अणु
  काष्ठा set_dce_घड़ी_parameters_v2_1 param;
  uपूर्णांक32_t ulReserved[2];
पूर्ण;


/****************************************************************************/   
// Structures used by BlankCRTC
/****************************************************************************/   
काष्ठा blank_crtc_parameters
अणु
  uपूर्णांक8_t  crtc_id;                   // क्रमागत atom_crtc_def
  uपूर्णांक8_t  blanking;                  // क्रमागत atom_blank_crtc_command
  uपूर्णांक16_t reserved;
  uपूर्णांक32_t reserved1;
पूर्ण;

क्रमागत atom_blank_crtc_command
अणु
  ATOM_BLANKING         = 1,
  ATOM_BLANKING_OFF     = 0,
पूर्ण;

/****************************************************************************/   
// Structures used by enablecrtc
/****************************************************************************/   
काष्ठा enable_crtc_parameters
अणु
  uपूर्णांक8_t crtc_id;                    // क्रमागत atom_crtc_def
  uपूर्णांक8_t enable;                     // ATOM_ENABLE or ATOM_DISABLE 
  uपूर्णांक8_t padding[2];
पूर्ण;


/****************************************************************************/   
// Structure used by EnableDispPowerGating
/****************************************************************************/   
काष्ठा enable_disp_घातer_gating_parameters_v2_1
अणु
  uपूर्णांक8_t disp_pipe_id;                // ATOM_CRTC1, ATOM_CRTC2, ...
  uपूर्णांक8_t enable;                     // ATOM_ENABLE or ATOM_DISABLE
  uपूर्णांक8_t padding[2];
पूर्ण;

काष्ठा enable_disp_घातer_gating_ps_allocation 
अणु
  काष्ठा enable_disp_घातer_gating_parameters_v2_1 param;
  uपूर्णांक32_t ulReserved[4];
पूर्ण;

/****************************************************************************/   
// Structure used in setcrtc_usingdtdtiming
/****************************************************************************/   
काष्ठा set_crtc_using_dtd_timing_parameters
अणु
  uपूर्णांक16_t  h_size;
  uपूर्णांक16_t  h_blanking_समय;
  uपूर्णांक16_t  v_size;
  uपूर्णांक16_t  v_blanking_समय;
  uपूर्णांक16_t  h_syncoffset;
  uपूर्णांक16_t  h_syncwidth;
  uपूर्णांक16_t  v_syncoffset;
  uपूर्णांक16_t  v_syncwidth;
  uपूर्णांक16_t  modemiscinfo;  
  uपूर्णांक8_t   h_border;
  uपूर्णांक8_t   v_border;
  uपूर्णांक8_t   crtc_id;                   // क्रमागत atom_crtc_def
  uपूर्णांक8_t   encoder_mode;			   // atom_encode_mode_def
  uपूर्णांक8_t   padding[2];
पूर्ण;


/****************************************************************************/   
// Structures used by processi2cchanneltransaction
/****************************************************************************/   
काष्ठा process_i2c_channel_transaction_parameters
अणु
  uपूर्णांक8_t i2cspeed_khz;
  जोड़ अणु
    uपूर्णांक8_t regindex;
    uपूर्णांक8_t status;                  /* क्रमागत atom_process_i2c_flag */
  पूर्ण regind_status;
  uपूर्णांक16_t  i2c_data_out;
  uपूर्णांक8_t   flag;                    /* क्रमागत atom_process_i2c_status */
  uपूर्णांक8_t   trans_bytes;
  uपूर्णांक8_t   slave_addr;
  uपूर्णांक8_t   i2c_id;
पूर्ण;

//ucFlag
क्रमागत atom_process_i2c_flag
अणु
  HW_I2C_WRITE          = 1,
  HW_I2C_READ           = 0,
  I2C_2BYTE_ADDR        = 0x02,
  HW_I2C_SMBUS_BYTE_WR  = 0x04,
पूर्ण;

//status
क्रमागत atom_process_i2c_status
अणु
  HW_ASSISTED_I2C_STATUS_FAILURE     =2,
  HW_ASSISTED_I2C_STATUS_SUCCESS     =1,
पूर्ण;


/****************************************************************************/   
// Structures used by processauxchanneltransaction
/****************************************************************************/   

काष्ठा process_aux_channel_transaction_parameters_v1_2
अणु
  uपूर्णांक16_t aux_request;
  uपूर्णांक16_t dataout;
  uपूर्णांक8_t  channelid;
  जोड़ अणु
    uपूर्णांक8_t   reply_status;
    uपूर्णांक8_t   aux_delay;
  पूर्ण aux_status_delay;
  uपूर्णांक8_t   dataout_len;
  uपूर्णांक8_t   hpd_id;                                       //=0: HPD1, =1: HPD2, =2: HPD3, =3: HPD4, =4: HPD5, =5: HPD6
पूर्ण;


/****************************************************************************/   
// Structures used by selectcrtc_source
/****************************************************************************/   

काष्ठा select_crtc_source_parameters_v2_3
अणु
  uपूर्णांक8_t crtc_id;                        // क्रमागत atom_crtc_def
  uपूर्णांक8_t encoder_id;                     // क्रमागत atom_dig_def
  uपूर्णांक8_t encode_mode;                    // क्रमागत atom_encode_mode_def
  uपूर्णांक8_t dst_bpc;                        // क्रमागत atom_panel_bit_per_color
पूर्ण;


/****************************************************************************/   
// Structures used by digxencodercontrol
/****************************************************************************/   

// ucAction:
क्रमागत atom_dig_encoder_control_action
अणु
  ATOM_ENCODER_CMD_DISABLE_DIG                  = 0,
  ATOM_ENCODER_CMD_ENABLE_DIG                   = 1,
  ATOM_ENCODER_CMD_DP_LINK_TRAINING_START       = 0x08,
  ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN1    = 0x09,
  ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN2    = 0x0a,
  ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN3    = 0x13,
  ATOM_ENCODER_CMD_DP_LINK_TRAINING_COMPLETE    = 0x0b,
  ATOM_ENCODER_CMD_DP_VIDEO_OFF                 = 0x0c,
  ATOM_ENCODER_CMD_DP_VIDEO_ON                  = 0x0d,
  ATOM_ENCODER_CMD_SETUP_PANEL_MODE             = 0x10,
  ATOM_ENCODER_CMD_DP_LINK_TRAINING_PATTERN4    = 0x14,
  ATOM_ENCODER_CMD_STREAM_SETUP                 = 0x0F, 
  ATOM_ENCODER_CMD_LINK_SETUP                   = 0x11, 
  ATOM_ENCODER_CMD_ENCODER_BLANK                = 0x12,
पूर्ण;

//define ucPanelMode
क्रमागत atom_dig_encoder_control_panelmode
अणु
  DP_PANEL_MODE_DISABLE                        = 0x00,
  DP_PANEL_MODE_ENABLE_eDP_MODE                = 0x01,
  DP_PANEL_MODE_ENABLE_LVLINK_MODE             = 0x11,
पूर्ण;

//ucDigId
क्रमागत atom_dig_encoder_control_v5_digid
अणु
  ATOM_ENCODER_CONFIG_V5_DIG0_ENCODER           = 0x00,
  ATOM_ENCODER_CONFIG_V5_DIG1_ENCODER           = 0x01,
  ATOM_ENCODER_CONFIG_V5_DIG2_ENCODER           = 0x02,
  ATOM_ENCODER_CONFIG_V5_DIG3_ENCODER           = 0x03,
  ATOM_ENCODER_CONFIG_V5_DIG4_ENCODER           = 0x04,
  ATOM_ENCODER_CONFIG_V5_DIG5_ENCODER           = 0x05,
  ATOM_ENCODER_CONFIG_V5_DIG6_ENCODER           = 0x06,
  ATOM_ENCODER_CONFIG_V5_DIG7_ENCODER           = 0x07,
पूर्ण;

काष्ठा dig_encoder_stream_setup_parameters_v1_5
अणु
  uपूर्णांक8_t digid;            // 0~6 map to DIG0~DIG6 क्रमागत atom_dig_encoder_control_v5_digid
  uपूर्णांक8_t action;           // =  ATOM_ENOCODER_CMD_STREAM_SETUP
  uपूर्णांक8_t digmode;          // ATOM_ENCODER_MODE_DP/ATOM_ENCODER_MODE_DVI/ATOM_ENCODER_MODE_HDMI
  uपूर्णांक8_t lanक्रमागत;          // Lane number     
  uपूर्णांक32_t pclk_10khz;      // Pixel Clock in 10Khz
  uपूर्णांक8_t bitpercolor;
  uपूर्णांक8_t dplinkrate_270mhz;//= DP link rate/270Mhz, =6: 1.62G  = 10: 2.7G, =20: 5.4Ghz, =30: 8.1Ghz etc
  uपूर्णांक8_t reserved[2];
पूर्ण;

काष्ठा dig_encoder_link_setup_parameters_v1_5
अणु
  uपूर्णांक8_t digid;           // 0~6 map to DIG0~DIG6 क्रमागत atom_dig_encoder_control_v5_digid
  uपूर्णांक8_t action;          // =  ATOM_ENOCODER_CMD_LINK_SETUP              
  uपूर्णांक8_t digmode;         // ATOM_ENCODER_MODE_DP/ATOM_ENCODER_MODE_DVI/ATOM_ENCODER_MODE_HDMI
  uपूर्णांक8_t lanक्रमागत;         // Lane number     
  uपूर्णांक8_t symclk_10khz;    // Symbol Clock in 10Khz
  uपूर्णांक8_t hpd_sel;
  uपूर्णांक8_t digfe_sel;       // DIG stream( front-end ) selection, bit0 means DIG0 FE is enable, 
  uपूर्णांक8_t reserved[2];
पूर्ण;

काष्ठा dp_panel_mode_set_parameters_v1_5
अणु
  uपूर्णांक8_t digid;              // 0~6 map to DIG0~DIG6 क्रमागत atom_dig_encoder_control_v5_digid
  uपूर्णांक8_t action;             // = ATOM_ENCODER_CMD_DPLINK_SETUP
  uपूर्णांक8_t panelmode;      // क्रमागत atom_dig_encoder_control_panelmode
  uपूर्णांक8_t reserved1;    
  uपूर्णांक32_t reserved2[2];
पूर्ण;

काष्ठा dig_encoder_generic_cmd_parameters_v1_5 
अणु
  uपूर्णांक8_t digid;           // 0~6 map to DIG0~DIG6 क्रमागत atom_dig_encoder_control_v5_digid
  uपूर्णांक8_t action;          // = rest of generic encoder command which करोes not carry any parameters
  uपूर्णांक8_t reserved1[2];    
  uपूर्णांक32_t reserved2[2];
पूर्ण;

जोड़ dig_encoder_control_parameters_v1_5
अणु
  काष्ठा dig_encoder_generic_cmd_parameters_v1_5  cmd_param;
  काष्ठा dig_encoder_stream_setup_parameters_v1_5 stream_param;
  काष्ठा dig_encoder_link_setup_parameters_v1_5   link_param;
  काष्ठा dp_panel_mode_set_parameters_v1_5 dppanel_param;
पूर्ण;

/* 
  ***************************************************************************
              Structures used by dig1transmittercontrol
  *************************************************************************** 
*/   
काष्ठा dig_transmitter_control_parameters_v1_6
अणु
  uपूर्णांक8_t phyid;           // 0=UNIPHYA, 1=UNIPHYB, 2=UNIPHYC, 3=UNIPHYD, 4= UNIPHYE 5=UNIPHYF
  uपूर्णांक8_t action;          // define as ATOM_TRANSMITER_ACTION_xxx
  जोड़ अणु
    uपूर्णांक8_t digmode;        // क्रमागत atom_encode_mode_def
    uपूर्णांक8_t dplaneset;      // DP voltage swing and pre-emphasis value defined in DPCD DP_LANE_SET, "DP_LANE_SET__xDB_y_zV"
  पूर्ण mode_laneset;
  uपूर्णांक8_t  lanक्रमागत;        // Lane number 1, 2, 4, 8    
  uपूर्णांक32_t symclk_10khz;   // Symbol Clock in 10Khz
  uपूर्णांक8_t  hpdsel;         // =1: HPD1, =2: HPD2, .... =6: HPD6, =0: HPD is not asचिन्हित
  uपूर्णांक8_t  digfe_sel;      // DIG stream( front-end ) selection, bit0 means DIG0 FE is enable, 
  uपूर्णांक8_t  connobj_id;     // Connector Object Id defined in ObjectId.h
  uपूर्णांक8_t  reserved;
  uपूर्णांक32_t reserved1;
पूर्ण;

काष्ठा dig_transmitter_control_ps_allocation_v1_6
अणु
  काष्ठा dig_transmitter_control_parameters_v1_6 param;
  uपूर्णांक32_t reserved[4];
पूर्ण;

//ucAction
क्रमागत atom_dig_transmitter_control_action
अणु
  ATOM_TRANSMITTER_ACTION_DISABLE                 = 0,
  ATOM_TRANSMITTER_ACTION_ENABLE                  = 1,
  ATOM_TRANSMITTER_ACTION_LCD_BLOFF               = 2,
  ATOM_TRANSMITTER_ACTION_LCD_BLON                = 3,
  ATOM_TRANSMITTER_ACTION_BL_BRIGHTNESS_CONTROL   = 4,
  ATOM_TRANSMITTER_ACTION_LCD_SELFTEST_START      = 5,
  ATOM_TRANSMITTER_ACTION_LCD_SELFTEST_STOP       = 6,
  ATOM_TRANSMITTER_ACTION_INIT                    = 7,
  ATOM_TRANSMITTER_ACTION_DISABLE_OUTPUT          = 8,
  ATOM_TRANSMITTER_ACTION_ENABLE_OUTPUT           = 9,
  ATOM_TRANSMITTER_ACTION_SETUP                   = 10,
  ATOM_TRANSMITTER_ACTION_SETUP_VSEMPH            = 11,
  ATOM_TRANSMITTER_ACTION_POWER_ON                = 12,
  ATOM_TRANSMITTER_ACTION_POWER_OFF               = 13,
पूर्ण;

// digfe_sel
क्रमागत atom_dig_transmitter_control_digfe_sel
अणु
  ATOM_TRANMSITTER_V6__DIGA_SEL                   = 0x01,
  ATOM_TRANMSITTER_V6__DIGB_SEL                   = 0x02,
  ATOM_TRANMSITTER_V6__DIGC_SEL                   = 0x04,
  ATOM_TRANMSITTER_V6__DIGD_SEL                   = 0x08,
  ATOM_TRANMSITTER_V6__DIGE_SEL                   = 0x10,
  ATOM_TRANMSITTER_V6__DIGF_SEL                   = 0x20,
  ATOM_TRANMSITTER_V6__DIGG_SEL                   = 0x40,
पूर्ण;


//ucHPDSel
क्रमागत atom_dig_transmitter_control_hpd_sel
अणु
  ATOM_TRANSMITTER_V6_NO_HPD_SEL                  = 0x00,
  ATOM_TRANSMITTER_V6_HPD1_SEL                    = 0x01,
  ATOM_TRANSMITTER_V6_HPD2_SEL                    = 0x02,
  ATOM_TRANSMITTER_V6_HPD3_SEL                    = 0x03,
  ATOM_TRANSMITTER_V6_HPD4_SEL                    = 0x04,
  ATOM_TRANSMITTER_V6_HPD5_SEL                    = 0x05,
  ATOM_TRANSMITTER_V6_HPD6_SEL                    = 0x06,
पूर्ण;

// ucDPLaneSet
क्रमागत atom_dig_transmitter_control_dplaneset
अणु
  DP_LANE_SET__0DB_0_4V                           = 0x00,
  DP_LANE_SET__0DB_0_6V                           = 0x01,
  DP_LANE_SET__0DB_0_8V                           = 0x02,
  DP_LANE_SET__0DB_1_2V                           = 0x03,
  DP_LANE_SET__3_5DB_0_4V                         = 0x08, 
  DP_LANE_SET__3_5DB_0_6V                         = 0x09,
  DP_LANE_SET__3_5DB_0_8V                         = 0x0a,
  DP_LANE_SET__6DB_0_4V                           = 0x10,
  DP_LANE_SET__6DB_0_6V                           = 0x11,
  DP_LANE_SET__9_5DB_0_4V                         = 0x18, 
पूर्ण;



/****************************************************************************/ 
// Structures used by ExternalEncoderControl V2.4
/****************************************************************************/   

काष्ठा बाह्यal_encoder_control_parameters_v2_4
अणु
  uपूर्णांक16_t pixelघड़ी_10khz;  // pixel घड़ी in 10Khz, valid when ucAction=SETUP/ENABLE_OUTPUT 
  uपूर्णांक8_t  config;            // indicate which encoder, and DP link rate when ucAction = SETUP/ENABLE_OUTPUT  
  uपूर्णांक8_t  action;            // 
  uपूर्णांक8_t  encodermode;       // encoder mode, only used when ucAction = SETUP/ENABLE_OUTPUT
  uपूर्णांक8_t  lanक्रमागत;           // lane number, only used when ucAction = SETUP/ENABLE_OUTPUT  
  uपूर्णांक8_t  bitpercolor;       // output bit per color, only valid when ucAction = SETUP/ENABLE_OUTPUT and ucEncodeMode= DP
  uपूर्णांक8_t  hpd_id;        
पूर्ण;


// ucAction
क्रमागत बाह्यal_encoder_control_action_def
अणु
  EXTERNAL_ENCODER_ACTION_V3_DISABLE_OUTPUT           = 0x00,
  EXTERNAL_ENCODER_ACTION_V3_ENABLE_OUTPUT            = 0x01,
  EXTERNAL_ENCODER_ACTION_V3_ENCODER_INIT             = 0x07,
  EXTERNAL_ENCODER_ACTION_V3_ENCODER_SETUP            = 0x0f,
  EXTERNAL_ENCODER_ACTION_V3_ENCODER_BLANKING_OFF     = 0x10,
  EXTERNAL_ENCODER_ACTION_V3_ENCODER_BLANKING         = 0x11,
  EXTERNAL_ENCODER_ACTION_V3_DACLOAD_DETECTION        = 0x12,
  EXTERNAL_ENCODER_ACTION_V3_DDC_SETUP                = 0x14,
पूर्ण;

// ucConfig
क्रमागत बाह्यal_encoder_control_v2_4_config_def
अणु
  EXTERNAL_ENCODER_CONFIG_V3_DPLINKRATE_MASK          = 0x03,
  EXTERNAL_ENCODER_CONFIG_V3_DPLINKRATE_1_62GHZ       = 0x00,
  EXTERNAL_ENCODER_CONFIG_V3_DPLINKRATE_2_70GHZ       = 0x01,
  EXTERNAL_ENCODER_CONFIG_V3_DPLINKRATE_5_40GHZ       = 0x02,
  EXTERNAL_ENCODER_CONFIG_V3_DPLINKRATE_3_24GHZ       = 0x03,  
  EXTERNAL_ENCODER_CONFIG_V3_ENCODER_SEL_MAKS         = 0x70,
  EXTERNAL_ENCODER_CONFIG_V3_ENCODER1                 = 0x00,
  EXTERNAL_ENCODER_CONFIG_V3_ENCODER2                 = 0x10,
  EXTERNAL_ENCODER_CONFIG_V3_ENCODER3                 = 0x20,
पूर्ण;

काष्ठा बाह्यal_encoder_control_ps_allocation_v2_4
अणु
  काष्ठा बाह्यal_encoder_control_parameters_v2_4 sExtEncoder;
  uपूर्णांक32_t reserved[2];
पूर्ण;


/* 
  ***************************************************************************
                           AMD ACPI Table
  
  *************************************************************************** 
*/   

काष्ठा amd_acpi_description_headerअणु
  uपूर्णांक32_t signature;
  uपूर्णांक32_t tableLength;      //Length
  uपूर्णांक8_t  revision;
  uपूर्णांक8_t  checksum;
  uपूर्णांक8_t  oemId[6];
  uपूर्णांक8_t  oemTableId[8];    //UINT64  OemTableId;
  uपूर्णांक32_t oemRevision;
  uपूर्णांक32_t creatorId;
  uपूर्णांक32_t creatorRevision;
पूर्ण;

काष्ठा uefi_acpi_vfctअणु
  काष्ठा   amd_acpi_description_header sheader;
  uपूर्णांक8_t  tableUUID[16];    //0x24
  uपूर्णांक32_t vbiosimageoffset; //0x34. Offset to the first GOP_VBIOS_CONTENT block from the beginning of the stucture.
  uपूर्णांक32_t lib1Imageoffset;  //0x38. Offset to the first GOP_LIB1_CONTENT block from the beginning of the stucture.
  uपूर्णांक32_t reserved[4];      //0x3C
पूर्ण;

काष्ठा vfct_image_headerअणु
  uपूर्णांक32_t  pcibus;          //0x4C
  uपूर्णांक32_t  pcidevice;       //0x50
  uपूर्णांक32_t  pcअगरunction;     //0x54
  uपूर्णांक16_t  venकरोrid;        //0x58
  uपूर्णांक16_t  deviceid;        //0x5A
  uपूर्णांक16_t  ssvid;           //0x5C
  uपूर्णांक16_t  ssid;            //0x5E
  uपूर्णांक32_t  revision;        //0x60
  uपूर्णांक32_t  imagelength;     //0x64
पूर्ण;


काष्ठा gop_vbios_content अणु
  काष्ठा vfct_image_header vbiosheader;
  uपूर्णांक8_t                  vbioscontent[1];
पूर्ण;

काष्ठा gop_lib1_content अणु
  काष्ठा vfct_image_header lib1header;
  uपूर्णांक8_t                  lib1content[1];
पूर्ण;



/* 
  ***************************************************************************
                   Scratch Register definitions
  Each number below indicates which scratch regiser request, Active and 
  Connect all share the same definitions as display_device_tag defines
  *************************************************************************** 
*/   

क्रमागत scratch_रेजिस्टर_defअणु
  ATOM_DEVICE_CONNECT_INFO_DEF      = 0,
  ATOM_BL_BRI_LEVEL_INFO_DEF        = 2,
  ATOM_ACTIVE_INFO_DEF              = 3,
  ATOM_LCD_INFO_DEF                 = 4,
  ATOM_DEVICE_REQ_INFO_DEF          = 5,
  ATOM_ACC_CHANGE_INFO_DEF          = 6,
  ATOM_PRE_OS_MODE_INFO_DEF         = 7,
  ATOM_PRE_OS_ASSERTION_DEF      = 8,    //For GOP to record a 32bit निश्चितion code, this is enabled by शेष in prodution GOP drivers.
  ATOM_INTERNAL_TIMER_INFO_DEF      = 10,
पूर्ण;

क्रमागत scratch_device_connect_info_bit_defअणु
  ATOM_DISPLAY_LCD1_CONNECT           =0x0002,
  ATOM_DISPLAY_DFP1_CONNECT           =0x0008,
  ATOM_DISPLAY_DFP2_CONNECT           =0x0080,
  ATOM_DISPLAY_DFP3_CONNECT           =0x0200,
  ATOM_DISPLAY_DFP4_CONNECT           =0x0400,
  ATOM_DISPLAY_DFP5_CONNECT           =0x0800,
  ATOM_DISPLAY_DFP6_CONNECT           =0x0040,
  ATOM_DISPLAY_DFPx_CONNECT           =0x0ec8,
  ATOM_CONNECT_INFO_DEVICE_MASK       =0x0fff,
पूर्ण;

क्रमागत scratch_bl_bri_level_info_bit_defअणु
  ATOM_CURRENT_BL_LEVEL_SHIFT         =0x8,
#अगर_अघोषित _H2INC
  ATOM_CURRENT_BL_LEVEL_MASK          =0x0000ff00,
  ATOM_DEVICE_DPMS_STATE              =0x00010000,
#पूर्ण_अगर
पूर्ण;

क्रमागत scratch_active_info_bits_defअणु
  ATOM_DISPLAY_LCD1_ACTIVE            =0x0002,
  ATOM_DISPLAY_DFP1_ACTIVE            =0x0008,
  ATOM_DISPLAY_DFP2_ACTIVE            =0x0080,
  ATOM_DISPLAY_DFP3_ACTIVE            =0x0200,
  ATOM_DISPLAY_DFP4_ACTIVE            =0x0400,
  ATOM_DISPLAY_DFP5_ACTIVE            =0x0800,
  ATOM_DISPLAY_DFP6_ACTIVE            =0x0040,
  ATOM_ACTIVE_INFO_DEVICE_MASK        =0x0fff,
पूर्ण;

क्रमागत scratch_device_req_info_bits_defअणु
  ATOM_DISPLAY_LCD1_REQ               =0x0002,
  ATOM_DISPLAY_DFP1_REQ               =0x0008,
  ATOM_DISPLAY_DFP2_REQ               =0x0080,
  ATOM_DISPLAY_DFP3_REQ               =0x0200,
  ATOM_DISPLAY_DFP4_REQ               =0x0400,
  ATOM_DISPLAY_DFP5_REQ               =0x0800,
  ATOM_DISPLAY_DFP6_REQ               =0x0040,
  ATOM_REQ_INFO_DEVICE_MASK           =0x0fff,
पूर्ण;

क्रमागत scratch_acc_change_info_bitshअगरt_defअणु
  ATOM_ACC_CHANGE_ACC_MODE_SHIFT    =4,
  ATOM_ACC_CHANGE_LID_STATUS_SHIFT  =6,
पूर्ण;

क्रमागत scratch_acc_change_info_bits_defअणु
  ATOM_ACC_CHANGE_ACC_MODE          =0x00000010,
  ATOM_ACC_CHANGE_LID_STATUS        =0x00000040,
पूर्ण;

क्रमागत scratch_pre_os_mode_info_bits_defअणु
  ATOM_PRE_OS_MODE_MASK             =0x00000003,
  ATOM_PRE_OS_MODE_VGA              =0x00000000,
  ATOM_PRE_OS_MODE_VESA             =0x00000001,
  ATOM_PRE_OS_MODE_GOP              =0x00000002,
  ATOM_PRE_OS_MODE_PIXEL_DEPTH      =0x0000000C,
  ATOM_PRE_OS_MODE_PIXEL_FORMAT_MASK=0x000000F0,
  ATOM_PRE_OS_MODE_8BIT_PAL_EN      =0x00000100,
  ATOM_ASIC_INIT_COMPLETE           =0x00000200,
#अगर_अघोषित _H2INC
  ATOM_PRE_OS_MODE_NUMBER_MASK      =0xFFFF0000,
#पूर्ण_अगर
पूर्ण;



/* 
  ***************************************************************************
                       ATOM firmware ID header file
              !! Please keep it at end of the atomfirmware.h !!
  *************************************************************************** 
*/   
#समावेश "atomfirmwareid.h"
#आशय pack()

#पूर्ण_अगर

