<शैली गुरु>
/*
 * Copyright 2016 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */
// CZ Ucode Loading Definitions
#अगर_अघोषित SMU_UCODE_XFER_CZ_H
#घोषणा SMU_UCODE_XFER_CZ_H

#घोषणा NUM_JOBLIST_ENTRIES      32

#घोषणा TASK_TYPE_NO_ACTION      0
#घोषणा TASK_TYPE_UCODE_LOAD     1
#घोषणा TASK_TYPE_UCODE_SAVE     2
#घोषणा TASK_TYPE_REG_LOAD       3
#घोषणा TASK_TYPE_REG_SAVE       4
#घोषणा TASK_TYPE_INITIALIZE     5

#घोषणा TASK_ARG_REG_SMCIND      0
#घोषणा TASK_ARG_REG_MMIO        1
#घोषणा TASK_ARG_REG_FCH         2
#घोषणा TASK_ARG_REG_UNB         3

#घोषणा TASK_ARG_INIT_MM_PWR_LOG 0
#घोषणा TASK_ARG_INIT_CLK_TABLE  1

#घोषणा JOB_GFX_SAVE             0
#घोषणा JOB_GFX_RESTORE          1
#घोषणा JOB_FCH_SAVE             2
#घोषणा JOB_FCH_RESTORE          3
#घोषणा JOB_UNB_SAVE             4
#घोषणा JOB_UNB_RESTORE          5
#घोषणा JOB_GMC_SAVE             6
#घोषणा JOB_GMC_RESTORE          7
#घोषणा JOB_GNB_SAVE             8
#घोषणा JOB_GNB_RESTORE          9

#घोषणा IGNORE_JOB               0xff
#घोषणा END_OF_TASK_LIST     (uपूर्णांक16_t)0xffff

// Size of DRAM regions (in bytes) requested by SMU:
#घोषणा SMU_DRAM_REQ_MM_PWR_LOG 48 

#घोषणा UCODE_ID_SDMA0           0
#घोषणा UCODE_ID_SDMA1           1
#घोषणा UCODE_ID_CP_CE           2
#घोषणा UCODE_ID_CP_PFP          3
#घोषणा UCODE_ID_CP_ME           4
#घोषणा UCODE_ID_CP_MEC_JT1      5
#घोषणा UCODE_ID_CP_MEC_JT2      6
#घोषणा UCODE_ID_GMCON_RENG      7
#घोषणा UCODE_ID_RLC_G           8
#घोषणा UCODE_ID_RLC_SCRATCH     9
#घोषणा UCODE_ID_RLC_SRM_ARAM    10
#घोषणा UCODE_ID_RLC_SRM_DRAM    11
#घोषणा UCODE_ID_DMCU_ERAM       12
#घोषणा UCODE_ID_DMCU_IRAM       13

#घोषणा UCODE_ID_SDMA0_MASK           0x00000001       
#घोषणा UCODE_ID_SDMA1_MASK           0x00000002        
#घोषणा UCODE_ID_CP_CE_MASK           0x00000004      
#घोषणा UCODE_ID_CP_PFP_MASK          0x00000008         
#घोषणा UCODE_ID_CP_ME_MASK           0x00000010          
#घोषणा UCODE_ID_CP_MEC_JT1_MASK      0x00000020             
#घोषणा UCODE_ID_CP_MEC_JT2_MASK      0x00000040          
#घोषणा UCODE_ID_GMCON_RENG_MASK      0x00000080            
#घोषणा UCODE_ID_RLC_G_MASK           0x00000100           
#घोषणा UCODE_ID_RLC_SCRATCH_MASK     0x00000200         
#घोषणा UCODE_ID_RLC_SRM_ARAM_MASK    0x00000400                
#घोषणा UCODE_ID_RLC_SRM_DRAM_MASK    0x00000800                 
#घोषणा UCODE_ID_DMCU_ERAM_MASK       0x00001000             
#घोषणा UCODE_ID_DMCU_IRAM_MASK       0x00002000              

#घोषणा UCODE_ID_SDMA0_SIZE_BYTE           10368        
#घोषणा UCODE_ID_SDMA1_SIZE_BYTE           10368          
#घोषणा UCODE_ID_CP_CE_SIZE_BYTE           8576        
#घोषणा UCODE_ID_CP_PFP_SIZE_BYTE          16768           
#घोषणा UCODE_ID_CP_ME_SIZE_BYTE           16768            
#घोषणा UCODE_ID_CP_MEC_JT1_SIZE_BYTE      384               
#घोषणा UCODE_ID_CP_MEC_JT2_SIZE_BYTE      384            
#घोषणा UCODE_ID_GMCON_RENG_SIZE_BYTE      4096              
#घोषणा UCODE_ID_RLC_G_SIZE_BYTE           2048             
#घोषणा UCODE_ID_RLC_SCRATCH_SIZE_BYTE     132           
#घोषणा UCODE_ID_RLC_SRM_ARAM_SIZE_BYTE    8192                  
#घोषणा UCODE_ID_RLC_SRM_DRAM_SIZE_BYTE    4096                   
#घोषणा UCODE_ID_DMCU_ERAM_SIZE_BYTE       24576               
#घोषणा UCODE_ID_DMCU_IRAM_SIZE_BYTE       1024                 

#घोषणा NUM_UCODES               14

प्रकार काष्ठा अणु
	uपूर्णांक32_t high;
	uपूर्णांक32_t low;
पूर्ण data_64_t;

काष्ठा SMU_Task अणु
    uपूर्णांक8_t type;
    uपूर्णांक8_t arg;
    uपूर्णांक16_t next;
    data_64_t addr;
    uपूर्णांक32_t size_bytes;
पूर्ण;
प्रकार काष्ठा SMU_Task SMU_Task;

काष्ठा TOC अणु
    uपूर्णांक8_t JobList[NUM_JOBLIST_ENTRIES];
    SMU_Task tasks[1];
पूर्ण;

// META DATA COMMAND Definitions
#घोषणा METADATA_CMD_MODE0         0x00000103 
#घोषणा METADATA_CMD_MODE1         0x00000113 
#घोषणा METADATA_CMD_MODE2         0x00000123 
#घोषणा METADATA_CMD_MODE3         0x00000133
#घोषणा METADATA_CMD_DELAY         0x00000203
#घोषणा METADATA_CMD_CHNG_REGSPACE 0x00000303
#घोषणा METADATA_PERFORM_ON_SAVE   0x00001000
#घोषणा METADATA_PERFORM_ON_LOAD   0x00002000
#घोषणा METADATA_CMD_ARG_MASK      0xFFFF0000
#घोषणा METADATA_CMD_ARG_SHIFT     16

// Simple रेजिस्टर addr/data fields
काष्ठा SMU_MetaData_Mode0 अणु
    uपूर्णांक32_t रेजिस्टर_address;
    uपूर्णांक32_t रेजिस्टर_data;
पूर्ण;
प्रकार काष्ठा SMU_MetaData_Mode0 SMU_MetaData_Mode0;

// Register addr/data with mask
काष्ठा SMU_MetaData_Mode1 अणु
    uपूर्णांक32_t रेजिस्टर_address;
    uपूर्णांक32_t रेजिस्टर_mask;
    uपूर्णांक32_t रेजिस्टर_data;
पूर्ण;
प्रकार काष्ठा SMU_MetaData_Mode1 SMU_MetaData_Mode1;

काष्ठा SMU_MetaData_Mode2 अणु
    uपूर्णांक32_t रेजिस्टर_address;
    uपूर्णांक32_t रेजिस्टर_mask;
    uपूर्णांक32_t target_value;
पूर्ण;
प्रकार काष्ठा SMU_MetaData_Mode2 SMU_MetaData_Mode2;

// Always ग_लिखो data (even on a save operation)
काष्ठा SMU_MetaData_Mode3 अणु
    uपूर्णांक32_t रेजिस्टर_address;
    uपूर्णांक32_t रेजिस्टर_mask;
    uपूर्णांक32_t रेजिस्टर_data;
पूर्ण;
प्रकार काष्ठा SMU_MetaData_Mode3 SMU_MetaData_Mode3;

#पूर्ण_अगर
