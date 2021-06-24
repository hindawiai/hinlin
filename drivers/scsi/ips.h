<शैली गुरु>
/*****************************************************************************/
/* ips.h -- driver क्रम the Adaptec / IBM ServeRAID controller                */
/*                                                                           */
/* Written By: Keith Mitchell, IBM Corporation                               */
/*             Jack Hammer, Adaptec, Inc.                                    */
/*             David Jeffery, Adaptec, Inc.                                  */
/*                                                                           */
/* Copyright (C) 1999 IBM Corporation                                        */
/* Copyright (C) 2003 Adaptec, Inc.                                          */
/*                                                                           */
/* This program is मुक्त software; you can redistribute it and/or modअगरy      */
/* it under the terms of the GNU General Public License as published by      */
/* the Free Software Foundation; either version 2 of the License, or         */
/* (at your option) any later version.                                       */
/*                                                                           */
/* This program is distributed in the hope that it will be useful,           */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             */
/* GNU General Public License क्रम more details.                              */
/*                                                                           */
/* NO WARRANTY                                                               */
/* THE PROGRAM IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OR        */
/* CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED INCLUDING, WITHOUT      */
/* LIMITATION, ANY WARRANTIES OR CONDITIONS OF TITLE, NON-INFRINGEMENT,      */
/* MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Each Recipient is    */
/* solely responsible क्रम determining the appropriateness of using and       */
/* distributing the Program and assumes all risks associated with its        */
/* exercise of rights under this Agreement, including but not limited to     */
/* the risks and costs of program errors, damage to or loss of data,         */
/* programs or equipment, and unavailability or पूर्णांकerruption of operations.  */
/*                                                                           */
/* DISCLAIMER OF LIABILITY                                                   */
/* NEITHER RECIPIENT NOR ANY CONTRIBUTORS SHALL HAVE ANY LIABILITY FOR ANY   */
/* सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL        */
/* DAMAGES (INCLUDING WITHOUT LIMITATION LOST PROFITS), HOWEVER CAUSED AND   */
/* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR     */
/* TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE    */
/* USE OR DISTRIBUTION OF THE PROGRAM OR THE EXERCISE OF ANY RIGHTS GRANTED  */
/* HEREUNDER, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGES             */
/*                                                                           */
/* You should have received a copy of the GNU General Public License         */
/* aदीर्घ with this program; अगर not, ग_लिखो to the Free Software               */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */
/*                                                                           */
/* Bugs/Comments/Suggestions should be mailed to:                            */
/*      ipslinux@adaptec.com                                                 */
/*                                                                           */
/*****************************************************************************/

#अगर_अघोषित _IPS_H_
   #घोषणा _IPS_H_

#समावेश <linux/nmi.h>
#समावेश <linux/uaccess.h>
   #समावेश <यंत्र/पन.स>

   /*
    * Some handy macros
    */
   #घोषणा IPS_HA(x)                   ((ips_ha_t *) x->hostdata)
   #घोषणा IPS_COMMAND_ID(ha, scb)     (पूर्णांक) (scb - ha->scbs)
   #घोषणा IPS_IS_TROMBONE(ha)         (((ha->pcidev->device == IPS_DEVICEID_COPPERHEAD) && \
                                         (ha->pcidev->revision >= IPS_REVID_TROMBONE32) && \
                                         (ha->pcidev->revision <= IPS_REVID_TROMBONE64)) ? 1 : 0)
   #घोषणा IPS_IS_CLARINET(ha)         (((ha->pcidev->device == IPS_DEVICEID_COPPERHEAD) && \
                                         (ha->pcidev->revision >= IPS_REVID_CLARINETP1) && \
                                         (ha->pcidev->revision <= IPS_REVID_CLARINETP3)) ? 1 : 0)
   #घोषणा IPS_IS_MORPHEUS(ha)         (ha->pcidev->device == IPS_DEVICEID_MORPHEUS)
   #घोषणा IPS_IS_MARCO(ha)            (ha->pcidev->device == IPS_DEVICEID_MARCO)
   #घोषणा IPS_USE_I2O_DELIVER(ha)     ((IPS_IS_MORPHEUS(ha) || \
                                         (IPS_IS_TROMBONE(ha) && \
                                          (ips_क्रमce_i2o))) ? 1 : 0)
   #घोषणा IPS_USE_MEMIO(ha)           ((IPS_IS_MORPHEUS(ha) || \
                                         ((IPS_IS_TROMBONE(ha) || IPS_IS_CLARINET(ha)) && \
                                          (ips_क्रमce_memio))) ? 1 : 0)

    #घोषणा IPS_HAS_ENH_SGLIST(ha)    (IPS_IS_MORPHEUS(ha) || IPS_IS_MARCO(ha))
    #घोषणा IPS_USE_ENH_SGLIST(ha)    ((ha)->flags & IPS_HA_ENH_SG)
    #घोषणा IPS_SGLIST_SIZE(ha)       (IPS_USE_ENH_SGLIST(ha) ? \
                                         माप(IPS_ENH_SG_LIST) : माप(IPS_STD_SG_LIST))

  #घोषणा IPS_PRINTK(level, pcidev, क्रमmat, arg...)                 \
            dev_prपूर्णांकk(level , &((pcidev)->dev) , क्रमmat , ## arg)

   #घोषणा MDELAY(n)			\
	करो अणु				\
		mdelay(n);		\
		touch_nmi_watchकरोg();	\
	पूर्ण जबतक (0)

   #अगर_अघोषित min
      #घोषणा min(x,y) ((x) < (y) ? x : y)
   #पूर्ण_अगर

   #अगर_अघोषित __iomem       /* For clean compiles in earlier kernels without __iomem annotations */
      #घोषणा __iomem
   #पूर्ण_अगर

   /*
    * Adapter address map equates
    */
   #घोषणा IPS_REG_HISR                 0x08    /* Host Interrupt Status Reg   */
   #घोषणा IPS_REG_CCSAR                0x10    /* Cmd Channel System Addr Reg */
   #घोषणा IPS_REG_CCCR                 0x14    /* Cmd Channel Control Reg     */
   #घोषणा IPS_REG_SQHR                 0x20    /* Status Q Head Reg           */
   #घोषणा IPS_REG_SQTR                 0x24    /* Status Q Tail Reg           */
   #घोषणा IPS_REG_SQER                 0x28    /* Status Q End Reg            */
   #घोषणा IPS_REG_SQSR                 0x2C    /* Status Q Start Reg          */
   #घोषणा IPS_REG_SCPR                 0x05    /* Subप्रणाली control port reg  */
   #घोषणा IPS_REG_ISPR                 0x06    /* पूर्णांकerrupt status port reg   */
   #घोषणा IPS_REG_CBSP                 0x07    /* CBSP रेजिस्टर               */
   #घोषणा IPS_REG_FLAP                 0x18    /* Flash address port          */
   #घोषणा IPS_REG_FLDP                 0x1C    /* Flash data port             */
   #घोषणा IPS_REG_NDAE                 0x38    /* Anaconda 64 NDAE Register   */
   #घोषणा IPS_REG_I2O_INMSGQ           0x40    /* I2O Inbound Message Queue   */
   #घोषणा IPS_REG_I2O_OUTMSGQ          0x44    /* I2O Outbound Message Queue  */
   #घोषणा IPS_REG_I2O_HIR              0x30    /* I2O Interrupt Status        */
   #घोषणा IPS_REG_I960_IDR             0x20    /* i960 Inbound Doorbell       */
   #घोषणा IPS_REG_I960_MSG0            0x18    /* i960 Outbound Reg 0         */
   #घोषणा IPS_REG_I960_MSG1            0x1C    /* i960 Outbound Reg 1         */
   #घोषणा IPS_REG_I960_OIMR            0x34    /* i960 Oubound Int Mask Reg   */

   /*
    * Adapter रेजिस्टर bit equates
    */
   #घोषणा IPS_BIT_GHI                  0x04    /* HISR General Host Interrupt */
   #घोषणा IPS_BIT_SQO                  0x02    /* HISR Status Q Overflow      */
   #घोषणा IPS_BIT_SCE                  0x01    /* HISR Status Channel Enqueue */
   #घोषणा IPS_BIT_SEM                  0x08    /* CCCR Semaphore Bit          */
   #घोषणा IPS_BIT_ILE                  0x10    /* CCCR ILE Bit                */
   #घोषणा IPS_BIT_START_CMD            0x101A  /* CCCR Start Command Channel  */
   #घोषणा IPS_BIT_START_STOP           0x0002  /* CCCR Start/Stop Bit         */
   #घोषणा IPS_BIT_RST                  0x80    /* SCPR Reset Bit              */
   #घोषणा IPS_BIT_EBM                  0x02    /* SCPR Enable Bus Master      */
   #घोषणा IPS_BIT_EI                   0x80    /* HISR Enable Interrupts      */
   #घोषणा IPS_BIT_OP                   0x01    /* OP bit in CBSP              */
   #घोषणा IPS_BIT_I2O_OPQI             0x08    /* General Host Interrupt      */
   #घोषणा IPS_BIT_I960_MSG0I           0x01    /* Message Register 0 Interrupt*/
   #घोषणा IPS_BIT_I960_MSG1I           0x02    /* Message Register 1 Interrupt*/

   /*
    * Adapter Command ID Equates
    */
   #घोषणा IPS_CMD_GET_LD_INFO          0x19
   #घोषणा IPS_CMD_GET_SUBSYS           0x40
   #घोषणा IPS_CMD_READ_CONF            0x38
   #घोषणा IPS_CMD_RW_NVRAM_PAGE        0xBC
   #घोषणा IPS_CMD_READ                 0x02
   #घोषणा IPS_CMD_WRITE                0x03
   #घोषणा IPS_CMD_FFDC                 0xD7
   #घोषणा IPS_CMD_ENQUIRY              0x05
   #घोषणा IPS_CMD_FLUSH                0x0A
   #घोषणा IPS_CMD_READ_SG              0x82
   #घोषणा IPS_CMD_WRITE_SG             0x83
   #घोषणा IPS_CMD_DCDB                 0x04
   #घोषणा IPS_CMD_DCDB_SG              0x84
   #घोषणा IPS_CMD_EXTENDED_DCDB 	    0x95
   #घोषणा IPS_CMD_EXTENDED_DCDB_SG	    0x96
   #घोषणा IPS_CMD_CONFIG_SYNC          0x58
   #घोषणा IPS_CMD_ERROR_TABLE          0x17
   #घोषणा IPS_CMD_DOWNLOAD             0x20
   #घोषणा IPS_CMD_RW_BIOSFW            0x22
   #घोषणा IPS_CMD_GET_VERSION_INFO     0xC6
   #घोषणा IPS_CMD_RESET_CHANNEL        0x1A

   /*
    * Adapter Equates
    */
   #घोषणा IPS_CSL                      0xFF
   #घोषणा IPS_POCL                     0x30
   #घोषणा IPS_NORM_STATE               0x00
   #घोषणा IPS_MAX_ADAPTER_TYPES        3
   #घोषणा IPS_MAX_ADAPTERS             16
   #घोषणा IPS_MAX_IOCTL                1
   #घोषणा IPS_MAX_IOCTL_QUEUE          8
   #घोषणा IPS_MAX_QUEUE                128
   #घोषणा IPS_BLKSIZE                  512
   #घोषणा IPS_MAX_SG                   17
   #घोषणा IPS_MAX_LD                   8
   #घोषणा IPS_MAX_CHANNELS             4
   #घोषणा IPS_MAX_TARGETS              15
   #घोषणा IPS_MAX_CHUNKS               16
   #घोषणा IPS_MAX_CMDS                 128
   #घोषणा IPS_MAX_XFER                 0x10000
   #घोषणा IPS_NVRAM_P5_SIG             0xFFDDBB99
   #घोषणा IPS_MAX_POST_BYTES           0x02
   #घोषणा IPS_MAX_CONFIG_BYTES         0x02
   #घोषणा IPS_GOOD_POST_STATUS         0x80
   #घोषणा IPS_SEM_TIMEOUT              2000
   #घोषणा IPS_IOCTL_COMMAND            0x0D
   #घोषणा IPS_INTR_ON                  0
   #घोषणा IPS_INTR_IORL                1
   #घोषणा IPS_FFDC                     99
   #घोषणा IPS_ADAPTER_ID               0xF
   #घोषणा IPS_VENDORID_IBM             0x1014
   #घोषणा IPS_VENDORID_ADAPTEC         0x9005
   #घोषणा IPS_DEVICEID_COPPERHEAD      0x002E
   #घोषणा IPS_DEVICEID_MORPHEUS        0x01BD
   #घोषणा IPS_DEVICEID_MARCO           0x0250
   #घोषणा IPS_SUBDEVICEID_4M           0x01BE
   #घोषणा IPS_SUBDEVICEID_4L           0x01BF
   #घोषणा IPS_SUBDEVICEID_4MX          0x0208
   #घोषणा IPS_SUBDEVICEID_4LX          0x020E
   #घोषणा IPS_SUBDEVICEID_5I2          0x0259
   #घोषणा IPS_SUBDEVICEID_5I1          0x0258
   #घोषणा IPS_SUBDEVICEID_6M           0x0279
   #घोषणा IPS_SUBDEVICEID_6I           0x028C
   #घोषणा IPS_SUBDEVICEID_7k           0x028E
   #घोषणा IPS_SUBDEVICEID_7M           0x028F
   #घोषणा IPS_IOCTL_SIZE               8192
   #घोषणा IPS_STATUS_SIZE              4
   #घोषणा IPS_STATUS_Q_SIZE            (IPS_MAX_CMDS+1) * IPS_STATUS_SIZE
   #घोषणा IPS_IMAGE_SIZE               500 * 1024
   #घोषणा IPS_MEMMAP_SIZE              128
   #घोषणा IPS_ONE_MSEC                 1
   #घोषणा IPS_ONE_SEC                  1000

   /*
    * Geometry Settings
    */
   #घोषणा IPS_COMP_HEADS               128
   #घोषणा IPS_COMP_SECTORS             32
   #घोषणा IPS_NORM_HEADS               254
   #घोषणा IPS_NORM_SECTORS             63

   /*
    * Adapter Basic Status Codes
    */
   #घोषणा IPS_BASIC_STATUS_MASK        0xFF
   #घोषणा IPS_GSC_STATUS_MASK          0x0F
   #घोषणा IPS_CMD_SUCCESS              0x00
   #घोषणा IPS_CMD_RECOVERED_ERROR      0x01
   #घोषणा IPS_INVAL_OPCO               0x03
   #घोषणा IPS_INVAL_CMD_BLK            0x04
   #घोषणा IPS_INVAL_PARM_BLK           0x05
   #घोषणा IPS_BUSY                     0x08
   #घोषणा IPS_CMD_CMPLT_WERROR         0x0C
   #घोषणा IPS_LD_ERROR                 0x0D
   #घोषणा IPS_CMD_TIMEOUT              0x0E
   #घोषणा IPS_PHYS_DRV_ERROR           0x0F

   /*
    * Adapter Extended Status Equates
    */
   #घोषणा IPS_ERR_SEL_TO               0xF0
   #घोषणा IPS_ERR_OU_RUN               0xF2
   #घोषणा IPS_ERR_HOST_RESET           0xF7
   #घोषणा IPS_ERR_DEV_RESET            0xF8
   #घोषणा IPS_ERR_RECOVERY             0xFC
   #घोषणा IPS_ERR_CKCOND               0xFF

   /*
    * Operating System Defines
    */
   #घोषणा IPS_OS_WINDOWS_NT            0x01
   #घोषणा IPS_OS_NETWARE               0x02
   #घोषणा IPS_OS_OPENSERVER            0x03
   #घोषणा IPS_OS_UNIXWARE              0x04
   #घोषणा IPS_OS_SOLARIS               0x05
   #घोषणा IPS_OS_OS2                   0x06
   #घोषणा IPS_OS_LINUX                 0x07
   #घोषणा IPS_OS_FREEBSD               0x08

   /*
    * Adapter Revision ID's
    */
   #घोषणा IPS_REVID_SERVERAID          0x02
   #घोषणा IPS_REVID_NAVAJO             0x03
   #घोषणा IPS_REVID_SERVERAID2         0x04
   #घोषणा IPS_REVID_CLARINETP1         0x05
   #घोषणा IPS_REVID_CLARINETP2         0x07
   #घोषणा IPS_REVID_CLARINETP3         0x0D
   #घोषणा IPS_REVID_TROMBONE32         0x0F
   #घोषणा IPS_REVID_TROMBONE64         0x10

   /*
    * NVRAM Page 5 Adapter Defines
    */
   #घोषणा IPS_ADTYPE_SERVERAID         0x01
   #घोषणा IPS_ADTYPE_SERVERAID2        0x02
   #घोषणा IPS_ADTYPE_NAVAJO            0x03
   #घोषणा IPS_ADTYPE_KIOWA             0x04
   #घोषणा IPS_ADTYPE_SERVERAID3        0x05
   #घोषणा IPS_ADTYPE_SERVERAID3L       0x06
   #घोषणा IPS_ADTYPE_SERVERAID4H       0x07
   #घोषणा IPS_ADTYPE_SERVERAID4M       0x08
   #घोषणा IPS_ADTYPE_SERVERAID4L       0x09
   #घोषणा IPS_ADTYPE_SERVERAID4MX      0x0A
   #घोषणा IPS_ADTYPE_SERVERAID4LX      0x0B
   #घोषणा IPS_ADTYPE_SERVERAID5I2      0x0C
   #घोषणा IPS_ADTYPE_SERVERAID5I1      0x0D
   #घोषणा IPS_ADTYPE_SERVERAID6M       0x0E
   #घोषणा IPS_ADTYPE_SERVERAID6I       0x0F
   #घोषणा IPS_ADTYPE_SERVERAID7t       0x10
   #घोषणा IPS_ADTYPE_SERVERAID7k       0x11
   #घोषणा IPS_ADTYPE_SERVERAID7M       0x12

   /*
    * Adapter Command/Status Packet Definitions
    */
   #घोषणा IPS_SUCCESS                  0x01 /* Successfully completed       */
   #घोषणा IPS_SUCCESS_IMM              0x02 /* Success - Immediately        */
   #घोषणा IPS_FAILURE                  0x04 /* Completed with Error         */

   /*
    * Logical Drive Equates
    */
   #घोषणा IPS_LD_OFFLINE               0x02
   #घोषणा IPS_LD_OKAY                  0x03
   #घोषणा IPS_LD_FREE                  0x00
   #घोषणा IPS_LD_SYS                   0x06
   #घोषणा IPS_LD_CRS                   0x24

   /*
    * DCDB Table Equates
    */
   #घोषणा IPS_NO_DISCONNECT            0x00
   #घोषणा IPS_DISCONNECT_ALLOWED       0x80
   #घोषणा IPS_NO_AUTO_REQSEN           0x40
   #घोषणा IPS_DATA_NONE                0x00
   #घोषणा IPS_DATA_UNK                 0x00
   #घोषणा IPS_DATA_IN                  0x01
   #घोषणा IPS_DATA_OUT                 0x02
   #घोषणा IPS_TRANSFER64K              0x08
   #घोषणा IPS_NOTIMEOUT                0x00
   #घोषणा IPS_TIMEOUT10                0x10
   #घोषणा IPS_TIMEOUT60                0x20
   #घोषणा IPS_TIMEOUT20M               0x30

   /*
    * SCSI Inquiry Data Flags
    */
   #घोषणा IPS_SCSI_INQ_TYPE_DASD       0x00
   #घोषणा IPS_SCSI_INQ_TYPE_PROCESSOR  0x03
   #घोषणा IPS_SCSI_INQ_LU_CONNECTED    0x00
   #घोषणा IPS_SCSI_INQ_RD_REV2         0x02
   #घोषणा IPS_SCSI_INQ_REV2            0x02
   #घोषणा IPS_SCSI_INQ_REV3            0x03
   #घोषणा IPS_SCSI_INQ_Address16       0x01
   #घोषणा IPS_SCSI_INQ_Address32       0x02
   #घोषणा IPS_SCSI_INQ_MedChanger      0x08
   #घोषणा IPS_SCSI_INQ_MultiPort       0x10
   #घोषणा IPS_SCSI_INQ_EncServ         0x40
   #घोषणा IPS_SCSI_INQ_SoftReset       0x01
   #घोषणा IPS_SCSI_INQ_CmdQue          0x02
   #घोषणा IPS_SCSI_INQ_Linked          0x08
   #घोषणा IPS_SCSI_INQ_Sync            0x10
   #घोषणा IPS_SCSI_INQ_WBus16          0x20
   #घोषणा IPS_SCSI_INQ_WBus32          0x40
   #घोषणा IPS_SCSI_INQ_RelAdr          0x80

   /*
    * SCSI Request Sense Data Flags
    */
   #घोषणा IPS_SCSI_REQSEN_VALID        0x80
   #घोषणा IPS_SCSI_REQSEN_CURRENT_ERR  0x70
   #घोषणा IPS_SCSI_REQSEN_NO_SENSE     0x00

   /*
    * SCSI Mode Page Equates
    */
   #घोषणा IPS_SCSI_MP3_SoftSector      0x01
   #घोषणा IPS_SCSI_MP3_HardSector      0x02
   #घोषणा IPS_SCSI_MP3_Removeable      0x04
   #घोषणा IPS_SCSI_MP3_AllocateSurface 0x08

   /*
    * HA Flags
    */

   #घोषणा IPS_HA_ENH_SG                0x1

   /*
    * SCB Flags
    */
   #घोषणा IPS_SCB_MAP_SG               0x00008
   #घोषणा IPS_SCB_MAP_SINGLE           0X00010

   /*
    * Passthru stuff
    */
   #घोषणा IPS_COPPUSRCMD              (('C'<<8) | 65)
   #घोषणा IPS_COPPIOCCMD              (('C'<<8) | 66)
   #घोषणा IPS_NUMCTRLS                (('C'<<8) | 68)
   #घोषणा IPS_CTRLINFO                (('C'<<8) | 69)

   /* flashing defines */
   #घोषणा IPS_FW_IMAGE                0x00
   #घोषणा IPS_BIOS_IMAGE              0x01
   #घोषणा IPS_WRITE_FW                0x01
   #घोषणा IPS_WRITE_BIOS              0x02
   #घोषणा IPS_ERASE_BIOS              0x03
   #घोषणा IPS_BIOS_HEADER             0xC0

   /* समय oriented stuff */
   #घोषणा IPS_SECS_8HOURS              28800

   /*
    * Scsi_Host Template
    */
   अटल पूर्णांक ips_biosparam(काष्ठा scsi_device *sdev, काष्ठा block_device *bdev,
		sector_t capacity, पूर्णांक geom[]);
   अटल पूर्णांक ips_slave_configure(काष्ठा scsi_device *SDptr);

/*
 * Raid Command Formats
 */
प्रकार काष्ठा अणु
   uपूर्णांक8_t  op_code;
   uपूर्णांक8_t  command_id;
   uपूर्णांक8_t  log_drv;
   uपूर्णांक8_t  sg_count;
   uपूर्णांक32_t lba;
   uपूर्णांक32_t sg_addr;
   uपूर्णांक16_t sector_count;
   uपूर्णांक8_t  segment_4G;
   uपूर्णांक8_t  enhanced_sg;
   uपूर्णांक32_t ccsar;
   uपूर्णांक32_t cccr;
पूर्ण IPS_IO_CMD, *PIPS_IO_CMD;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  op_code;
   uपूर्णांक8_t  command_id;
   uपूर्णांक16_t reserved;
   uपूर्णांक32_t reserved2;
   uपूर्णांक32_t buffer_addr;
   uपूर्णांक32_t reserved3;
   uपूर्णांक32_t ccsar;
   uपूर्णांक32_t cccr;
पूर्ण IPS_LD_CMD, *PIPS_LD_CMD;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  op_code;
   uपूर्णांक8_t  command_id;
   uपूर्णांक8_t  reserved;
   uपूर्णांक8_t  reserved2;
   uपूर्णांक32_t reserved3;
   uपूर्णांक32_t buffer_addr;
   uपूर्णांक32_t reserved4;
पूर्ण IPS_IOCTL_CMD, *PIPS_IOCTL_CMD;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  op_code;
   uपूर्णांक8_t  command_id;
   uपूर्णांक8_t  channel;
   uपूर्णांक8_t  reserved3;
   uपूर्णांक8_t  reserved4;
   uपूर्णांक8_t  reserved5;
   uपूर्णांक8_t  reserved6;
   uपूर्णांक8_t  reserved7;
   uपूर्णांक8_t  reserved8;
   uपूर्णांक8_t  reserved9;
   uपूर्णांक8_t  reserved10;
   uपूर्णांक8_t  reserved11;
   uपूर्णांक8_t  reserved12;
   uपूर्णांक8_t  reserved13;
   uपूर्णांक8_t  reserved14;
   uपूर्णांक8_t  adapter_flag;
पूर्ण IPS_RESET_CMD, *PIPS_RESET_CMD;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  op_code;
   uपूर्णांक8_t  command_id;
   uपूर्णांक16_t reserved;
   uपूर्णांक32_t reserved2;
   uपूर्णांक32_t dcdb_address;
   uपूर्णांक16_t reserved3;
   uपूर्णांक8_t  segment_4G;
   uपूर्णांक8_t  enhanced_sg;
   uपूर्णांक32_t ccsar;
   uपूर्णांक32_t cccr;
पूर्ण IPS_DCDB_CMD, *PIPS_DCDB_CMD;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  op_code;
   uपूर्णांक8_t  command_id;
   uपूर्णांक8_t  channel;
   uपूर्णांक8_t  source_target;
   uपूर्णांक32_t reserved;
   uपूर्णांक32_t reserved2;
   uपूर्णांक32_t reserved3;
   uपूर्णांक32_t ccsar;
   uपूर्णांक32_t cccr;
पूर्ण IPS_CS_CMD, *PIPS_CS_CMD;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  op_code;
   uपूर्णांक8_t  command_id;
   uपूर्णांक8_t  log_drv;
   uपूर्णांक8_t  control;
   uपूर्णांक32_t reserved;
   uपूर्णांक32_t reserved2;
   uपूर्णांक32_t reserved3;
   uपूर्णांक32_t ccsar;
   uपूर्णांक32_t cccr;
पूर्ण IPS_US_CMD, *PIPS_US_CMD;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  op_code;
   uपूर्णांक8_t  command_id;
   uपूर्णांक8_t  reserved;
   uपूर्णांक8_t  state;
   uपूर्णांक32_t reserved2;
   uपूर्णांक32_t reserved3;
   uपूर्णांक32_t reserved4;
   uपूर्णांक32_t ccsar;
   uपूर्णांक32_t cccr;
पूर्ण IPS_FC_CMD, *PIPS_FC_CMD;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  op_code;
   uपूर्णांक8_t  command_id;
   uपूर्णांक8_t  reserved;
   uपूर्णांक8_t  desc;
   uपूर्णांक32_t reserved2;
   uपूर्णांक32_t buffer_addr;
   uपूर्णांक32_t reserved3;
   uपूर्णांक32_t ccsar;
   uपूर्णांक32_t cccr;
पूर्ण IPS_STATUS_CMD, *PIPS_STATUS_CMD;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  op_code;
   uपूर्णांक8_t  command_id;
   uपूर्णांक8_t  page;
   uपूर्णांक8_t  ग_लिखो;
   uपूर्णांक32_t reserved;
   uपूर्णांक32_t buffer_addr;
   uपूर्णांक32_t reserved2;
   uपूर्णांक32_t ccsar;
   uपूर्णांक32_t cccr;
पूर्ण IPS_NVRAM_CMD, *PIPS_NVRAM_CMD;

प्रकार काष्ठा
अणु
    uपूर्णांक8_t  op_code;
    uपूर्णांक8_t  command_id;
    uपूर्णांक16_t reserved;
    uपूर्णांक32_t count;
    uपूर्णांक32_t buffer_addr;
    uपूर्णांक32_t reserved2;
पूर्ण IPS_VERSION_INFO, *PIPS_VERSION_INFO;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  op_code;
   uपूर्णांक8_t  command_id;
   uपूर्णांक8_t  reset_count;
   uपूर्णांक8_t  reset_type;
   uपूर्णांक8_t  second;
   uपूर्णांक8_t  minute;
   uपूर्णांक8_t  hour;
   uपूर्णांक8_t  day;
   uपूर्णांक8_t  reserved1[4];
   uपूर्णांक8_t  month;
   uपूर्णांक8_t  yearH;
   uपूर्णांक8_t  yearL;
   uपूर्णांक8_t  reserved2;
पूर्ण IPS_FFDC_CMD, *PIPS_FFDC_CMD;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  op_code;
   uपूर्णांक8_t  command_id;
   uपूर्णांक8_t  type;
   uपूर्णांक8_t  direction;
   uपूर्णांक32_t count;
   uपूर्णांक32_t buffer_addr;
   uपूर्णांक8_t  total_packets;
   uपूर्णांक8_t  packet_num;
   uपूर्णांक16_t reserved;
पूर्ण IPS_FLASHFW_CMD, *PIPS_FLASHFW_CMD;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  op_code;
   uपूर्णांक8_t  command_id;
   uपूर्णांक8_t  type;
   uपूर्णांक8_t  direction;
   uपूर्णांक32_t count;
   uपूर्णांक32_t buffer_addr;
   uपूर्णांक32_t offset;
पूर्ण IPS_FLASHBIOS_CMD, *PIPS_FLASHBIOS_CMD;

प्रकार जोड़ अणु
   IPS_IO_CMD         basic_io;
   IPS_LD_CMD         logical_info;
   IPS_IOCTL_CMD      ioctl_info;
   IPS_DCDB_CMD       dcdb;
   IPS_CS_CMD         config_sync;
   IPS_US_CMD         unlock_stripe;
   IPS_FC_CMD         flush_cache;
   IPS_STATUS_CMD     status;
   IPS_NVRAM_CMD      nvram;
   IPS_FFDC_CMD       ffdc;
   IPS_FLASHFW_CMD    flashfw;
   IPS_FLASHBIOS_CMD  flashbios;
   IPS_VERSION_INFO   version_info;
   IPS_RESET_CMD      reset;
पूर्ण IPS_HOST_COMMAND, *PIPS_HOST_COMMAND;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  logical_id;
   uपूर्णांक8_t  reserved;
   uपूर्णांक8_t  raid_level;
   uपूर्णांक8_t  state;
   uपूर्णांक32_t sector_count;
पूर्ण IPS_DRIVE_INFO, *PIPS_DRIVE_INFO;

प्रकार काष्ठा अणु
   uपूर्णांक8_t       no_of_log_drive;
   uपूर्णांक8_t       reserved[3];
   IPS_DRIVE_INFO drive_info[IPS_MAX_LD];
पूर्ण IPS_LD_INFO, *PIPS_LD_INFO;

प्रकार काष्ठा अणु
   uपूर्णांक8_t   device_address;
   uपूर्णांक8_t   cmd_attribute;
   uपूर्णांक16_t  transfer_length;
   uपूर्णांक32_t  buffer_poपूर्णांकer;
   uपूर्णांक8_t   cdb_length;
   uपूर्णांक8_t   sense_length;
   uपूर्णांक8_t   sg_count;
   uपूर्णांक8_t   reserved;
   uपूर्णांक8_t   scsi_cdb[12];
   uपूर्णांक8_t   sense_info[64];
   uपूर्णांक8_t   scsi_status;
   uपूर्णांक8_t   reserved2[3];
पूर्ण IPS_DCDB_TABLE, *PIPS_DCDB_TABLE;

प्रकार काष्ठा अणु
   uपूर्णांक8_t   device_address;
   uपूर्णांक8_t   cmd_attribute;
   uपूर्णांक8_t   cdb_length;
   uपूर्णांक8_t   reserved_क्रम_LUN;
   uपूर्णांक32_t  transfer_length;
   uपूर्णांक32_t  buffer_poपूर्णांकer;
   uपूर्णांक16_t  sg_count;
   uपूर्णांक8_t   sense_length;
   uपूर्णांक8_t   scsi_status;
   uपूर्णांक32_t  reserved;
   uपूर्णांक8_t   scsi_cdb[16];
   uपूर्णांक8_t   sense_info[56];
पूर्ण IPS_DCDB_TABLE_TAPE, *PIPS_DCDB_TABLE_TAPE;

प्रकार जोड़ अणु
   काष्ठा अणु
      अस्थिर uपूर्णांक8_t  reserved;
      अस्थिर uपूर्णांक8_t  command_id;
      अस्थिर uपूर्णांक8_t  basic_status;
      अस्थिर uपूर्णांक8_t  extended_status;
   पूर्ण fields;

   अस्थिर uपूर्णांक32_t    value;
पूर्ण IPS_STATUS, *PIPS_STATUS;

प्रकार काष्ठा अणु
   IPS_STATUS           status[IPS_MAX_CMDS + 1];
   अस्थिर PIPS_STATUS p_status_start;
   अस्थिर PIPS_STATUS p_status_end;
   अस्थिर PIPS_STATUS p_status_tail;
   अस्थिर uपूर्णांक32_t    hw_status_start;
   अस्थिर uपूर्णांक32_t    hw_status_tail;
पूर्ण IPS_ADAPTER, *PIPS_ADAPTER;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  ucLogDriveCount;
   uपूर्णांक8_t  ucMiscFlag;
   uपूर्णांक8_t  ucSLTFlag;
   uपूर्णांक8_t  ucBSTFlag;
   uपूर्णांक8_t  ucPwrChgCnt;
   uपूर्णांक8_t  ucWrongAdrCnt;
   uपूर्णांक8_t  ucUnidentCnt;
   uपूर्णांक8_t  ucNVramDevChgCnt;
   uपूर्णांक8_t  CodeBlkVersion[8];
   uपूर्णांक8_t  BootBlkVersion[8];
   uपूर्णांक32_t ulDriveSize[IPS_MAX_LD];
   uपूर्णांक8_t  ucConcurrentCmdCount;
   uपूर्णांक8_t  ucMaxPhysicalDevices;
   uपूर्णांक16_t usFlashRepgmCount;
   uपूर्णांक8_t  ucDefunctDiskCount;
   uपूर्णांक8_t  ucRebuildFlag;
   uपूर्णांक8_t  ucOfflineLogDrvCount;
   uपूर्णांक8_t  ucCriticalDrvCount;
   uपूर्णांक16_t usConfigUpdateCount;
   uपूर्णांक8_t  ucBlkFlag;
   uपूर्णांक8_t  reserved;
   uपूर्णांक16_t usAddrDeadDisk[IPS_MAX_CHANNELS * (IPS_MAX_TARGETS + 1)];
पूर्ण IPS_ENQ, *PIPS_ENQ;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  ucInitiator;
   uपूर्णांक8_t  ucParameters;
   uपूर्णांक8_t  ucMiscFlag;
   uपूर्णांक8_t  ucState;
   uपूर्णांक32_t ulBlockCount;
   uपूर्णांक8_t  ucDeviceId[28];
पूर्ण IPS_DEVSTATE, *PIPS_DEVSTATE;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  ucChn;
   uपूर्णांक8_t  ucTgt;
   uपूर्णांक16_t ucReserved;
   uपूर्णांक32_t ulStartSect;
   uपूर्णांक32_t ulNoOfSects;
पूर्ण IPS_CHUNK, *PIPS_CHUNK;

प्रकार काष्ठा अणु
   uपूर्णांक16_t ucUserField;
   uपूर्णांक8_t  ucState;
   uपूर्णांक8_t  ucRaidCacheParam;
   uपूर्णांक8_t  ucNoOfChunkUnits;
   uपूर्णांक8_t  ucStripeSize;
   uपूर्णांक8_t  ucParams;
   uपूर्णांक8_t  ucReserved;
   uपूर्णांक32_t ulLogDrvSize;
   IPS_CHUNK chunk[IPS_MAX_CHUNKS];
पूर्ण IPS_LD, *PIPS_LD;

प्रकार काष्ठा अणु
   uपूर्णांक8_t  board_disc[8];
   uपूर्णांक8_t  processor[8];
   uपूर्णांक8_t  ucNoChanType;
   uपूर्णांक8_t  ucNoHostIntType;
   uपूर्णांक8_t  ucCompression;
   uपूर्णांक8_t  ucNvramType;
   uपूर्णांक32_t ulNvramSize;
पूर्ण IPS_HARDWARE, *PIPS_HARDWARE;

प्रकार काष्ठा अणु
   uपूर्णांक8_t        ucLogDriveCount;
   uपूर्णांक8_t        ucDateD;
   uपूर्णांक8_t        ucDateM;
   uपूर्णांक8_t        ucDateY;
   uपूर्णांक8_t        init_id[4];
   uपूर्णांक8_t        host_id[12];
   uपूर्णांक8_t        समय_sign[8];
   uपूर्णांक32_t       UserOpt;
   uपूर्णांक16_t       user_field;
   uपूर्णांक8_t        ucRebuildRate;
   uपूर्णांक8_t        ucReserve;
   IPS_HARDWARE   hardware_disc;
   IPS_LD         logical_drive[IPS_MAX_LD];
   IPS_DEVSTATE   dev[IPS_MAX_CHANNELS][IPS_MAX_TARGETS+1];
   uपूर्णांक8_t        reserved[512];
पूर्ण IPS_CONF, *PIPS_CONF;

प्रकार काष्ठा अणु
   uपूर्णांक32_t  signature;
   uपूर्णांक8_t   reserved1;
   uपूर्णांक8_t   adapter_slot;
   uपूर्णांक16_t  adapter_type;
   uपूर्णांक8_t   ctrl_bios[8];
   uपूर्णांक8_t   versioning;                   /* 1 = Versioning Supported, अन्यथा 0 */
   uपूर्णांक8_t   version_mismatch;             /* 1 = Versioning MisMatch,  अन्यथा 0 */
   uपूर्णांक8_t   reserved2;
   uपूर्णांक8_t   operating_प्रणाली;
   uपूर्णांक8_t   driver_high[4];
   uपूर्णांक8_t   driver_low[4];
   uपूर्णांक8_t   BiosCompatibilityID[8];
   uपूर्णांक8_t   ReservedForOS2[8];
   uपूर्णांक8_t   bios_high[4];                 /* Adapter's Flashed BIOS Version   */
   uपूर्णांक8_t   bios_low[4];
   uपूर्णांक8_t   adapter_order[16];            /* BIOS Telling us the Sort Order   */
   uपूर्णांक8_t   Filler[60];
पूर्ण IPS_NVRAM_P5, *PIPS_NVRAM_P5;

/*--------------------------------------------------------------------------*/
/* Data वापसed from a GetVersion Command                                  */
/*--------------------------------------------------------------------------*/

                                             /* SubSystem Parameter[4]      */
#घोषणा  IPS_GET_VERSION_SUPPORT 0x00018000  /* Mask क्रम Versioning Support */

प्रकार काष्ठा
अणु
   uपूर्णांक32_t  revision;
   uपूर्णांक8_t   bootBlkVersion[32];
   uपूर्णांक8_t   bootBlkAttributes[4];
   uपूर्णांक8_t   codeBlkVersion[32];
   uपूर्णांक8_t   biosVersion[32];
   uपूर्णांक8_t   biosAttributes[4];
   uपूर्णांक8_t   compatibilityId[32];
   uपूर्णांक8_t   reserved[4];
पूर्ण IPS_VERSION_DATA;


प्रकार काष्ठा _IPS_SUBSYS अणु
   uपूर्णांक32_t  param[128];
पूर्ण IPS_SUBSYS, *PIPS_SUBSYS;

/**
 ** SCSI Structures
 **/

/*
 * Inquiry Data Format
 */
प्रकार काष्ठा अणु
   uपूर्णांक8_t   DeviceType;
   uपूर्णांक8_t   DeviceTypeQualअगरier;
   uपूर्णांक8_t   Version;
   uपूर्णांक8_t   ResponseDataFormat;
   uपूर्णांक8_t   AdditionalLength;
   uपूर्णांक8_t   Reserved;
   uपूर्णांक8_t   Flags[2];
   uपूर्णांक8_t   VenकरोrId[8];
   uपूर्णांक8_t   ProductId[16];
   uपूर्णांक8_t   ProductRevisionLevel[4];
   uपूर्णांक8_t   Reserved2;                                  /* Provides शून्य terminator to name */
पूर्ण IPS_SCSI_INQ_DATA, *PIPS_SCSI_INQ_DATA;

/*
 * Read Capacity Data Format
 */
प्रकार काष्ठा अणु
   uपूर्णांक32_t lba;
   uपूर्णांक32_t len;
पूर्ण IPS_SCSI_CAPACITY;

/*
 * Request Sense Data Format
 */
प्रकार काष्ठा अणु
   uपूर्णांक8_t  ResponseCode;
   uपूर्णांक8_t  SegmentNumber;
   uपूर्णांक8_t  Flags;
   uपूर्णांक8_t  Inक्रमmation[4];
   uपूर्णांक8_t  AdditionalLength;
   uपूर्णांक8_t  CommandSpecअगरic[4];
   uपूर्णांक8_t  AdditionalSenseCode;
   uपूर्णांक8_t  AdditionalSenseCodeQual;
   uपूर्णांक8_t  FRUCode;
   uपूर्णांक8_t  SenseKeySpecअगरic[3];
पूर्ण IPS_SCSI_REQSEN;

/*
 * Sense Data Format - Page 3
 */
प्रकार काष्ठा अणु
   uपूर्णांक8_t  PageCode;
   uपूर्णांक8_t  PageLength;
   uपूर्णांक16_t TracksPerZone;
   uपूर्णांक16_t AltSectorsPerZone;
   uपूर्णांक16_t AltTracksPerZone;
   uपूर्णांक16_t AltTracksPerVolume;
   uपूर्णांक16_t SectorsPerTrack;
   uपूर्णांक16_t BytesPerSector;
   uपूर्णांक16_t Interleave;
   uपूर्णांक16_t TrackSkew;
   uपूर्णांक16_t CylinderSkew;
   uपूर्णांक8_t  flags;
   uपूर्णांक8_t  reserved[3];
पूर्ण IPS_SCSI_MODE_PAGE3;

/*
 * Sense Data Format - Page 4
 */
प्रकार काष्ठा अणु
   uपूर्णांक8_t  PageCode;
   uपूर्णांक8_t  PageLength;
   uपूर्णांक16_t CylindersHigh;
   uपूर्णांक8_t  CylindersLow;
   uपूर्णांक8_t  Heads;
   uपूर्णांक16_t WritePrecompHigh;
   uपूर्णांक8_t  WritePrecompLow;
   uपूर्णांक16_t ReducedWriteCurrentHigh;
   uपूर्णांक8_t  ReducedWriteCurrentLow;
   uपूर्णांक16_t StepRate;
   uपूर्णांक16_t LandingZoneHigh;
   uपूर्णांक8_t  LandingZoneLow;
   uपूर्णांक8_t  flags;
   uपूर्णांक8_t  RotationalOffset;
   uपूर्णांक8_t  Reserved;
   uपूर्णांक16_t MediumRotationRate;
   uपूर्णांक8_t  Reserved2[2];
पूर्ण IPS_SCSI_MODE_PAGE4;

/*
 * Sense Data Format - Page 8
 */
प्रकार काष्ठा अणु
   uपूर्णांक8_t  PageCode;
   uपूर्णांक8_t  PageLength;
   uपूर्णांक8_t  flags;
   uपूर्णांक8_t  RetentPrio;
   uपूर्णांक16_t DisPrefetchLen;
   uपूर्णांक16_t MinPrefetchLen;
   uपूर्णांक16_t MaxPrefetchLen;
   uपूर्णांक16_t MaxPrefetchCeiling;
पूर्ण IPS_SCSI_MODE_PAGE8;

/*
 * Sense Data Format - Block Descriptor (DASD)
 */
प्रकार काष्ठा अणु
   uपूर्णांक32_t NumberOfBlocks;
   uपूर्णांक8_t  DensityCode;
   uपूर्णांक16_t BlockLengthHigh;
   uपूर्णांक8_t  BlockLengthLow;
पूर्ण IPS_SCSI_MODE_PAGE_BLKDESC;

/*
 * Sense Data Format - Mode Page Header
 */
प्रकार काष्ठा अणु
   uपूर्णांक8_t  DataLength;
   uपूर्णांक8_t  MediumType;
   uपूर्णांक8_t  Reserved;
   uपूर्णांक8_t  BlockDescLength;
पूर्ण IPS_SCSI_MODE_PAGE_HEADER;

प्रकार काष्ठा अणु
   IPS_SCSI_MODE_PAGE_HEADER  hdr;
   IPS_SCSI_MODE_PAGE_BLKDESC blkdesc;

   जोड़ अणु
      IPS_SCSI_MODE_PAGE3 pg3;
      IPS_SCSI_MODE_PAGE4 pg4;
      IPS_SCSI_MODE_PAGE8 pg8;
   पूर्ण pdata;
पूर्ण IPS_SCSI_MODE_PAGE_DATA;

/*
 * Scatter Gather list क्रमmat
 */
प्रकार काष्ठा ips_sglist अणु
   uपूर्णांक32_t address;
   uपूर्णांक32_t length;
पूर्ण IPS_STD_SG_LIST;

प्रकार काष्ठा ips_enh_sglist अणु
   uपूर्णांक32_t address_lo;
   uपूर्णांक32_t address_hi;
   uपूर्णांक32_t length;
   uपूर्णांक32_t reserved;
पूर्ण IPS_ENH_SG_LIST;

प्रकार जोड़ अणु
   व्योम             *list;
   IPS_STD_SG_LIST  *std_list;
   IPS_ENH_SG_LIST  *enh_list;
पूर्ण IPS_SG_LIST;

प्रकार काष्ठा अणु
   अक्षर *option_name;
   पूर्णांक  *option_flag;
   पूर्णांक   option_value;
पूर्ण IPS_OPTION;

/*
 * Status Info
 */
प्रकार काष्ठा ips_stat अणु
   uपूर्णांक32_t residue_len;
   व्योम     *scb_addr;
   uपूर्णांक8_t  padding[12 - माप(व्योम *)];
पूर्ण ips_stat_t;

/*
 * SCB Queue Format
 */
प्रकार काष्ठा ips_scb_queue अणु
   काष्ठा ips_scb *head;
   काष्ठा ips_scb *tail;
   पूर्णांक             count;
पूर्ण ips_scb_queue_t;

/*
 * Wait queue_क्रमmat
 */
प्रकार काष्ठा ips_रुको_queue अणु
	काष्ठा scsi_cmnd *head;
	काष्ठा scsi_cmnd *tail;
	पूर्णांक count;
पूर्ण ips_रुको_queue_entry_t;

प्रकार काष्ठा ips_copp_रुको_item अणु
	काष्ठा scsi_cmnd *scsi_cmd;
	काष्ठा ips_copp_रुको_item *next;
पूर्ण ips_copp_रुको_item_t;

प्रकार काष्ठा ips_copp_queue अणु
   काष्ठा ips_copp_रुको_item *head;
   काष्ठा ips_copp_रुको_item *tail;
   पूर्णांक                        count;
पूर्ण ips_copp_queue_t;

/* क्रमward decl क्रम host काष्ठाure */
काष्ठा ips_ha;

प्रकार काष्ठा अणु
   पूर्णांक       (*reset)(काष्ठा ips_ha *);
   पूर्णांक       (*issue)(काष्ठा ips_ha *, काष्ठा ips_scb *);
   पूर्णांक       (*isinit)(काष्ठा ips_ha *);
   पूर्णांक       (*isपूर्णांकr)(काष्ठा ips_ha *);
   पूर्णांक       (*init)(काष्ठा ips_ha *);
   पूर्णांक       (*erasebios)(काष्ठा ips_ha *);
   पूर्णांक       (*programbios)(काष्ठा ips_ha *, अक्षर *, uपूर्णांक32_t, uपूर्णांक32_t);
   पूर्णांक       (*verअगरybios)(काष्ठा ips_ha *, अक्षर *, uपूर्णांक32_t, uपूर्णांक32_t);
   व्योम      (*statinit)(काष्ठा ips_ha *);
   पूर्णांक       (*पूर्णांकr)(काष्ठा ips_ha *);
   व्योम      (*enableपूर्णांक)(काष्ठा ips_ha *);
   uपूर्णांक32_t (*statupd)(काष्ठा ips_ha *);
पूर्ण ips_hw_func_t;

प्रकार काष्ठा ips_ha अणु
   uपूर्णांक8_t            ha_id[IPS_MAX_CHANNELS+1];
   uपूर्णांक32_t           dcdb_active[IPS_MAX_CHANNELS];
   uपूर्णांक32_t           io_addr;            /* Base I/O address           */
   uपूर्णांक8_t            ntarमाला_लो;           /* Number of tarमाला_लो          */
   uपूर्णांक8_t            nbus;               /* Number of buses            */
   uपूर्णांक8_t            nlun;               /* Number of Luns             */
   uपूर्णांक16_t           ad_type;            /* Adapter type               */
   uपूर्णांक16_t           host_num;           /* Adapter number             */
   uपूर्णांक32_t           max_xfer;           /* Maximum Xfer size          */
   uपूर्णांक32_t           max_cmds;           /* Max concurrent commands    */
   uपूर्णांक32_t           num_ioctl;          /* Number of Ioctls           */
   ips_stat_t         sp;                 /* Status packer poपूर्णांकer      */
   काष्ठा ips_scb    *scbs;               /* Array of all CCBS          */
   काष्ठा ips_scb    *scb_मुक्तlist;       /* SCB मुक्त list              */
   ips_रुको_queue_entry_t   scb_रुकोlist;       /* Pending SCB list           */
   ips_copp_queue_t   copp_रुकोlist;      /* Pending PT list            */
   ips_scb_queue_t    scb_activelist;     /* Active SCB list            */
   IPS_IO_CMD        *dummy;              /* dummy command              */
   IPS_ADAPTER       *adapt;              /* Adapter status area        */
   IPS_LD_INFO       *logical_drive_info; /* Adapter Logical Drive Info */
   dma_addr_t         logical_drive_info_dma_addr; /* Logical Drive Info DMA Address */
   IPS_ENQ           *enq;                /* Adapter Enquiry data       */
   IPS_CONF          *conf;               /* Adapter config data        */
   IPS_NVRAM_P5      *nvram;              /* NVRAM page 5 data          */
   IPS_SUBSYS        *subsys;             /* Subप्रणाली parameters       */
   अक्षर              *ioctl_data;         /* IOCTL data area            */
   uपूर्णांक32_t           ioctl_datasize;     /* IOCTL data size            */
   uपूर्णांक32_t           cmd_in_progress;    /* Current command in progress*/
   पूर्णांक                flags;              /*                            */
   uपूर्णांक8_t            रुकोflag;           /* are we रुकोing क्रम cmd     */
   uपूर्णांक8_t            active;
   पूर्णांक                ioctl_reset;        /* IOCTL Requested Reset Flag */
   uपूर्णांक16_t           reset_count;        /* number of resets           */
   समय64_t           last_ffdc;          /* last समय we sent ffdc info*/
   uपूर्णांक8_t            slot_num;           /* PCI Slot Number            */
   पूर्णांक                ioctl_len;          /* size of ioctl buffer       */
   dma_addr_t         ioctl_busaddr;      /* dma address of ioctl buffer*/
   uपूर्णांक8_t            bios_version[8];    /* BIOS Revision              */
   uपूर्णांक32_t           mem_addr;           /* Memory mapped address      */
   uपूर्णांक32_t           io_len;             /* Size of IO Address         */
   uपूर्णांक32_t           mem_len;            /* Size of memory address     */
   अक्षर              __iomem *mem_ptr;    /* Memory mapped Ptr          */
   अक्षर              __iomem *ioremap_ptr;/* ioremapped memory poपूर्णांकer  */
   ips_hw_func_t      func;               /* hw function poपूर्णांकers       */
   काष्ठा pci_dev    *pcidev;             /* PCI device handle          */
   अक्षर              *flash_data;         /* Save Area क्रम flash data   */
   पूर्णांक                flash_len;          /* length of flash buffer     */
   u32                flash_datasize;     /* Save Area क्रम flash data size */
   dma_addr_t         flash_busaddr;      /* dma address of flash buffer*/
   dma_addr_t         enq_busaddr;        /* dma address of enq काष्ठा  */
   uपूर्णांक8_t            requires_esl;       /* Requires an EraseStripeLock */
पूर्ण ips_ha_t;

प्रकार व्योम (*ips_scb_callback) (ips_ha_t *, काष्ठा ips_scb *);

/*
 * SCB Format
 */
प्रकार काष्ठा ips_scb अणु
   IPS_HOST_COMMAND  cmd;
   IPS_DCDB_TABLE    dcdb;
   uपूर्णांक8_t           target_id;
   uपूर्णांक8_t           bus;
   uपूर्णांक8_t           lun;
   uपूर्णांक8_t           cdb[12];
   uपूर्णांक32_t          scb_busaddr;
   uपूर्णांक32_t          old_data_busaddr;  // Obsolete, but kept क्रम old utility compatibility
   uपूर्णांक32_t          समयout;
   uपूर्णांक8_t           basic_status;
   uपूर्णांक8_t           extended_status;
   uपूर्णांक8_t           अवरोधup;
   uपूर्णांक8_t           sg_अवरोध;
   uपूर्णांक32_t          data_len;
   uपूर्णांक32_t          sg_len;
   uपूर्णांक32_t          flags;
   uपूर्णांक32_t          op_code;
   IPS_SG_LIST       sg_list;
   काष्ठा scsi_cmnd *scsi_cmd;
   काष्ठा ips_scb   *q_next;
   ips_scb_callback  callback;
   uपूर्णांक32_t          sg_busaddr;
   पूर्णांक               sg_count;
   dma_addr_t        data_busaddr;
पूर्ण ips_scb_t;

प्रकार काष्ठा ips_scb_pt अणु
   IPS_HOST_COMMAND  cmd;
   IPS_DCDB_TABLE    dcdb;
   uपूर्णांक8_t           target_id;
   uपूर्णांक8_t           bus;
   uपूर्णांक8_t           lun;
   uपूर्णांक8_t           cdb[12];
   uपूर्णांक32_t          scb_busaddr;
   uपूर्णांक32_t          data_busaddr;
   uपूर्णांक32_t          समयout;
   uपूर्णांक8_t           basic_status;
   uपूर्णांक8_t           extended_status;
   uपूर्णांक16_t          अवरोधup;
   uपूर्णांक32_t          data_len;
   uपूर्णांक32_t          sg_len;
   uपूर्णांक32_t          flags;
   uपूर्णांक32_t          op_code;
   IPS_SG_LIST      *sg_list;
   काष्ठा scsi_cmnd *scsi_cmd;
   काष्ठा ips_scb   *q_next;
   ips_scb_callback  callback;
पूर्ण ips_scb_pt_t;

/*
 * Passthru Command Format
 */
प्रकार काष्ठा अणु
   uपूर्णांक8_t       CoppID[4];
   uपूर्णांक32_t      CoppCmd;
   uपूर्णांक32_t      PtBuffer;
   uपूर्णांक8_t      *CmdBuffer;
   uपूर्णांक32_t      CmdBSize;
   ips_scb_pt_t  CoppCP;
   uपूर्णांक32_t      TimeOut;
   uपूर्णांक8_t       BasicStatus;
   uपूर्णांक8_t       ExtendedStatus;
   uपूर्णांक8_t       AdapterType;
   uपूर्णांक8_t       reserved;
पूर्ण ips_passthru_t;

#पूर्ण_अगर

/* The Version Inक्रमmation below माला_लो created by SED during the build process. */
/* Do not modअगरy the next line; it's what SED is looking क्रम to करो the insert. */
/* Version Info                                                                */
/*************************************************************************
*
* VERSION.H -- version numbers and copyright notices in various क्रमmats
*
*************************************************************************/

#घोषणा IPS_VER_MAJOR 7
#घोषणा IPS_VER_MAJOR_STRING __stringअगरy(IPS_VER_MAJOR)
#घोषणा IPS_VER_MINOR 12
#घोषणा IPS_VER_MINOR_STRING __stringअगरy(IPS_VER_MINOR)
#घोषणा IPS_VER_BUILD 05
#घोषणा IPS_VER_BUILD_STRING __stringअगरy(IPS_VER_BUILD)
#घोषणा IPS_VER_STRING IPS_VER_MAJOR_STRING "." \
		IPS_VER_MINOR_STRING "." IPS_VER_BUILD_STRING
#घोषणा IPS_RELEASE_ID 0x00020000
#घोषणा IPS_BUILD_IDENT 761
#घोषणा IPS_LEGALCOPYRIGHT_STRING "(C) Copyright IBM Corp. 1994, 2002. All Rights Reserved."
#घोषणा IPS_ADAPTECCOPYRIGHT_STRING "(c) Copyright Adaptec, Inc. 2002 to 2004. All Rights Reserved."
#घोषणा IPS_DELLCOPYRIGHT_STRING "(c) Copyright Dell 2004. All Rights Reserved."
#घोषणा IPS_NT_LEGALCOPYRIGHT_STRING "(C) Copyright IBM Corp. 1994, 2002."

/* Version numbers क्रम various adapters */
#घोषणा IPS_VER_SERVERAID1 "2.25.01"
#घोषणा IPS_VER_SERVERAID2 "2.88.13"
#घोषणा IPS_VER_NAVAJO "2.88.13"
#घोषणा IPS_VER_SERVERAID3 "6.10.24"
#घोषणा IPS_VER_SERVERAID4H "7.12.02"
#घोषणा IPS_VER_SERVERAID4MLx "7.12.02"
#घोषणा IPS_VER_SARASOTA "7.12.02"
#घोषणा IPS_VER_MARCO "7.12.02"
#घोषणा IPS_VER_SEBRING "7.12.02"
#घोषणा IPS_VER_KEYWEST "7.12.02"

/* Compatibility IDs क्रम various adapters */
#घोषणा IPS_COMPAT_UNKNOWN ""
#घोषणा IPS_COMPAT_CURRENT "KW710"
#घोषणा IPS_COMPAT_SERVERAID1 "2.25.01"
#घोषणा IPS_COMPAT_SERVERAID2 "2.88.13"
#घोषणा IPS_COMPAT_NAVAJO  "2.88.13"
#घोषणा IPS_COMPAT_KIOWA "2.88.13"
#घोषणा IPS_COMPAT_SERVERAID3H  "SB610"
#घोषणा IPS_COMPAT_SERVERAID3L  "SB610"
#घोषणा IPS_COMPAT_SERVERAID4H  "KW710"
#घोषणा IPS_COMPAT_SERVERAID4M  "KW710"
#घोषणा IPS_COMPAT_SERVERAID4L  "KW710"
#घोषणा IPS_COMPAT_SERVERAID4Mx "KW710"
#घोषणा IPS_COMPAT_SERVERAID4Lx "KW710"
#घोषणा IPS_COMPAT_SARASOTA     "KW710"
#घोषणा IPS_COMPAT_MARCO        "KW710"
#घोषणा IPS_COMPAT_SEBRING      "KW710"
#घोषणा IPS_COMPAT_TAMPA        "KW710"
#घोषणा IPS_COMPAT_KEYWEST      "KW710"
#घोषणा IPS_COMPAT_BIOS "KW710"

#घोषणा IPS_COMPAT_MAX_ADAPTER_TYPE 18
#घोषणा IPS_COMPAT_ID_LENGTH 8

#घोषणा IPS_DEFINE_COMPAT_TABLE(tablename) \
   अक्षर tablename[IPS_COMPAT_MAX_ADAPTER_TYPE] [IPS_COMPAT_ID_LENGTH] = अणु \
      IPS_COMPAT_UNKNOWN, \
      IPS_COMPAT_SERVERAID1, \
      IPS_COMPAT_SERVERAID2, \
      IPS_COMPAT_NAVAJO, \
      IPS_COMPAT_KIOWA, \
      IPS_COMPAT_SERVERAID3H, \
      IPS_COMPAT_SERVERAID3L, \
      IPS_COMPAT_SERVERAID4H, \
      IPS_COMPAT_SERVERAID4M, \
      IPS_COMPAT_SERVERAID4L, \
      IPS_COMPAT_SERVERAID4Mx, \
      IPS_COMPAT_SERVERAID4Lx, \
      IPS_COMPAT_SARASOTA,         /* one-channel variety of SARASOTA */  \
      IPS_COMPAT_SARASOTA,         /* two-channel variety of SARASOTA */  \
      IPS_COMPAT_MARCO, \
      IPS_COMPAT_SEBRING, \
      IPS_COMPAT_TAMPA, \
      IPS_COMPAT_KEYWEST \
   पूर्ण
