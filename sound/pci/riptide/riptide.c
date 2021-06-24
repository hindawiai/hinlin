<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Driver क्रम the Conexant Riptide Soundchip
 *
 *	Copyright (c) 2004 Peter Gruber <nokos@gmx.net>
 */
/*
  History:
   - 02/15/2004 first release
   
  This Driver is based on the OSS Driver version from Linuxant (riptide-0.6lnxtbeta03111100)
  credits from the original files:
  
  MODULE NAME:        cnxt_rt.h                       
  AUTHOR:             K. Lazarev  (Transcribed by KNL)
  HISTORY:         Major Revision               Date        By
            -----------------------------     --------     -----
            Created                           02/1/2000     KNL

  MODULE NAME:     पूर्णांक_mdl.c                       
  AUTHOR:          Konstantin Lazarev    (Transcribed by KNL)
  HISTORY:         Major Revision               Date        By
            -----------------------------     --------     -----
            Created                           10/01/99      KNL
	    
  MODULE NAME:        riptide.h                       
  AUTHOR:             O. Druzhinin  (Transcribed by OLD)
  HISTORY:         Major Revision               Date        By
            -----------------------------     --------     -----
            Created                           10/16/97      OLD

  MODULE NAME:        Rp_Cmdअगर.cpp                       
  AUTHOR:             O. Druzhinin  (Transcribed by OLD)
                      K. Lazarev    (Transcribed by KNL)
  HISTORY:         Major Revision               Date        By
            -----------------------------     --------     -----
            Aकरोpted from NT4 driver            6/22/99      OLD
            Ported to Linux                    9/01/99      KNL

  MODULE NAME:        rt_hw.c                       
  AUTHOR:             O. Druzhinin  (Transcribed by OLD)
                      C. Lazarev    (Transcribed by CNL)
  HISTORY:         Major Revision               Date        By
            -----------------------------     --------     -----
            Created                           11/18/97      OLD
            Hardware functions क्रम RipTide    11/24/97      CNL
            (ES1) are coded
            Hardware functions क्रम RipTide    12/24/97      CNL
            (A0) are coded
            Hardware functions क्रम RipTide    03/20/98      CNL
            (A1) are coded
            Boot loader is included           05/07/98      CNL
            Redeचिन्हित क्रम WDM                07/27/98      CNL
            Redeचिन्हित क्रम Linux              09/01/99      CNL

  MODULE NAME:        rt_hw.h
  AUTHOR:             C. Lazarev    (Transcribed by CNL)
  HISTORY:         Major Revision               Date        By
            -----------------------------     --------     -----
            Created                           11/18/97      CNL

  MODULE NAME:     rt_mdl.c                       
  AUTHOR:          Konstantin Lazarev    (Transcribed by KNL)
  HISTORY:         Major Revision               Date        By
            -----------------------------     --------     -----
            Created                           10/01/99      KNL

  MODULE NAME:        mixer.h                        
  AUTHOR:             K. Kenney
  HISTORY:         Major Revision                   Date          By
            -----------------------------          --------     -----
            Created from MS W95 Sample             11/28/95      KRS
            RipTide                                10/15/97      KRS
            Aकरोpted क्रम Winकरोws NT driver          01/20/98      CNL
*/

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/रुको.h>
#समावेश <linux/gameport.h>
#समावेश <linux/device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/info.h>
#समावेश <sound/control.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/mpu401.h>
#समावेश <sound/opl3.h>
#समावेश <sound/initval.h>

#अगर IS_REACHABLE(CONFIG_GAMEPORT)
#घोषणा SUPPORT_JOYSTICK 1
#पूर्ण_अगर

MODULE_AUTHOR("Peter Gruber <nokos@gmx.net>");
MODULE_DESCRIPTION("riptide");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("riptide.hex");

अटल पूर्णांक index[SNDRV_CARDS] = SNDRV_DEFAULT_IDX;
अटल अक्षर *id[SNDRV_CARDS] = SNDRV_DEFAULT_STR;
अटल bool enable[SNDRV_CARDS] = SNDRV_DEFAULT_ENABLE;

#अगर_घोषित SUPPORT_JOYSTICK
अटल पूर्णांक joystick_port[SNDRV_CARDS] = अणु [0 ... (SNDRV_CARDS - 1)] = 0x200 पूर्ण;
#पूर्ण_अगर
अटल पूर्णांक mpu_port[SNDRV_CARDS] = अणु [0 ... (SNDRV_CARDS - 1)] = 0x330 पूर्ण;
अटल पूर्णांक opl3_port[SNDRV_CARDS] = अणु [0 ... (SNDRV_CARDS - 1)] = 0x388 पूर्ण;

module_param_array(index, पूर्णांक, शून्य, 0444);
MODULE_PARM_DESC(index, "Index value for Riptide soundcard.");
module_param_array(id, अक्षरp, शून्य, 0444);
MODULE_PARM_DESC(id, "ID string for Riptide soundcard.");
module_param_array(enable, bool, शून्य, 0444);
MODULE_PARM_DESC(enable, "Enable Riptide soundcard.");
#अगर_घोषित SUPPORT_JOYSTICK
module_param_hw_array(joystick_port, पूर्णांक, ioport, शून्य, 0444);
MODULE_PARM_DESC(joystick_port, "Joystick port # for Riptide soundcard.");
#पूर्ण_अगर
module_param_hw_array(mpu_port, पूर्णांक, ioport, शून्य, 0444);
MODULE_PARM_DESC(mpu_port, "MPU401 port # for Riptide driver.");
module_param_hw_array(opl3_port, पूर्णांक, ioport, शून्य, 0444);
MODULE_PARM_DESC(opl3_port, "OPL3 port # for Riptide driver.");

/*
 */

#घोषणा MPU401_HW_RIPTIDE MPU401_HW_MPU401
#घोषणा OPL3_HW_RIPTIDE   OPL3_HW_OPL3

#घोषणा PCI_EXT_CapId       0x40
#घोषणा PCI_EXT_NextCapPrt  0x41
#घोषणा PCI_EXT_PWMC        0x42
#घोषणा PCI_EXT_PWSCR       0x44
#घोषणा PCI_EXT_Data00      0x46
#घोषणा PCI_EXT_PMSCR_BSE   0x47
#घोषणा PCI_EXT_SB_Base     0x48
#घोषणा PCI_EXT_FM_Base     0x4a
#घोषणा PCI_EXT_MPU_Base    0x4C
#घोषणा PCI_EXT_Game_Base   0x4E
#घोषणा PCI_EXT_Legacy_Mask 0x50
#घोषणा PCI_EXT_AsicRev     0x52
#घोषणा PCI_EXT_Reserved3   0x53

#घोषणा LEGACY_ENABLE_ALL      0x8000	/* legacy device options */
#घोषणा LEGACY_ENABLE_SB       0x4000
#घोषणा LEGACY_ENABLE_FM       0x2000
#घोषणा LEGACY_ENABLE_MPU_INT  0x1000
#घोषणा LEGACY_ENABLE_MPU      0x0800
#घोषणा LEGACY_ENABLE_GAMEPORT 0x0400

#घोषणा MAX_WRITE_RETRY  10	/* cmd पूर्णांकerface limits */
#घोषणा MAX_ERROR_COUNT  10
#घोषणा CMDIF_TIMEOUT    50000
#घोषणा RESET_TRIES      5

#घोषणा READ_PORT_ULONG(p)     inl((अचिन्हित दीर्घ)&(p))
#घोषणा WRITE_PORT_ULONG(p,x)  outl(x,(अचिन्हित दीर्घ)&(p))

#घोषणा READ_AUDIO_CONTROL(p)     READ_PORT_ULONG(p->audio_control)
#घोषणा WRITE_AUDIO_CONTROL(p,x)  WRITE_PORT_ULONG(p->audio_control,x)
#घोषणा UMASK_AUDIO_CONTROL(p,x)  WRITE_PORT_ULONG(p->audio_control,READ_PORT_ULONG(p->audio_control)|x)
#घोषणा MASK_AUDIO_CONTROL(p,x)   WRITE_PORT_ULONG(p->audio_control,READ_PORT_ULONG(p->audio_control)&x)
#घोषणा READ_AUDIO_STATUS(p)      READ_PORT_ULONG(p->audio_status)

#घोषणा SET_GRESET(p)     UMASK_AUDIO_CONTROL(p,0x0001)	/* global reset चयन */
#घोषणा UNSET_GRESET(p)   MASK_AUDIO_CONTROL(p,~0x0001)
#घोषणा SET_AIE(p)        UMASK_AUDIO_CONTROL(p,0x0004)	/* पूर्णांकerrupt enable */
#घोषणा UNSET_AIE(p)      MASK_AUDIO_CONTROL(p,~0x0004)
#घोषणा SET_AIACK(p)      UMASK_AUDIO_CONTROL(p,0x0008)	/* पूर्णांकerrupt acknowledge */
#घोषणा UNSET_AIACKT(p)   MASKAUDIO_CONTROL(p,~0x0008)
#घोषणा SET_ECMDAE(p)     UMASK_AUDIO_CONTROL(p,0x0010)
#घोषणा UNSET_ECMDAE(p)   MASK_AUDIO_CONTROL(p,~0x0010)
#घोषणा SET_ECMDBE(p)     UMASK_AUDIO_CONTROL(p,0x0020)
#घोषणा UNSET_ECMDBE(p)   MASK_AUDIO_CONTROL(p,~0x0020)
#घोषणा SET_EDATAF(p)     UMASK_AUDIO_CONTROL(p,0x0040)
#घोषणा UNSET_EDATAF(p)   MASK_AUDIO_CONTROL(p,~0x0040)
#घोषणा SET_EDATBF(p)     UMASK_AUDIO_CONTROL(p,0x0080)
#घोषणा UNSET_EDATBF(p)   MASK_AUDIO_CONTROL(p,~0x0080)
#घोषणा SET_ESBIRQON(p)   UMASK_AUDIO_CONTROL(p,0x0100)
#घोषणा UNSET_ESBIRQON(p) MASK_AUDIO_CONTROL(p,~0x0100)
#घोषणा SET_EMPUIRQ(p)    UMASK_AUDIO_CONTROL(p,0x0200)
#घोषणा UNSET_EMPUIRQ(p)  MASK_AUDIO_CONTROL(p,~0x0200)
#घोषणा IS_CMDE(a)        (READ_PORT_ULONG(a->stat)&0x1)	/* cmd empty */
#घोषणा IS_DATF(a)        (READ_PORT_ULONG(a->stat)&0x2)	/* data filled */
#घोषणा IS_READY(p)       (READ_AUDIO_STATUS(p)&0x0001)
#घोषणा IS_DLREADY(p)     (READ_AUDIO_STATUS(p)&0x0002)
#घोषणा IS_DLERR(p)       (READ_AUDIO_STATUS(p)&0x0004)
#घोषणा IS_GERR(p)        (READ_AUDIO_STATUS(p)&0x0008)	/* error ! */
#घोषणा IS_CMDAEIRQ(p)    (READ_AUDIO_STATUS(p)&0x0010)
#घोषणा IS_CMDBEIRQ(p)    (READ_AUDIO_STATUS(p)&0x0020)
#घोषणा IS_DATAFIRQ(p)    (READ_AUDIO_STATUS(p)&0x0040)
#घोषणा IS_DATBFIRQ(p)    (READ_AUDIO_STATUS(p)&0x0080)
#घोषणा IS_EOBIRQ(p)      (READ_AUDIO_STATUS(p)&0x0100)	/* पूर्णांकerrupt status */
#घोषणा IS_EOSIRQ(p)      (READ_AUDIO_STATUS(p)&0x0200)
#घोषणा IS_EOCIRQ(p)      (READ_AUDIO_STATUS(p)&0x0400)
#घोषणा IS_UNSLIRQ(p)     (READ_AUDIO_STATUS(p)&0x0800)
#घोषणा IS_SBIRQ(p)       (READ_AUDIO_STATUS(p)&0x1000)
#घोषणा IS_MPUIRQ(p)      (READ_AUDIO_STATUS(p)&0x2000)

#घोषणा RESP 0x00000001		/* command flags */
#घोषणा PARM 0x00000002
#घोषणा CMDA 0x00000004
#घोषणा CMDB 0x00000008
#घोषणा NILL 0x00000000

#घोषणा LONG0(a)   ((u32)a)	/* shअगरts and masks */
#घोषणा BYTE0(a)   (LONG0(a)&0xff)
#घोषणा BYTE1(a)   (BYTE0(a)<<8)
#घोषणा BYTE2(a)   (BYTE0(a)<<16)
#घोषणा BYTE3(a)   (BYTE0(a)<<24)
#घोषणा WORD0(a)   (LONG0(a)&0xffff)
#घोषणा WORD1(a)   (WORD0(a)<<8)
#घोषणा WORD2(a)   (WORD0(a)<<16)
#घोषणा TRINIB0(a) (LONG0(a)&0xffffff)
#घोषणा TRINIB1(a) (TRINIB0(a)<<8)

#घोषणा RET(a)     ((जोड़ cmdret *)(a))

#घोषणा SEND_GETV(p,b)             sendcmd(p,RESP,GETV,0,RET(b))	/* get version */
#घोषणा SEND_GETC(p,b,c)           sendcmd(p,PARM|RESP,GETC,c,RET(b))
#घोषणा SEND_GUNS(p,b)             sendcmd(p,RESP,GUNS,0,RET(b))
#घोषणा SEND_SCID(p,b)             sendcmd(p,RESP,SCID,0,RET(b))
#घोषणा SEND_RMEM(p,b,c,d)         sendcmd(p,PARM|RESP,RMEM|BYTE1(b),LONG0(c),RET(d))	/* memory access क्रम firmware ग_लिखो */
#घोषणा SEND_SMEM(p,b,c)           sendcmd(p,PARM,SMEM|BYTE1(b),LONG0(c),RET(0))	/* memory access क्रम firmware ग_लिखो */
#घोषणा SEND_WMEM(p,b,c)           sendcmd(p,PARM,WMEM|BYTE1(b),LONG0(c),RET(0))	/* memory access क्रम firmware ग_लिखो */
#घोषणा SEND_SDTM(p,b,c)           sendcmd(p,PARM|RESP,SDTM|TRINIB1(b),0,RET(c))	/* memory access क्रम firmware ग_लिखो */
#घोषणा SEND_GOTO(p,b)             sendcmd(p,PARM,GOTO,LONG0(b),RET(0))	/* memory access क्रम firmware ग_लिखो */
#घोषणा SEND_SETDPLL(p)	           sendcmd(p,0,ARM_SETDPLL,0,RET(0))
#घोषणा SEND_SSTR(p,b,c)           sendcmd(p,PARM,SSTR|BYTE3(b),LONG0(c),RET(0))	/* start stream */
#घोषणा SEND_PSTR(p,b)             sendcmd(p,PARM,PSTR,BYTE3(b),RET(0))	/* छोड़ो stream */
#घोषणा SEND_KSTR(p,b)             sendcmd(p,PARM,KSTR,BYTE3(b),RET(0))	/* stop stream */
#घोषणा SEND_KDMA(p)               sendcmd(p,0,KDMA,0,RET(0))	/* stop all dma */
#घोषणा SEND_GPOS(p,b,c,d)         sendcmd(p,PARM|RESP,GPOS,BYTE3(c)|BYTE2(b),RET(d))	/* get position in dma */
#घोषणा SEND_SETF(p,b,c,d,e,f,g)   sendcmd(p,PARM,SETF|WORD1(b)|BYTE3(c),d|BYTE1(e)|BYTE2(f)|BYTE3(g),RET(0))	/* set sample क्रमmat at mixer */
#घोषणा SEND_GSTS(p,b,c,d)         sendcmd(p,PARM|RESP,GSTS,BYTE3(c)|BYTE2(b),RET(d))
#घोषणा SEND_NGPOS(p,b,c,d)        sendcmd(p,PARM|RESP,NGPOS,BYTE3(c)|BYTE2(b),RET(d))
#घोषणा SEND_PSEL(p,b,c)           sendcmd(p,PARM,PSEL,BYTE2(b)|BYTE3(c),RET(0))	/* activate lbus path */
#घोषणा SEND_PCLR(p,b,c)           sendcmd(p,PARM,PCLR,BYTE2(b)|BYTE3(c),RET(0))	/* deactivate lbus path */
#घोषणा SEND_PLST(p,b)             sendcmd(p,PARM,PLST,BYTE3(b),RET(0))
#घोषणा SEND_RSSV(p,b,c,d)         sendcmd(p,PARM|RESP,RSSV,BYTE2(b)|BYTE3(c),RET(d))
#घोषणा SEND_LSEL(p,b,c,d,e,f,g,h) sendcmd(p,PARM,LSEL|BYTE1(b)|BYTE2(c)|BYTE3(d),BYTE0(e)|BYTE1(f)|BYTE2(g)|BYTE3(h),RET(0))	/* select paths क्रम पूर्णांकernal connections */
#घोषणा SEND_SSRC(p,b,c,d,e)       sendcmd(p,PARM,SSRC|BYTE1(b)|WORD2(c),WORD0(d)|WORD2(e),RET(0))	/* configure source */
#घोषणा SEND_SLST(p,b)             sendcmd(p,PARM,SLST,BYTE3(b),RET(0))
#घोषणा SEND_RSRC(p,b,c)           sendcmd(p,RESP,RSRC|BYTE1(b),0,RET(c))	/* पढ़ो source config */
#घोषणा SEND_SSRB(p,b,c)           sendcmd(p,PARM,SSRB|BYTE1(b),WORD2(c),RET(0))
#घोषणा SEND_SDGV(p,b,c,d,e)       sendcmd(p,PARM,SDGV|BYTE2(b)|BYTE3(c),WORD0(d)|WORD2(e),RET(0))	/* set digital mixer */
#घोषणा SEND_RDGV(p,b,c,d)         sendcmd(p,PARM|RESP,RDGV|BYTE2(b)|BYTE3(c),0,RET(d))	/* पढ़ो digital mixer */
#घोषणा SEND_DLST(p,b)             sendcmd(p,PARM,DLST,BYTE3(b),RET(0))
#घोषणा SEND_SACR(p,b,c)           sendcmd(p,PARM,SACR,WORD0(b)|WORD2(c),RET(0))	/* set AC97 रेजिस्टर */
#घोषणा SEND_RACR(p,b,c)           sendcmd(p,PARM|RESP,RACR,WORD2(b),RET(c))	/* get AC97 रेजिस्टर */
#घोषणा SEND_ALST(p,b)             sendcmd(p,PARM,ALST,BYTE3(b),RET(0))
#घोषणा SEND_TXAC(p,b,c,d,e,f)     sendcmd(p,PARM,TXAC|BYTE1(b)|WORD2(c),WORD0(d)|BYTE2(e)|BYTE3(f),RET(0))
#घोषणा SEND_RXAC(p,b,c,d)         sendcmd(p,PARM|RESP,RXAC,BYTE2(b)|BYTE3(c),RET(d))
#घोषणा SEND_SI2S(p,b)             sendcmd(p,PARM,SI2S,WORD2(b),RET(0))

#घोषणा EOB_STATUS         0x80000000	/* status flags : block boundary */
#घोषणा EOS_STATUS         0x40000000	/*              : stoppped */
#घोषणा EOC_STATUS         0x20000000	/*              : stream end */
#घोषणा ERR_STATUS         0x10000000
#घोषणा EMPTY_STATUS       0x08000000

#घोषणा IEOB_ENABLE        0x1	/* enable पूर्णांकerrupts क्रम status notअगरication above */
#घोषणा IEOS_ENABLE        0x2
#घोषणा IEOC_ENABLE        0x4
#घोषणा RDONCE             0x8
#घोषणा DESC_MAX_MASK      0xff

#घोषणा ST_PLAY  0x1		/* stream states */
#घोषणा ST_STOP  0x2
#घोषणा ST_PAUSE 0x4

#घोषणा I2S_INTDEC     3	/* config क्रम I2S link */
#घोषणा I2S_MERGER     0
#घोषणा I2S_SPLITTER   0
#घोषणा I2S_MIXER      7
#घोषणा I2S_RATE       44100

#घोषणा MODEM_INTDEC   4	/* config क्रम modem link */
#घोषणा MODEM_MERGER   3
#घोषणा MODEM_SPLITTER 0
#घोषणा MODEM_MIXER    11

#घोषणा FM_INTDEC      3	/* config क्रम FM/OPL3 link */
#घोषणा FM_MERGER      0
#घोषणा FM_SPLITTER    0
#घोषणा FM_MIXER       9

#घोषणा SPLIT_PATH  0x80	/* path splitting flag */

क्रमागत FIRMWARE अणु
	DATA_REC = 0, EXT_END_OF_खाता, EXT_SEG_ADDR_REC, EXT_GOTO_CMD_REC,
	EXT_LIN_ADDR_REC,
पूर्ण;

क्रमागत CMDS अणु
	GETV = 0x00, GETC, GUNS, SCID, RMEM =
	    0x10, SMEM, WMEM, SDTM, GOTO, SSTR =
	    0x20, PSTR, KSTR, KDMA, GPOS, SETF, GSTS, NGPOS, PSEL =
	    0x30, PCLR, PLST, RSSV, LSEL, SSRC = 0x40, SLST, RSRC, SSRB, SDGV =
	    0x50, RDGV, DLST, SACR = 0x60, RACR, ALST, TXAC, RXAC, SI2S =
	    0x70, ARM_SETDPLL = 0x72,
पूर्ण;

क्रमागत E1SOURCE अणु
	ARM2LBUS_FIFO0 = 0, ARM2LBUS_FIFO1, ARM2LBUS_FIFO2, ARM2LBUS_FIFO3,
	ARM2LBUS_FIFO4, ARM2LBUS_FIFO5, ARM2LBUS_FIFO6, ARM2LBUS_FIFO7,
	ARM2LBUS_FIFO8, ARM2LBUS_FIFO9, ARM2LBUS_FIFO10, ARM2LBUS_FIFO11,
	ARM2LBUS_FIFO12, ARM2LBUS_FIFO13, ARM2LBUS_FIFO14, ARM2LBUS_FIFO15,
	INTER0_OUT, INTER1_OUT, INTER2_OUT, INTER3_OUT, INTER4_OUT,
	INTERM0_OUT, INTERM1_OUT, INTERM2_OUT, INTERM3_OUT, INTERM4_OUT,
	INTERM5_OUT, INTERM6_OUT, DECIMM0_OUT, DECIMM1_OUT, DECIMM2_OUT,
	DECIMM3_OUT, DECIM0_OUT, SR3_4_OUT, OPL3_SAMPLE, ASRC0, ASRC1,
	ACLNK2PADC, ACLNK2MODEM0RX, ACLNK2MIC, ACLNK2MODEM1RX, ACLNK2HNDMIC,
	DIGITAL_MIXER_OUT0, GAINFUNC0_OUT, GAINFUNC1_OUT, GAINFUNC2_OUT,
	GAINFUNC3_OUT, GAINFUNC4_OUT, SOFTMODEMTX, SPLITTER0_OUTL,
	SPLITTER0_OUTR, SPLITTER1_OUTL, SPLITTER1_OUTR, SPLITTER2_OUTL,
	SPLITTER2_OUTR, SPLITTER3_OUTL, SPLITTER3_OUTR, MERGER0_OUT,
	MERGER1_OUT, MERGER2_OUT, MERGER3_OUT, ARM2LBUS_FIFO_सूचीECT, NO_OUT
पूर्ण;

क्रमागत E2SINK अणु
	LBUS2ARM_FIFO0 = 0, LBUS2ARM_FIFO1, LBUS2ARM_FIFO2, LBUS2ARM_FIFO3,
	LBUS2ARM_FIFO4, LBUS2ARM_FIFO5, LBUS2ARM_FIFO6, LBUS2ARM_FIFO7,
	INTER0_IN, INTER1_IN, INTER2_IN, INTER3_IN, INTER4_IN, INTERM0_IN,
	INTERM1_IN, INTERM2_IN, INTERM3_IN, INTERM4_IN, INTERM5_IN, INTERM6_IN,
	DECIMM0_IN, DECIMM1_IN, DECIMM2_IN, DECIMM3_IN, DECIM0_IN, SR3_4_IN,
	PDAC2ACLNK, MODEM0TX2ACLNK, MODEM1TX2ACLNK, HNDSPK2ACLNK,
	DIGITAL_MIXER_IN0, DIGITAL_MIXER_IN1, DIGITAL_MIXER_IN2,
	DIGITAL_MIXER_IN3, DIGITAL_MIXER_IN4, DIGITAL_MIXER_IN5,
	DIGITAL_MIXER_IN6, DIGITAL_MIXER_IN7, DIGITAL_MIXER_IN8,
	DIGITAL_MIXER_IN9, DIGITAL_MIXER_IN10, DIGITAL_MIXER_IN11,
	GAINFUNC0_IN, GAINFUNC1_IN, GAINFUNC2_IN, GAINFUNC3_IN, GAINFUNC4_IN,
	SOFTMODEMRX, SPLITTER0_IN, SPLITTER1_IN, SPLITTER2_IN, SPLITTER3_IN,
	MERGER0_INL, MERGER0_INR, MERGER1_INL, MERGER1_INR, MERGER2_INL,
	MERGER2_INR, MERGER3_INL, MERGER3_INR, E2SINK_MAX
पूर्ण;

क्रमागत LBUS_SINK अणु
	LS_SRC_INTERPOLATOR = 0, LS_SRC_INTERPOLATORM, LS_SRC_DECIMATOR,
	LS_SRC_DECIMATORM, LS_MIXER_IN, LS_MIXER_GAIN_FUNCTION,
	LS_SRC_SPLITTER, LS_SRC_MERGER, LS_NONE1, LS_NONE2,
पूर्ण;

क्रमागत RT_CHANNEL_IDS अणु
	M0TX = 0, M1TX, TAMTX, HSSPKR, PDAC, DSNDTX0, DSNDTX1, DSNDTX2,
	DSNDTX3, DSNDTX4, DSNDTX5, DSNDTX6, DSNDTX7, WVSTRTX, COP3DTX, SPARE,
	M0RX, HSMIC, M1RX, CLEANRX, MICADC, PADC, COPRX1, COPRX2,
	CHANNEL_ID_COUNTER
पूर्ण;

क्रमागत अणु SB_CMD = 0, MODEM_CMD, I2S_CMD0, I2S_CMD1, FM_CMD, MAX_CMD पूर्ण;

काष्ठा lbuspath अणु
	स्थिर अचिन्हित अक्षर *noconv;
	स्थिर अचिन्हित अक्षर *stereo;
	स्थिर अचिन्हित अक्षर *mono;
पूर्ण;

काष्ठा cmdport अणु
	u32 data1;		/* cmd,param */
	u32 data2;		/* param */
	u32 stat;		/* status */
	u32 pad[5];
पूर्ण;

काष्ठा riptideport अणु
	u32 audio_control;	/* status रेजिस्टरs */
	u32 audio_status;
	u32 pad[2];
	काष्ठा cmdport port[2];	/* command ports */
पूर्ण;

काष्ठा cmdअगर अणु
	काष्ठा riptideport *hwport;
	spinlock_t lock;
	अचिन्हित पूर्णांक cmdcnt;	/* cmd statistics */
	अचिन्हित पूर्णांक cmdसमय;
	अचिन्हित पूर्णांक cmdसमयmax;
	अचिन्हित पूर्णांक cmdसमयmin;
	अचिन्हित पूर्णांक errcnt;
	पूर्णांक is_reset;
पूर्ण;

काष्ठा riptide_firmware अणु
	u16 ASIC;
	u16 CODEC;
	u16 AUXDSP;
	u16 PROG;
पूर्ण;

जोड़ cmdret अणु
	u8 retbytes[8];
	u16 retwords[4];
	u32 retदीर्घs[2];
पूर्ण;

जोड़ firmware_version अणु
	जोड़ cmdret ret;
	काष्ठा riptide_firmware firmware;
पूर्ण;

#घोषणा get_pcmhwdev(substream) (काष्ठा pcmhw *)(substream->runसमय->निजी_data)

#घोषणा PLAYBACK_SUBSTREAMS 3
काष्ठा snd_riptide अणु
	काष्ठा snd_card *card;
	काष्ठा pci_dev *pci;
	स्थिर काष्ठा firmware *fw_entry;

	काष्ठा cmdअगर *cअगर;

	काष्ठा snd_pcm *pcm;
	काष्ठा snd_pcm *pcm_i2s;
	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_opl3 *opl3;
	काष्ठा snd_ac97 *ac97;
	काष्ठा snd_ac97_bus *ac97_bus;

	काष्ठा snd_pcm_substream *playback_substream[PLAYBACK_SUBSTREAMS];
	काष्ठा snd_pcm_substream *capture_substream;

	पूर्णांक खोलोstreams;

	पूर्णांक irq;
	अचिन्हित दीर्घ port;
	अचिन्हित लघु mpuaddr;
	अचिन्हित लघु opladdr;
#अगर_घोषित SUPPORT_JOYSTICK
	अचिन्हित लघु gameaddr;
#पूर्ण_अगर
	काष्ठा resource *res_port;

	अचिन्हित लघु device_id;

	जोड़ firmware_version firmware;

	spinlock_t lock;
	काष्ठा snd_info_entry *proc_entry;

	अचिन्हित दीर्घ received_irqs;
	अचिन्हित दीर्घ handled_irqs;
#अगर_घोषित CONFIG_PM_SLEEP
	पूर्णांक in_suspend;
#पूर्ण_अगर
पूर्ण;

काष्ठा sgd अणु			/* scatter gather desriptor */
	__le32 dwNextLink;
	__le32 dwSegPtrPhys;
	__le32 dwSegLen;
	__le32 dwStat_Ctl;
पूर्ण;

काष्ठा pcmhw अणु			/* pcm descriptor */
	काष्ठा lbuspath paths;
	स्थिर अचिन्हित अक्षर *lbuspath;
	अचिन्हित अक्षर source;
	अचिन्हित अक्षर पूर्णांकdec[2];
	अचिन्हित अक्षर mixer;
	अचिन्हित अक्षर id;
	अचिन्हित अक्षर state;
	अचिन्हित पूर्णांक rate;
	अचिन्हित पूर्णांक channels;
	snd_pcm_क्रमmat_t क्रमmat;
	काष्ठा snd_dma_buffer sgdlist;
	काष्ठा sgd *sgdbuf;
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक pages;
	अचिन्हित पूर्णांक oldpos;
	अचिन्हित पूर्णांक poपूर्णांकer;
पूर्ण;

#घोषणा CMDRET_ZERO (जोड़ cmdret)अणुअणु(u32)0, (u32) 0पूर्णपूर्ण

अटल पूर्णांक sendcmd(काष्ठा cmdअगर *cअगर, u32 flags, u32 cmd, u32 parm,
		   जोड़ cmdret *ret);
अटल पूर्णांक माला_लोourcesink(काष्ठा cmdअगर *cअगर, अचिन्हित अक्षर source,
			 अचिन्हित अक्षर sink, अचिन्हित अक्षर *a,
			 अचिन्हित अक्षर *b);
अटल पूर्णांक snd_riptide_initialize(काष्ठा snd_riptide *chip);
अटल पूर्णांक riptide_reset(काष्ठा cmdअगर *cअगर, काष्ठा snd_riptide *chip);

/*
 */

अटल स्थिर काष्ठा pci_device_id snd_riptide_ids[] = अणु
	अणु PCI_DEVICE(0x127a, 0x4310) पूर्ण,
	अणु PCI_DEVICE(0x127a, 0x4320) पूर्ण,
	अणु PCI_DEVICE(0x127a, 0x4330) पूर्ण,
	अणु PCI_DEVICE(0x127a, 0x4340) पूर्ण,
	अणु0,पूर्ण,
पूर्ण;

#अगर_घोषित SUPPORT_JOYSTICK
अटल स्थिर काष्ठा pci_device_id snd_riptide_joystick_ids[] = अणु
	अणु PCI_DEVICE(0x127a, 0x4312) पूर्ण,
	अणु PCI_DEVICE(0x127a, 0x4322) पूर्ण,
	अणु PCI_DEVICE(0x127a, 0x4332) पूर्ण,
	अणु PCI_DEVICE(0x127a, 0x4342) पूर्ण,
	अणु0,पूर्ण,
पूर्ण;
#पूर्ण_अगर

MODULE_DEVICE_TABLE(pci, snd_riptide_ids);

/*
 */

अटल स्थिर अचिन्हित अक्षर lbusin2out[E2SINK_MAX + 1][2] = अणु
	अणुNO_OUT, LS_NONE1पूर्ण, अणुNO_OUT, LS_NONE2पूर्ण, अणुNO_OUT, LS_NONE1पूर्ण, अणुNO_OUT,
								     LS_NONE2पूर्ण,
	अणुNO_OUT, LS_NONE1पूर्ण, अणुNO_OUT, LS_NONE2पूर्ण, अणुNO_OUT, LS_NONE1पूर्ण, अणुNO_OUT,
								     LS_NONE2पूर्ण,
	अणुINTER0_OUT, LS_SRC_INTERPOLATORपूर्ण, अणुINTER1_OUT, LS_SRC_INTERPOLATORपूर्ण,
	अणुINTER2_OUT, LS_SRC_INTERPOLATORपूर्ण, अणुINTER3_OUT, LS_SRC_INTERPOLATORपूर्ण,
	अणुINTER4_OUT, LS_SRC_INTERPOLATORपूर्ण, अणुINTERM0_OUT, LS_SRC_INTERPOLATORMपूर्ण,
	अणुINTERM1_OUT, LS_SRC_INTERPOLATORMपूर्ण, अणुINTERM2_OUT,
					      LS_SRC_INTERPOLATORMपूर्ण,
	अणुINTERM3_OUT, LS_SRC_INTERPOLATORMपूर्ण, अणुINTERM4_OUT,
					      LS_SRC_INTERPOLATORMपूर्ण,
	अणुINTERM5_OUT, LS_SRC_INTERPOLATORMपूर्ण, अणुINTERM6_OUT,
					      LS_SRC_INTERPOLATORMपूर्ण,
	अणुDECIMM0_OUT, LS_SRC_DECIMATORMपूर्ण, अणुDECIMM1_OUT, LS_SRC_DECIMATORMपूर्ण,
	अणुDECIMM2_OUT, LS_SRC_DECIMATORMपूर्ण, अणुDECIMM3_OUT, LS_SRC_DECIMATORMपूर्ण,
	अणुDECIM0_OUT, LS_SRC_DECIMATORपूर्ण, अणुSR3_4_OUT, LS_NONE1पूर्ण, अणुNO_OUT,
								LS_NONE2पूर्ण,
	अणुNO_OUT, LS_NONE1पूर्ण, अणुNO_OUT, LS_NONE2पूर्ण, अणुNO_OUT, LS_NONE1पूर्ण,
	अणुDIGITAL_MIXER_OUT0, LS_MIXER_INपूर्ण, अणुDIGITAL_MIXER_OUT0, LS_MIXER_INपूर्ण,
	अणुDIGITAL_MIXER_OUT0, LS_MIXER_INपूर्ण, अणुDIGITAL_MIXER_OUT0, LS_MIXER_INपूर्ण,
	अणुDIGITAL_MIXER_OUT0, LS_MIXER_INपूर्ण, अणुDIGITAL_MIXER_OUT0, LS_MIXER_INपूर्ण,
	अणुDIGITAL_MIXER_OUT0, LS_MIXER_INपूर्ण, अणुDIGITAL_MIXER_OUT0, LS_MIXER_INपूर्ण,
	अणुDIGITAL_MIXER_OUT0, LS_MIXER_INपूर्ण, अणुDIGITAL_MIXER_OUT0, LS_MIXER_INपूर्ण,
	अणुDIGITAL_MIXER_OUT0, LS_MIXER_INपूर्ण, अणुDIGITAL_MIXER_OUT0, LS_MIXER_INपूर्ण,
	अणुGAINFUNC0_OUT, LS_MIXER_GAIN_FUNCTIONपूर्ण, अणुGAINFUNC1_OUT,
						  LS_MIXER_GAIN_FUNCTIONपूर्ण,
	अणुGAINFUNC2_OUT, LS_MIXER_GAIN_FUNCTIONपूर्ण, अणुGAINFUNC3_OUT,
						  LS_MIXER_GAIN_FUNCTIONपूर्ण,
	अणुGAINFUNC4_OUT, LS_MIXER_GAIN_FUNCTIONपूर्ण, अणुSOFTMODEMTX, LS_NONE1पूर्ण,
	अणुSPLITTER0_OUTL, LS_SRC_SPLITTERपूर्ण, अणुSPLITTER1_OUTL, LS_SRC_SPLITTERपूर्ण,
	अणुSPLITTER2_OUTL, LS_SRC_SPLITTERपूर्ण, अणुSPLITTER3_OUTL, LS_SRC_SPLITTERपूर्ण,
	अणुMERGER0_OUT, LS_SRC_MERGERपूर्ण, अणुMERGER0_OUT, LS_SRC_MERGERपूर्ण,
	अणुMERGER1_OUT, LS_SRC_MERGERपूर्ण,
	अणुMERGER1_OUT, LS_SRC_MERGERपूर्ण, अणुMERGER2_OUT, LS_SRC_MERGERपूर्ण,
	अणुMERGER2_OUT, LS_SRC_MERGERपूर्ण,
	अणुMERGER3_OUT, LS_SRC_MERGERपूर्ण, अणुMERGER3_OUT, LS_SRC_MERGERपूर्ण, अणुNO_OUT,
								     LS_NONE2पूर्ण,
पूर्ण;

अटल स्थिर अचिन्हित अक्षर lbus_play_opl3[] = अणु
	DIGITAL_MIXER_IN0 + FM_MIXER, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_play_modem[] = अणु
	DIGITAL_MIXER_IN0 + MODEM_MIXER, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_play_i2s[] = अणु
	INTER0_IN + I2S_INTDEC, DIGITAL_MIXER_IN0 + I2S_MIXER, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_play_out[] = अणु
	PDAC2ACLNK, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_play_outhp[] = अणु
	HNDSPK2ACLNK, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_play_noconv1[] = अणु
	DIGITAL_MIXER_IN0, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_play_stereo1[] = अणु
	INTER0_IN, DIGITAL_MIXER_IN0, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_play_mono1[] = अणु
	INTERM0_IN, DIGITAL_MIXER_IN0, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_play_noconv2[] = अणु
	DIGITAL_MIXER_IN1, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_play_stereo2[] = अणु
	INTER1_IN, DIGITAL_MIXER_IN1, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_play_mono2[] = अणु
	INTERM1_IN, DIGITAL_MIXER_IN1, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_play_noconv3[] = अणु
	DIGITAL_MIXER_IN2, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_play_stereo3[] = अणु
	INTER2_IN, DIGITAL_MIXER_IN2, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_play_mono3[] = अणु
	INTERM2_IN, DIGITAL_MIXER_IN2, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_rec_noconv1[] = अणु
	LBUS2ARM_FIFO5, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_rec_stereo1[] = अणु
	DECIM0_IN, LBUS2ARM_FIFO5, 0xff
पूर्ण;
अटल स्थिर अचिन्हित अक्षर lbus_rec_mono1[] = अणु
	DECIMM3_IN, LBUS2ARM_FIFO5, 0xff
पूर्ण;

अटल स्थिर अचिन्हित अक्षर play_ids[] = अणु 4, 1, 2, पूर्ण;
अटल स्थिर अचिन्हित अक्षर play_sources[] = अणु
	ARM2LBUS_FIFO4, ARM2LBUS_FIFO1, ARM2LBUS_FIFO2,
पूर्ण;
अटल स्थिर काष्ठा lbuspath lbus_play_paths[] = अणु
	अणु
	 .noconv = lbus_play_noconv1,
	 .stereo = lbus_play_stereo1,
	 .mono = lbus_play_mono1,
	 पूर्ण,
	अणु
	 .noconv = lbus_play_noconv2,
	 .stereo = lbus_play_stereo2,
	 .mono = lbus_play_mono2,
	 पूर्ण,
	अणु
	 .noconv = lbus_play_noconv3,
	 .stereo = lbus_play_stereo3,
	 .mono = lbus_play_mono3,
	 पूर्ण,
पूर्ण;
अटल स्थिर काष्ठा lbuspath lbus_rec_path = अणु
	.noconv = lbus_rec_noconv1,
	.stereo = lbus_rec_stereo1,
	.mono = lbus_rec_mono1,
पूर्ण;

#घोषणा FIRMWARE_VERSIONS 1
अटल जोड़ firmware_version firmware_versions[] = अणु
	अणु
		.firmware = अणु
			.ASIC = 3,
			.CODEC = 2,
			.AUXDSP = 3,
			.PROG = 773,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल u32 atoh(स्थिर अचिन्हित अक्षर *in, अचिन्हित पूर्णांक len)
अणु
	u32 sum = 0;
	अचिन्हित पूर्णांक mult = 1;
	अचिन्हित अक्षर c;

	जबतक (len) अणु
		पूर्णांक value;

		c = in[len - 1];
		value = hex_to_bin(c);
		अगर (value >= 0)
			sum += mult * value;
		mult *= 16;
		--len;
	पूर्ण
	वापस sum;
पूर्ण

अटल पूर्णांक senddata(काष्ठा cmdअगर *cअगर, स्थिर अचिन्हित अक्षर *in, u32 offset)
अणु
	u32 addr;
	u32 data;
	u32 i;
	स्थिर अचिन्हित अक्षर *p;

	i = atoh(&in[1], 2);
	addr = offset + atoh(&in[3], 4);
	अगर (SEND_SMEM(cअगर, 0, addr) != 0)
		वापस -EACCES;
	p = in + 9;
	जबतक (i) अणु
		data = atoh(p, 8);
		अगर (SEND_WMEM(cअगर, 2,
			      ((data & 0x0f0f0f0f) << 4) | ((data & 0xf0f0f0f0)
							    >> 4)))
			वापस -EACCES;
		i -= 4;
		p += 8;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक loadfirmware(काष्ठा cmdअगर *cअगर, स्थिर अचिन्हित अक्षर *img,
			अचिन्हित पूर्णांक size)
अणु
	स्थिर अचिन्हित अक्षर *in;
	u32 laddr, saddr, t, val;
	पूर्णांक err = 0;

	laddr = saddr = 0;
	जबतक (size > 0 && err == 0) अणु
		in = img;
		अगर (in[0] == ':') अणु
			t = atoh(&in[7], 2);
			चयन (t) अणु
			हाल DATA_REC:
				err = senddata(cअगर, in, laddr + saddr);
				अवरोध;
			हाल EXT_SEG_ADDR_REC:
				saddr = atoh(&in[9], 4) << 4;
				अवरोध;
			हाल EXT_LIN_ADDR_REC:
				laddr = atoh(&in[9], 4) << 16;
				अवरोध;
			हाल EXT_GOTO_CMD_REC:
				val = atoh(&in[9], 8);
				अगर (SEND_GOTO(cअगर, val) != 0)
					err = -EACCES;
				अवरोध;
			हाल EXT_END_OF_खाता:
				size = 0;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			जबतक (size > 0) अणु
				size--;
				अगर (*img++ == '\n')
					अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	snd_prपूर्णांकdd("load firmware return %d\n", err);
	वापस err;
पूर्ण

अटल व्योम
alloclbuspath(काष्ठा cmdअगर *cअगर, अचिन्हित अक्षर source,
	      स्थिर अचिन्हित अक्षर *path, अचिन्हित अक्षर *mixer, अचिन्हित अक्षर *s)
अणु
	जबतक (*path != 0xff) अणु
		अचिन्हित अक्षर sink, type;

		sink = *path & (~SPLIT_PATH);
		अगर (sink != E2SINK_MAX) अणु
			snd_prपूर्णांकdd("alloc path 0x%x->0x%x\n", source, sink);
			SEND_PSEL(cअगर, source, sink);
			source = lbusin2out[sink][0];
			type = lbusin2out[sink][1];
			अगर (type == LS_MIXER_IN) अणु
				अगर (mixer)
					*mixer = sink - DIGITAL_MIXER_IN0;
			पूर्ण
			अगर (type == LS_SRC_DECIMATORM ||
			    type == LS_SRC_DECIMATOR ||
			    type == LS_SRC_INTERPOLATORM ||
			    type == LS_SRC_INTERPOLATOR) अणु
				अगर (s) अणु
					अगर (s[0] != 0xff)
						s[1] = sink;
					अन्यथा
						s[0] = sink;
				पूर्ण
			पूर्ण
		पूर्ण
		अगर (*path++ & SPLIT_PATH) अणु
			स्थिर अचिन्हित अक्षर *npath = path;

			जबतक (*npath != 0xff)
				npath++;
			alloclbuspath(cअगर, source + 1, ++npath, mixer, s);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
मुक्तlbuspath(काष्ठा cmdअगर *cअगर, अचिन्हित अक्षर source, स्थिर अचिन्हित अक्षर *path)
अणु
	जबतक (*path != 0xff) अणु
		अचिन्हित अक्षर sink;

		sink = *path & (~SPLIT_PATH);
		अगर (sink != E2SINK_MAX) अणु
			snd_prपूर्णांकdd("free path 0x%x->0x%x\n", source, sink);
			SEND_PCLR(cअगर, source, sink);
			source = lbusin2out[sink][0];
		पूर्ण
		अगर (*path++ & SPLIT_PATH) अणु
			स्थिर अचिन्हित अक्षर *npath = path;

			जबतक (*npath != 0xff)
				npath++;
			मुक्तlbuspath(cअगर, source + 1, ++npath);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक ग_लिखोarm(काष्ठा cmdअगर *cअगर, u32 addr, u32 data, u32 mask)
अणु
	जोड़ cmdret rptr = CMDRET_ZERO;
	अचिन्हित पूर्णांक i = MAX_WRITE_RETRY;
	पूर्णांक flag = 1;

	SEND_RMEM(cअगर, 0x02, addr, &rptr);
	rptr.retदीर्घs[0] &= (~mask);

	जबतक (--i) अणु
		SEND_SMEM(cअगर, 0x01, addr);
		SEND_WMEM(cअगर, 0x02, (rptr.retदीर्घs[0] | data));
		SEND_RMEM(cअगर, 0x02, addr, &rptr);
		अगर ((rptr.retदीर्घs[0] & data) == data) अणु
			flag = 0;
			अवरोध;
		पूर्ण अन्यथा
			rptr.retदीर्घs[0] &= ~mask;
	पूर्ण
	snd_prपूर्णांकdd("send arm 0x%x 0x%x 0x%x return %d\n", addr, data, mask,
		    flag);
	वापस flag;
पूर्ण

अटल पूर्णांक sendcmd(काष्ठा cmdअगर *cअगर, u32 flags, u32 cmd, u32 parm,
		   जोड़ cmdret *ret)
अणु
	पूर्णांक i, j;
	पूर्णांक err;
	अचिन्हित पूर्णांक समय = 0;
	अचिन्हित दीर्घ irqflags;
	काष्ठा riptideport *hwport;
	काष्ठा cmdport *cmdport = शून्य;

	अगर (snd_BUG_ON(!cअगर))
		वापस -EINVAL;

	hwport = cअगर->hwport;
	अगर (cअगर->errcnt > MAX_ERROR_COUNT) अणु
		अगर (cअगर->is_reset) अणु
			snd_prपूर्णांकk(KERN_ERR
				   "Riptide: Too many failed cmds, reinitializing\n");
			अगर (riptide_reset(cअगर, शून्य) == 0) अणु
				cअगर->errcnt = 0;
				वापस -EIO;
			पूर्ण
		पूर्ण
		snd_prपूर्णांकk(KERN_ERR "Riptide: Initialization failed.\n");
		वापस -EINVAL;
	पूर्ण
	अगर (ret) अणु
		ret->retदीर्घs[0] = 0;
		ret->retदीर्घs[1] = 0;
	पूर्ण
	i = 0;
	spin_lock_irqsave(&cअगर->lock, irqflags);
	जबतक (i++ < CMDIF_TIMEOUT && !IS_READY(cअगर->hwport))
		udelay(10);
	अगर (i > CMDIF_TIMEOUT) अणु
		err = -EBUSY;
		जाओ errout;
	पूर्ण

	err = 0;
	क्रम (j = 0, समय = 0; समय < CMDIF_TIMEOUT; j++, समय += 2) अणु
		cmdport = &(hwport->port[j % 2]);
		अगर (IS_DATF(cmdport)) अणु	/* मुक्त pending data */
			READ_PORT_ULONG(cmdport->data1);
			READ_PORT_ULONG(cmdport->data2);
		पूर्ण
		अगर (IS_CMDE(cmdport)) अणु
			अगर (flags & PARM)	/* put data */
				WRITE_PORT_ULONG(cmdport->data2, parm);
			WRITE_PORT_ULONG(cmdport->data1, cmd);	/* ग_लिखो cmd */
			अगर ((flags & RESP) && ret) अणु
				जबतक (!IS_DATF(cmdport) &&
				       समय < CMDIF_TIMEOUT) अणु
					udelay(10);
					समय++;
				पूर्ण
				अगर (समय < CMDIF_TIMEOUT) अणु	/* पढ़ो response */
					ret->retदीर्घs[0] =
					    READ_PORT_ULONG(cmdport->data1);
					ret->retदीर्घs[1] =
					    READ_PORT_ULONG(cmdport->data2);
				पूर्ण अन्यथा अणु
					err = -ENOSYS;
					जाओ errout;
				पूर्ण
			पूर्ण
			अवरोध;
		पूर्ण
		udelay(20);
	पूर्ण
	अगर (समय == CMDIF_TIMEOUT) अणु
		err = -ENODATA;
		जाओ errout;
	पूर्ण
	spin_unlock_irqrestore(&cअगर->lock, irqflags);

	cअगर->cmdcnt++;		/* update command statistics */
	cअगर->cmdसमय += समय;
	अगर (समय > cअगर->cmdसमयmax)
		cअगर->cmdसमयmax = समय;
	अगर (समय < cअगर->cmdसमयmin)
		cअगर->cmdसमयmin = समय;
	अगर ((cअगर->cmdcnt) % 1000 == 0)
		snd_prपूर्णांकdd
		    ("send cmd %d time: %d mintime: %d maxtime %d err: %d\n",
		     cअगर->cmdcnt, cअगर->cmdसमय, cअगर->cmdसमयmin,
		     cअगर->cmdसमयmax, cअगर->errcnt);
	वापस 0;

      errout:
	cअगर->errcnt++;
	spin_unlock_irqrestore(&cअगर->lock, irqflags);
	snd_prपूर्णांकdd
	    ("send cmd %d hw: 0x%x flag: 0x%x cmd: 0x%x parm: 0x%x ret: 0x%x 0x%x CMDE: %d DATF: %d failed %d\n",
	     cअगर->cmdcnt, (पूर्णांक)((व्योम *)&(cmdport->stat) - (व्योम *)hwport),
	     flags, cmd, parm, ret ? ret->retदीर्घs[0] : 0,
	     ret ? ret->retदीर्घs[1] : 0, IS_CMDE(cmdport), IS_DATF(cmdport),
	     err);
	वापस err;
पूर्ण

अटल पूर्णांक
seपंचांगixer(काष्ठा cmdअगर *cअगर, लघु num, अचिन्हित लघु rval, अचिन्हित लघु lval)
अणु
	जोड़ cmdret rptr = CMDRET_ZERO;
	पूर्णांक i = 0;

	snd_prपूर्णांकdd("sent mixer %d: 0x%x 0x%x\n", num, rval, lval);
	करो अणु
		SEND_SDGV(cअगर, num, num, rval, lval);
		SEND_RDGV(cअगर, num, num, &rptr);
		अगर (rptr.retwords[0] == lval && rptr.retwords[1] == rval)
			वापस 0;
	पूर्ण जबतक (i++ < MAX_WRITE_RETRY);
	snd_prपूर्णांकdd("sent mixer failed\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक getpaths(काष्ठा cmdअगर *cअगर, अचिन्हित अक्षर *o)
अणु
	अचिन्हित अक्षर src[E2SINK_MAX];
	अचिन्हित अक्षर sink[E2SINK_MAX];
	पूर्णांक i, j = 0;

	क्रम (i = 0; i < E2SINK_MAX; i++) अणु
		माला_लोourcesink(cअगर, i, i, &src[i], &sink[i]);
		अगर (sink[i] < E2SINK_MAX) अणु
			o[j++] = sink[i];
			o[j++] = i;
		पूर्ण
	पूर्ण
	वापस j;
पूर्ण

अटल पूर्णांक
माला_लोourcesink(काष्ठा cmdअगर *cअगर, अचिन्हित अक्षर source, अचिन्हित अक्षर sink,
	      अचिन्हित अक्षर *a, अचिन्हित अक्षर *b)
अणु
	जोड़ cmdret rptr = CMDRET_ZERO;

	अगर (SEND_RSSV(cअगर, source, sink, &rptr) &&
	    SEND_RSSV(cअगर, source, sink, &rptr))
		वापस -EIO;
	*a = rptr.retbytes[0];
	*b = rptr.retbytes[1];
	snd_prपूर्णांकdd("getsourcesink 0x%x 0x%x\n", *a, *b);
	वापस 0;
पूर्ण

अटल पूर्णांक
माला_लोamplerate(काष्ठा cmdअगर *cअगर, अचिन्हित अक्षर *पूर्णांकdec, अचिन्हित पूर्णांक *rate)
अणु
	अचिन्हित अक्षर *s;
	अचिन्हित पूर्णांक p[2] = अणु 0, 0 पूर्ण;
	पूर्णांक i;
	जोड़ cmdret rptr = CMDRET_ZERO;

	s = पूर्णांकdec;
	क्रम (i = 0; i < 2; i++) अणु
		अगर (*s != 0xff) अणु
			अगर (SEND_RSRC(cअगर, *s, &rptr) &&
			    SEND_RSRC(cअगर, *s, &rptr))
				वापस -EIO;
			p[i] += rptr.retwords[1];
			p[i] *= rptr.retwords[2];
			p[i] += rptr.retwords[3];
			p[i] /= 65536;
		पूर्ण
		s++;
	पूर्ण
	अगर (p[0]) अणु
		अगर (p[1] != p[0])
			snd_prपूर्णांकdd("rates differ %d %d\n", p[0], p[1]);
		*rate = (अचिन्हित पूर्णांक)p[0];
	पूर्ण अन्यथा
		*rate = (अचिन्हित पूर्णांक)p[1];
	snd_prपूर्णांकdd("getsampleformat %d %d %d\n", पूर्णांकdec[0], पूर्णांकdec[1], *rate);
	वापस 0;
पूर्ण

अटल पूर्णांक
setsampleक्रमmat(काष्ठा cmdअगर *cअगर,
		अचिन्हित अक्षर mixer, अचिन्हित अक्षर id,
		अचिन्हित अक्षर channels, snd_pcm_क्रमmat_t क्रमmat)
अणु
	अचिन्हित अक्षर w, ch, sig, order;

	snd_prपूर्णांकdd
	    ("setsampleformat mixer: %d id: %d channels: %d format: %d\n",
	     mixer, id, channels, क्रमmat);
	ch = channels == 1;
	w = snd_pcm_क्रमmat_width(क्रमmat) == 8;
	sig = snd_pcm_क्रमmat_अचिन्हित(क्रमmat) != 0;
	order = snd_pcm_क्रमmat_big_endian(क्रमmat) != 0;

	अगर (SEND_SETF(cअगर, mixer, w, ch, order, sig, id) &&
	    SEND_SETF(cअगर, mixer, w, ch, order, sig, id)) अणु
		snd_prपूर्णांकdd("setsampleformat failed\n");
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
setsamplerate(काष्ठा cmdअगर *cअगर, अचिन्हित अक्षर *पूर्णांकdec, अचिन्हित पूर्णांक rate)
अणु
	u32 D, M, N;
	जोड़ cmdret rptr = CMDRET_ZERO;
	पूर्णांक i;

	snd_prपूर्णांकdd("setsamplerate intdec: %d,%d rate: %d\n", पूर्णांकdec[0],
		    पूर्णांकdec[1], rate);
	D = 48000;
	M = ((rate == 48000) ? 47999 : rate) * 65536;
	N = M % D;
	M /= D;
	क्रम (i = 0; i < 2; i++) अणु
		अगर (*पूर्णांकdec != 0xff) अणु
			करो अणु
				SEND_SSRC(cअगर, *पूर्णांकdec, D, M, N);
				SEND_RSRC(cअगर, *पूर्णांकdec, &rptr);
			पूर्ण जबतक (rptr.retwords[1] != D &&
				 rptr.retwords[2] != M &&
				 rptr.retwords[3] != N &&
				 i++ < MAX_WRITE_RETRY);
			अगर (i > MAX_WRITE_RETRY) अणु
				snd_prपूर्णांकdd("sent samplerate %d: %d failed\n",
					    *पूर्णांकdec, rate);
				वापस -EIO;
			पूर्ण
		पूर्ण
		पूर्णांकdec++;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक
geपंचांगixer(काष्ठा cmdअगर *cअगर, लघु num, अचिन्हित लघु *rval,
	 अचिन्हित लघु *lval)
अणु
	जोड़ cmdret rptr = CMDRET_ZERO;

	अगर (SEND_RDGV(cअगर, num, num, &rptr) && SEND_RDGV(cअगर, num, num, &rptr))
		वापस -EIO;
	*rval = rptr.retwords[0];
	*lval = rptr.retwords[1];
	snd_prपूर्णांकdd("got mixer %d: 0x%x 0x%x\n", num, *rval, *lval);
	वापस 0;
पूर्ण

अटल irqवापस_t riptide_handleirq(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_riptide *chip = dev_id;
	काष्ठा cmdअगर *cअगर = chip->cअगर;
	काष्ठा snd_pcm_substream *substream[PLAYBACK_SUBSTREAMS + 1];
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा pcmhw *data = शून्य;
	अचिन्हित पूर्णांक pos, period_bytes;
	काष्ठा sgd *c;
	पूर्णांक i, j;
	अचिन्हित पूर्णांक flag;

	अगर (!cअगर)
		वापस IRQ_HANDLED;

	क्रम (i = 0; i < PLAYBACK_SUBSTREAMS; i++)
		substream[i] = chip->playback_substream[i];
	substream[i] = chip->capture_substream;
	क्रम (i = 0; i < PLAYBACK_SUBSTREAMS + 1; i++) अणु
		अगर (substream[i] &&
		    (runसमय = substream[i]->runसमय) &&
		    (data = runसमय->निजी_data) && data->state != ST_STOP) अणु
			pos = 0;
			क्रम (j = 0; j < data->pages; j++) अणु
				c = &data->sgdbuf[j];
				flag = le32_to_cpu(c->dwStat_Ctl);
				अगर (flag & EOB_STATUS)
					pos += le32_to_cpu(c->dwSegLen);
				अगर (flag & EOC_STATUS)
					pos += le32_to_cpu(c->dwSegLen);
				अगर ((flag & EOS_STATUS)
				    && (data->state == ST_PLAY)) अणु
					data->state = ST_STOP;
					snd_prपूर्णांकk(KERN_ERR
						   "Riptide: DMA stopped unexpectedly\n");
				पूर्ण
				c->dwStat_Ctl =
				    cpu_to_le32(flag &
						~(EOS_STATUS | EOB_STATUS |
						  EOC_STATUS));
			पूर्ण
			data->poपूर्णांकer += pos;
			pos += data->oldpos;
			अगर (data->state != ST_STOP) अणु
				period_bytes =
				    frames_to_bytes(runसमय,
						    runसमय->period_size);
				snd_prपूर्णांकdd
				    ("interrupt 0x%x after 0x%lx of 0x%lx frames in period\n",
				     READ_AUDIO_STATUS(cअगर->hwport),
				     bytes_to_frames(runसमय, pos),
				     runसमय->period_size);
				j = 0;
				अगर (pos >= period_bytes) अणु
					j++;
					जबतक (pos >= period_bytes)
						pos -= period_bytes;
				पूर्ण
				data->oldpos = pos;
				अगर (j > 0)
					snd_pcm_period_elapsed(substream[i]);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक riptide_suspend(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_riptide *chip = card->निजी_data;

	chip->in_suspend = 1;
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D3hot);
	snd_ac97_suspend(chip->ac97);
	वापस 0;
पूर्ण

अटल पूर्णांक riptide_resume(काष्ठा device *dev)
अणु
	काष्ठा snd_card *card = dev_get_drvdata(dev);
	काष्ठा snd_riptide *chip = card->निजी_data;

	snd_riptide_initialize(chip);
	snd_ac97_resume(chip->ac97);
	snd_घातer_change_state(card, SNDRV_CTL_POWER_D0);
	chip->in_suspend = 0;
	वापस 0;
पूर्ण

अटल SIMPLE_DEV_PM_OPS(riptide_pm, riptide_suspend, riptide_resume);
#घोषणा RIPTIDE_PM_OPS	&riptide_pm
#अन्यथा
#घोषणा RIPTIDE_PM_OPS	शून्य
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल पूर्णांक try_to_load_firmware(काष्ठा cmdअगर *cअगर, काष्ठा snd_riptide *chip)
अणु
	जोड़ firmware_version firmware = अणु .ret = CMDRET_ZERO पूर्ण;
	पूर्णांक i, समयout, err;

	क्रम (i = 0; i < 2; i++) अणु
		WRITE_PORT_ULONG(cअगर->hwport->port[i].data1, 0);
		WRITE_PORT_ULONG(cअगर->hwport->port[i].data2, 0);
	पूर्ण
	SET_GRESET(cअगर->hwport);
	udelay(100);
	UNSET_GRESET(cअगर->hwport);
	udelay(100);

	क्रम (समयout = 100000; --समयout; udelay(10)) अणु
		अगर (IS_READY(cअगर->hwport) && !IS_GERR(cअगर->hwport))
			अवरोध;
	पूर्ण
	अगर (!समयout) अणु
		snd_prपूर्णांकk(KERN_ERR
			   "Riptide: device not ready, audio status: 0x%x "
			   "ready: %d gerr: %d\n",
			   READ_AUDIO_STATUS(cअगर->hwport),
			   IS_READY(cअगर->hwport), IS_GERR(cअगर->hwport));
		वापस -EIO;
	पूर्ण अन्यथा अणु
		snd_prपूर्णांकdd
			("Riptide: audio status: 0x%x ready: %d gerr: %d\n",
			 READ_AUDIO_STATUS(cअगर->hwport),
			 IS_READY(cअगर->hwport), IS_GERR(cअगर->hwport));
	पूर्ण

	SEND_GETV(cअगर, &firmware.ret);
	snd_prपूर्णांकdd("Firmware version: ASIC: %d CODEC %d AUXDSP %d PROG %d\n",
		    firmware.firmware.ASIC, firmware.firmware.CODEC,
		    firmware.firmware.AUXDSP, firmware.firmware.PROG);

	अगर (!chip)
		वापस 1;

	क्रम (i = 0; i < FIRMWARE_VERSIONS; i++) अणु
		अगर (!स_भेद(&firmware_versions[i], &firmware, माप(firmware)))
			वापस 1; /* OK */

	पूर्ण

	snd_prपूर्णांकdd("Writing Firmware\n");
	अगर (!chip->fw_entry) अणु
		err = request_firmware(&chip->fw_entry, "riptide.hex",
				       &chip->pci->dev);
		अगर (err) अणु
			snd_prपूर्णांकk(KERN_ERR
				   "Riptide: Firmware not available %d\n", err);
			वापस -EIO;
		पूर्ण
	पूर्ण
	err = loadfirmware(cअगर, chip->fw_entry->data, chip->fw_entry->size);
	अगर (err) अणु
		snd_prपूर्णांकk(KERN_ERR
			   "Riptide: Could not load firmware %d\n", err);
		वापस err;
	पूर्ण

	chip->firmware = firmware;

	वापस 1; /* OK */
पूर्ण

अटल पूर्णांक riptide_reset(काष्ठा cmdअगर *cअगर, काष्ठा snd_riptide *chip)
अणु
	जोड़ cmdret rptr = CMDRET_ZERO;
	पूर्णांक err, tries;

	अगर (!cअगर)
		वापस -EINVAL;

	cअगर->cmdcnt = 0;
	cअगर->cmdसमय = 0;
	cअगर->cmdसमयmax = 0;
	cअगर->cmdसमयmin = 0xffffffff;
	cअगर->errcnt = 0;
	cअगर->is_reset = 0;

	tries = RESET_TRIES;
	करो अणु
		err = try_to_load_firmware(cअगर, chip);
		अगर (err < 0)
			वापस err;
	पूर्ण जबतक (!err && --tries);

	SEND_SACR(cअगर, 0, AC97_RESET);
	SEND_RACR(cअगर, AC97_RESET, &rptr);
	snd_prपूर्णांकdd("AC97: 0x%x 0x%x\n", rptr.retदीर्घs[0], rptr.retदीर्घs[1]);

	SEND_PLST(cअगर, 0);
	SEND_SLST(cअगर, 0);
	SEND_DLST(cअगर, 0);
	SEND_ALST(cअगर, 0);
	SEND_KDMA(cअगर);

	ग_लिखोarm(cअगर, 0x301F8, 1, 1);
	ग_लिखोarm(cअगर, 0x301F4, 1, 1);

	SEND_LSEL(cअगर, MODEM_CMD, 0, 0, MODEM_INTDEC, MODEM_MERGER,
		  MODEM_SPLITTER, MODEM_MIXER);
	seपंचांगixer(cअगर, MODEM_MIXER, 0x7fff, 0x7fff);
	alloclbuspath(cअगर, ARM2LBUS_FIFO13, lbus_play_modem, शून्य, शून्य);

	SEND_LSEL(cअगर, FM_CMD, 0, 0, FM_INTDEC, FM_MERGER, FM_SPLITTER,
		  FM_MIXER);
	seपंचांगixer(cअगर, FM_MIXER, 0x7fff, 0x7fff);
	ग_लिखोarm(cअगर, 0x30648 + FM_MIXER * 4, 0x01, 0x00000005);
	ग_लिखोarm(cअगर, 0x301A8, 0x02, 0x00000002);
	ग_लिखोarm(cअगर, 0x30264, 0x08, 0xffffffff);
	alloclbuspath(cअगर, OPL3_SAMPLE, lbus_play_opl3, शून्य, शून्य);

	SEND_SSRC(cअगर, I2S_INTDEC, 48000,
		  ((u32) I2S_RATE * 65536) / 48000,
		  ((u32) I2S_RATE * 65536) % 48000);
	SEND_LSEL(cअगर, I2S_CMD0, 0, 0, I2S_INTDEC, I2S_MERGER, I2S_SPLITTER,
		  I2S_MIXER);
	SEND_SI2S(cअगर, 1);
	alloclbuspath(cअगर, ARM2LBUS_FIFO0, lbus_play_i2s, शून्य, शून्य);
	alloclbuspath(cअगर, DIGITAL_MIXER_OUT0, lbus_play_out, शून्य, शून्य);
	alloclbuspath(cअगर, DIGITAL_MIXER_OUT0, lbus_play_outhp, शून्य, शून्य);

	SET_AIACK(cअगर->hwport);
	SET_AIE(cअगर->hwport);
	SET_AIACK(cअगर->hwport);
	cअगर->is_reset = 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_riptide_playback = अणु
	.info = (SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_BLOCK_TRANSFER |
		 SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =
	    SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S8
	    | SNDRV_PCM_FMTBIT_U16_LE,
	.rates = SNDRV_PCM_RATE_KNOT | SNDRV_PCM_RATE_8000_48000,
	.rate_min = 5500,
	.rate_max = 48000,
	.channels_min = 1,
	.channels_max = 2,
	.buffer_bytes_max = (64 * 1024),
	.period_bytes_min = PAGE_SIZE >> 1,
	.period_bytes_max = PAGE_SIZE << 8,
	.periods_min = 2,
	.periods_max = 64,
	.fअगरo_size = 0,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hardware snd_riptide_capture = अणु
	.info = (SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_BLOCK_TRANSFER |
		 SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_MMAP_VALID),
	.क्रमmats =
	    SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S8
	    | SNDRV_PCM_FMTBIT_U16_LE,
	.rates = SNDRV_PCM_RATE_KNOT | SNDRV_PCM_RATE_8000_48000,
	.rate_min = 5500,
	.rate_max = 48000,
	.channels_min = 1,
	.channels_max = 2,
	.buffer_bytes_max = (64 * 1024),
	.period_bytes_min = PAGE_SIZE >> 1,
	.period_bytes_max = PAGE_SIZE << 3,
	.periods_min = 2,
	.periods_max = 64,
	.fअगरo_size = 0,
पूर्ण;

अटल snd_pcm_uframes_t snd_riptide_poपूर्णांकer(काष्ठा snd_pcm_substream
					     *substream)
अणु
	काष्ठा snd_riptide *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा pcmhw *data = get_pcmhwdev(substream);
	काष्ठा cmdअगर *cअगर = chip->cअगर;
	जोड़ cmdret rptr = CMDRET_ZERO;
	snd_pcm_uframes_t ret;

	SEND_GPOS(cअगर, 0, data->id, &rptr);
	अगर (data->size && runसमय->period_size) अणु
		snd_prपूर्णांकdd
		    ("pointer stream %d position 0x%x(0x%x in buffer) bytes 0x%lx(0x%lx in period) frames\n",
		     data->id, rptr.retदीर्घs[1], rptr.retदीर्घs[1] % data->size,
		     bytes_to_frames(runसमय, rptr.retदीर्घs[1]),
		     bytes_to_frames(runसमय,
				     rptr.retदीर्घs[1]) % runसमय->period_size);
		अगर (rptr.retदीर्घs[1] > data->poपूर्णांकer)
			ret =
			    bytes_to_frames(runसमय,
					    rptr.retदीर्घs[1] % data->size);
		अन्यथा
			ret =
			    bytes_to_frames(runसमय,
					    data->poपूर्णांकer % data->size);
	पूर्ण अन्यथा अणु
		snd_prपूर्णांकdd("stream not started or strange parms (%d %ld)\n",
			    data->size, runसमय->period_size);
		ret = bytes_to_frames(runसमय, 0);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक snd_riptide_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	पूर्णांक i, j;
	काष्ठा snd_riptide *chip = snd_pcm_substream_chip(substream);
	काष्ठा pcmhw *data = get_pcmhwdev(substream);
	काष्ठा cmdअगर *cअगर = chip->cअगर;
	जोड़ cmdret rptr = CMDRET_ZERO;

	spin_lock(&chip->lock);
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (!(data->state & ST_PLAY)) अणु
			SEND_SSTR(cअगर, data->id, data->sgdlist.addr);
			SET_AIE(cअगर->hwport);
			data->state = ST_PLAY;
			अगर (data->mixer != 0xff)
				seपंचांगixer(cअगर, data->mixer, 0x7fff, 0x7fff);
			chip->खोलोstreams++;
			data->oldpos = 0;
			data->poपूर्णांकer = 0;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (data->mixer != 0xff)
			seपंचांगixer(cअगर, data->mixer, 0, 0);
		seपंचांगixer(cअगर, data->mixer, 0, 0);
		SEND_KSTR(cअगर, data->id);
		data->state = ST_STOP;
		chip->खोलोstreams--;
		j = 0;
		करो अणु
			i = rptr.retदीर्घs[1];
			SEND_GPOS(cअगर, 0, data->id, &rptr);
			udelay(1);
		पूर्ण जबतक (i != rptr.retदीर्घs[1] && j++ < MAX_WRITE_RETRY);
		अगर (j > MAX_WRITE_RETRY)
			snd_prपूर्णांकk(KERN_ERR "Riptide: Could not stop stream!");
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (!(data->state & ST_PAUSE)) अणु
			SEND_PSTR(cअगर, data->id);
			data->state |= ST_PAUSE;
			chip->खोलोstreams--;
		पूर्ण
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (data->state & ST_PAUSE) अणु
			SEND_SSTR(cअगर, data->id, data->sgdlist.addr);
			data->state &= ~ST_PAUSE;
			chip->खोलोstreams++;
		पूर्ण
		अवरोध;
	शेष:
		spin_unlock(&chip->lock);
		वापस -EINVAL;
	पूर्ण
	spin_unlock(&chip->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_riptide_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_riptide *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा pcmhw *data = get_pcmhwdev(substream);
	काष्ठा cmdअगर *cअगर = chip->cअगर;
	स्थिर अचिन्हित अक्षर *lbuspath = शून्य;
	अचिन्हित पूर्णांक rate, channels;
	पूर्णांक err = 0;
	snd_pcm_क्रमmat_t क्रमmat;

	अगर (snd_BUG_ON(!cअगर || !data))
		वापस -EINVAL;

	snd_prपूर्णांकdd("prepare id %d ch: %d f:0x%x r:%d\n", data->id,
		    runसमय->channels, runसमय->क्रमmat, runसमय->rate);

	spin_lock_irq(&chip->lock);
	channels = runसमय->channels;
	क्रमmat = runसमय->क्रमmat;
	rate = runसमय->rate;
	चयन (channels) अणु
	हाल 1:
		अगर (rate == 48000 && क्रमmat == SNDRV_PCM_FORMAT_S16_LE)
			lbuspath = data->paths.noconv;
		अन्यथा
			lbuspath = data->paths.mono;
		अवरोध;
	हाल 2:
		अगर (rate == 48000 && क्रमmat == SNDRV_PCM_FORMAT_S16_LE)
			lbuspath = data->paths.noconv;
		अन्यथा
			lbuspath = data->paths.stereo;
		अवरोध;
	पूर्ण
	snd_prपूर्णांकdd("use sgdlist at 0x%p\n",
		    data->sgdlist.area);
	अगर (data->sgdlist.area) अणु
		अचिन्हित पूर्णांक i, j, size, pages, f, pt, period;
		काष्ठा sgd *c, *p = शून्य;

		size = frames_to_bytes(runसमय, runसमय->buffer_size);
		period = frames_to_bytes(runसमय, runसमय->period_size);
		f = PAGE_SIZE;
		जबतक ((size + (f >> 1) - 1) <= (f << 7) && (f << 1) > period)
			f = f >> 1;
		pages = DIV_ROUND_UP(size, f);
		data->size = size;
		data->pages = pages;
		snd_prपूर्णांकdd
		    ("create sgd size: 0x%x pages %d of size 0x%x for period 0x%x\n",
		     size, pages, f, period);
		pt = 0;
		j = 0;
		क्रम (i = 0; i < pages; i++) अणु
			अचिन्हित पूर्णांक ofs, addr;
			c = &data->sgdbuf[i];
			अगर (p)
				p->dwNextLink = cpu_to_le32(data->sgdlist.addr +
							    (i *
							     माप(काष्ठा
								    sgd)));
			c->dwNextLink = cpu_to_le32(data->sgdlist.addr);
			ofs = j << PAGE_SHIFT;
			addr = snd_pcm_sgbuf_get_addr(substream, ofs) + pt;
			c->dwSegPtrPhys = cpu_to_le32(addr);
			pt = (pt + f) % PAGE_SIZE;
			अगर (pt == 0)
				j++;
			c->dwSegLen = cpu_to_le32(f);
			c->dwStat_Ctl =
			    cpu_to_le32(IEOB_ENABLE | IEOS_ENABLE |
					IEOC_ENABLE);
			p = c;
			size -= f;
		पूर्ण
		data->sgdbuf[i].dwSegLen = cpu_to_le32(size);
	पूर्ण
	अगर (lbuspath && lbuspath != data->lbuspath) अणु
		अगर (data->lbuspath)
			मुक्तlbuspath(cअगर, data->source, data->lbuspath);
		alloclbuspath(cअगर, data->source, lbuspath,
			      &data->mixer, data->पूर्णांकdec);
		data->lbuspath = lbuspath;
		data->rate = 0;
	पूर्ण
	अगर (data->rate != rate || data->क्रमmat != क्रमmat ||
	    data->channels != channels) अणु
		data->rate = rate;
		data->क्रमmat = क्रमmat;
		data->channels = channels;
		अगर (setsampleक्रमmat
		    (cअगर, data->mixer, data->id, channels, क्रमmat)
		    || setsamplerate(cअगर, data->पूर्णांकdec, rate))
			err = -EIO;
	पूर्ण
	spin_unlock_irq(&chip->lock);
	वापस err;
पूर्ण

अटल पूर्णांक
snd_riptide_hw_params(काष्ठा snd_pcm_substream *substream,
		      काष्ठा snd_pcm_hw_params *hw_params)
अणु
	काष्ठा snd_riptide *chip = snd_pcm_substream_chip(substream);
	काष्ठा pcmhw *data = get_pcmhwdev(substream);
	काष्ठा snd_dma_buffer *sgdlist = &data->sgdlist;
	पूर्णांक err;

	snd_prपूर्णांकdd("hw params id %d (sgdlist: 0x%p 0x%lx %d)\n", data->id,
		    sgdlist->area, (अचिन्हित दीर्घ)sgdlist->addr,
		    (पूर्णांक)sgdlist->bytes);
	अगर (sgdlist->area)
		snd_dma_मुक्त_pages(sgdlist);
	अगर ((err = snd_dma_alloc_pages(SNDRV_DMA_TYPE_DEV,
				       &chip->pci->dev,
				       माप(काष्ठा sgd) * (DESC_MAX_MASK + 1),
				       sgdlist)) < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "Riptide: failed to alloc %d dma bytes\n",
			   (पूर्णांक)माप(काष्ठा sgd) * (DESC_MAX_MASK + 1));
		वापस err;
	पूर्ण
	data->sgdbuf = (काष्ठा sgd *)sgdlist->area;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_riptide_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_riptide *chip = snd_pcm_substream_chip(substream);
	काष्ठा pcmhw *data = get_pcmhwdev(substream);
	काष्ठा cmdअगर *cअगर = chip->cअगर;

	अगर (cअगर && data) अणु
		अगर (data->lbuspath)
			मुक्तlbuspath(cअगर, data->source, data->lbuspath);
		data->lbuspath = शून्य;
		data->source = 0xff;
		data->पूर्णांकdec[0] = 0xff;
		data->पूर्णांकdec[1] = 0xff;

		अगर (data->sgdlist.area) अणु
			snd_dma_मुक्त_pages(&data->sgdlist);
			data->sgdlist.area = शून्य;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_riptide_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_riptide *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा pcmhw *data;
	पूर्णांक sub_num = substream->number;

	chip->playback_substream[sub_num] = substream;
	runसमय->hw = snd_riptide_playback;

	data = kzalloc(माप(काष्ठा pcmhw), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;
	data->paths = lbus_play_paths[sub_num];
	data->id = play_ids[sub_num];
	data->source = play_sources[sub_num];
	data->पूर्णांकdec[0] = 0xff;
	data->पूर्णांकdec[1] = 0xff;
	data->state = ST_STOP;
	runसमय->निजी_data = data;
	वापस snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					     SNDRV_PCM_HW_PARAM_PERIODS);
पूर्ण

अटल पूर्णांक snd_riptide_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_riptide *chip = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा pcmhw *data;

	chip->capture_substream = substream;
	runसमय->hw = snd_riptide_capture;

	data = kzalloc(माप(काष्ठा pcmhw), GFP_KERNEL);
	अगर (data == शून्य)
		वापस -ENOMEM;
	data->paths = lbus_rec_path;
	data->id = PADC;
	data->source = ACLNK2PADC;
	data->पूर्णांकdec[0] = 0xff;
	data->पूर्णांकdec[1] = 0xff;
	data->state = ST_STOP;
	runसमय->निजी_data = data;
	वापस snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					     SNDRV_PCM_HW_PARAM_PERIODS);
पूर्ण

अटल पूर्णांक snd_riptide_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_riptide *chip = snd_pcm_substream_chip(substream);
	काष्ठा pcmhw *data = get_pcmhwdev(substream);
	पूर्णांक sub_num = substream->number;

	substream->runसमय->निजी_data = शून्य;
	chip->playback_substream[sub_num] = शून्य;
	kमुक्त(data);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_riptide_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_riptide *chip = snd_pcm_substream_chip(substream);
	काष्ठा pcmhw *data = get_pcmhwdev(substream);

	substream->runसमय->निजी_data = शून्य;
	chip->capture_substream = शून्य;
	kमुक्त(data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_riptide_playback_ops = अणु
	.खोलो = snd_riptide_playback_खोलो,
	.बंद = snd_riptide_playback_बंद,
	.hw_params = snd_riptide_hw_params,
	.hw_मुक्त = snd_riptide_hw_मुक्त,
	.prepare = snd_riptide_prepare,
	.trigger = snd_riptide_trigger,
	.poपूर्णांकer = snd_riptide_poपूर्णांकer,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_ops snd_riptide_capture_ops = अणु
	.खोलो = snd_riptide_capture_खोलो,
	.बंद = snd_riptide_capture_बंद,
	.hw_params = snd_riptide_hw_params,
	.hw_मुक्त = snd_riptide_hw_मुक्त,
	.prepare = snd_riptide_prepare,
	.trigger = snd_riptide_trigger,
	.poपूर्णांकer = snd_riptide_poपूर्णांकer,
पूर्ण;

अटल पूर्णांक snd_riptide_pcm(काष्ठा snd_riptide *chip, पूर्णांक device)
अणु
	काष्ठा snd_pcm *pcm;
	पूर्णांक err;

	अगर ((err =
	     snd_pcm_new(chip->card, "RIPTIDE", device, PLAYBACK_SUBSTREAMS, 1,
			 &pcm)) < 0)
		वापस err;
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK,
			&snd_riptide_playback_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE,
			&snd_riptide_capture_ops);
	pcm->निजी_data = chip;
	pcm->info_flags = 0;
	म_नकल(pcm->name, "RIPTIDE");
	chip->pcm = pcm;
	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_DEV_SG,
				       &chip->pci->dev, 64 * 1024, 128 * 1024);
	वापस 0;
पूर्ण

अटल irqवापस_t
snd_riptide_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_riptide *chip = dev_id;
	काष्ठा cmdअगर *cअगर = chip->cअगर;
	irqवापस_t ret = IRQ_HANDLED;

	अगर (cअगर) अणु
		chip->received_irqs++;
		अगर (IS_EOBIRQ(cअगर->hwport) || IS_EOSIRQ(cअगर->hwport) ||
		    IS_EOCIRQ(cअगर->hwport)) अणु
			chip->handled_irqs++;
			ret = IRQ_WAKE_THREAD;
		पूर्ण
		अगर (chip->rmidi && IS_MPUIRQ(cअगर->hwport)) अणु
			chip->handled_irqs++;
			snd_mpu401_uart_पूर्णांकerrupt(irq,
						  chip->rmidi->निजी_data);
		पूर्ण
		SET_AIACK(cअगर->hwport);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम
snd_riptide_codec_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg,
			अचिन्हित लघु val)
अणु
	काष्ठा snd_riptide *chip = ac97->निजी_data;
	काष्ठा cmdअगर *cअगर = chip->cअगर;
	जोड़ cmdret rptr = CMDRET_ZERO;
	पूर्णांक i = 0;

	अगर (snd_BUG_ON(!cअगर))
		वापस;

	snd_prपूर्णांकdd("Write AC97 reg 0x%x 0x%x\n", reg, val);
	करो अणु
		SEND_SACR(cअगर, val, reg);
		SEND_RACR(cअगर, reg, &rptr);
	पूर्ण जबतक (rptr.retwords[1] != val && i++ < MAX_WRITE_RETRY);
	अगर (i > MAX_WRITE_RETRY)
		snd_prपूर्णांकdd("Write AC97 reg failed\n");
पूर्ण

अटल अचिन्हित लघु snd_riptide_codec_पढ़ो(काष्ठा snd_ac97 *ac97,
					     अचिन्हित लघु reg)
अणु
	काष्ठा snd_riptide *chip = ac97->निजी_data;
	काष्ठा cmdअगर *cअगर = chip->cअगर;
	जोड़ cmdret rptr = CMDRET_ZERO;

	अगर (snd_BUG_ON(!cअगर))
		वापस 0;

	अगर (SEND_RACR(cअगर, reg, &rptr) != 0)
		SEND_RACR(cअगर, reg, &rptr);
	snd_prपूर्णांकdd("Read AC97 reg 0x%x got 0x%x\n", reg, rptr.retwords[1]);
	वापस rptr.retwords[1];
पूर्ण

अटल पूर्णांक snd_riptide_initialize(काष्ठा snd_riptide *chip)
अणु
	काष्ठा cmdअगर *cअगर;
	अचिन्हित पूर्णांक device_id;
	पूर्णांक err;

	अगर (snd_BUG_ON(!chip))
		वापस -EINVAL;

	cअगर = chip->cअगर;
	अगर (!cअगर) अणु
		अगर ((cअगर = kzalloc(माप(काष्ठा cmdअगर), GFP_KERNEL)) == शून्य)
			वापस -ENOMEM;
		cअगर->hwport = (काष्ठा riptideport *)chip->port;
		spin_lock_init(&cअगर->lock);
		chip->cअगर = cअगर;
	पूर्ण
	cअगर->is_reset = 0;
	अगर ((err = riptide_reset(cअगर, chip)) != 0)
		वापस err;
	device_id = chip->device_id;
	चयन (device_id) अणु
	हाल 0x4310:
	हाल 0x4320:
	हाल 0x4330:
		snd_prपूर्णांकdd("Modem enable?\n");
		SEND_SETDPLL(cअगर);
		अवरोध;
	पूर्ण
	snd_prपूर्णांकdd("Enabling MPU IRQs\n");
	अगर (chip->rmidi)
		SET_EMPUIRQ(cअगर->hwport);
	वापस err;
पूर्ण

अटल पूर्णांक snd_riptide_मुक्त(काष्ठा snd_riptide *chip)
अणु
	काष्ठा cmdअगर *cअगर;

	अगर (!chip)
		वापस 0;

	अगर ((cअगर = chip->cअगर)) अणु
		SET_GRESET(cअगर->hwport);
		udelay(100);
		UNSET_GRESET(cअगर->hwport);
		kमुक्त(chip->cअगर);
	पूर्ण
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, chip);
	release_firmware(chip->fw_entry);
	release_and_मुक्त_resource(chip->res_port);
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_riptide_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_riptide *chip = device->device_data;

	वापस snd_riptide_मुक्त(chip);
पूर्ण

अटल पूर्णांक
snd_riptide_create(काष्ठा snd_card *card, काष्ठा pci_dev *pci,
		   काष्ठा snd_riptide **rchip)
अणु
	काष्ठा snd_riptide *chip;
	काष्ठा riptideport *hwport;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_riptide_dev_मुक्त,
	पूर्ण;

	*rchip = शून्य;
	अगर ((err = pci_enable_device(pci)) < 0)
		वापस err;
	अगर (!(chip = kzalloc(माप(काष्ठा snd_riptide), GFP_KERNEL)))
		वापस -ENOMEM;

	spin_lock_init(&chip->lock);
	chip->card = card;
	chip->pci = pci;
	chip->irq = -1;
	chip->खोलोstreams = 0;
	chip->port = pci_resource_start(pci, 0);
	chip->received_irqs = 0;
	chip->handled_irqs = 0;
	chip->cअगर = शून्य;

	अगर ((chip->res_port =
	     request_region(chip->port, 64, "RIPTIDE")) == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR
			   "Riptide: unable to grab region 0x%lx-0x%lx\n",
			   chip->port, chip->port + 64 - 1);
		snd_riptide_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	hwport = (काष्ठा riptideport *)chip->port;
	UNSET_AIE(hwport);

	अगर (request_thपढ़ोed_irq(pci->irq, snd_riptide_पूर्णांकerrupt,
				 riptide_handleirq, IRQF_SHARED,
				 KBUILD_MODNAME, chip)) अणु
		snd_prपूर्णांकk(KERN_ERR "Riptide: unable to grab IRQ %d\n",
			   pci->irq);
		snd_riptide_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = pci->irq;
	card->sync_irq = chip->irq;
	chip->device_id = pci->device;
	pci_set_master(pci);
	अगर ((err = snd_riptide_initialize(chip)) < 0) अणु
		snd_riptide_मुक्त(chip);
		वापस err;
	पूर्ण

	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_riptide_मुक्त(chip);
		वापस err;
	पूर्ण

	*rchip = chip;
	वापस 0;
पूर्ण

अटल व्योम
snd_riptide_proc_पढ़ो(काष्ठा snd_info_entry *entry,
		      काष्ठा snd_info_buffer *buffer)
अणु
	काष्ठा snd_riptide *chip = entry->निजी_data;
	काष्ठा pcmhw *data;
	पूर्णांक i;
	काष्ठा cmdअगर *cअगर = शून्य;
	अचिन्हित अक्षर p[256];
	अचिन्हित लघु rval = 0, lval = 0;
	अचिन्हित पूर्णांक rate;

	अगर (!chip)
		वापस;

	snd_iम_लिखो(buffer, "%s\n\n", chip->card->दीर्घname);
	snd_iम_लिखो(buffer, "Device ID: 0x%x\nReceived IRQs: (%ld)%ld\nPorts:",
		    chip->device_id, chip->handled_irqs, chip->received_irqs);
	क्रम (i = 0; i < 64; i += 4)
		snd_iम_लिखो(buffer, "%c%02x: %08x",
			    (i % 16) ? ' ' : '\n', i, inl(chip->port + i));
	अगर ((cअगर = chip->cअगर)) अणु
		snd_iम_लिखो(buffer,
			    "\nVersion: ASIC: %d CODEC: %d AUXDSP: %d PROG: %d",
			    chip->firmware.firmware.ASIC,
			    chip->firmware.firmware.CODEC,
			    chip->firmware.firmware.AUXDSP,
			    chip->firmware.firmware.PROG);
		snd_iम_लिखो(buffer, "\nDigital mixer:");
		क्रम (i = 0; i < 12; i++) अणु
			geपंचांगixer(cअगर, i, &rval, &lval);
			snd_iम_लिखो(buffer, "\n %d: %d %d", i, rval, lval);
		पूर्ण
		snd_iम_लिखो(buffer,
			    "\nARM Commands num: %d failed: %d time: %d max: %d min: %d",
			    cअगर->cmdcnt, cअगर->errcnt,
			    cअगर->cmdसमय, cअगर->cmdसमयmax, cअगर->cmdसमयmin);
	पूर्ण
	snd_iम_लिखो(buffer, "\nOpen streams %d:\n", chip->खोलोstreams);
	क्रम (i = 0; i < PLAYBACK_SUBSTREAMS; i++) अणु
		अगर (chip->playback_substream[i]
		    && chip->playback_substream[i]->runसमय
		    && (data =
			chip->playback_substream[i]->runसमय->निजी_data)) अणु
			snd_iम_लिखो(buffer,
				    "stream: %d mixer: %d source: %d (%d,%d)\n",
				    data->id, data->mixer, data->source,
				    data->पूर्णांकdec[0], data->पूर्णांकdec[1]);
			अगर (!(माला_लोamplerate(cअगर, data->पूर्णांकdec, &rate)))
				snd_iम_लिखो(buffer, "rate: %d\n", rate);
		पूर्ण
	पूर्ण
	अगर (chip->capture_substream
	    && chip->capture_substream->runसमय
	    && (data = chip->capture_substream->runसमय->निजी_data)) अणु
		snd_iम_लिखो(buffer,
			    "stream: %d mixer: %d source: %d (%d,%d)\n",
			    data->id, data->mixer,
			    data->source, data->पूर्णांकdec[0], data->पूर्णांकdec[1]);
		अगर (!(माला_लोamplerate(cअगर, data->पूर्णांकdec, &rate)))
			snd_iम_लिखो(buffer, "rate: %d\n", rate);
	पूर्ण
	snd_iम_लिखो(buffer, "Paths:\n");
	i = getpaths(cअगर, p);
	जबतक (i >= 2) अणु
		i -= 2;
		snd_iम_लिखो(buffer, "%x->%x ", p[i], p[i + 1]);
	पूर्ण
	snd_iम_लिखो(buffer, "\n");
पूर्ण

अटल व्योम snd_riptide_proc_init(काष्ठा snd_riptide *chip)
अणु
	snd_card_ro_proc_new(chip->card, "riptide", chip,
			     snd_riptide_proc_पढ़ो);
पूर्ण

अटल पूर्णांक snd_riptide_mixer(काष्ठा snd_riptide *chip)
अणु
	काष्ठा snd_ac97_bus *pbus;
	काष्ठा snd_ac97_ढाँचा ac97;
	पूर्णांक err = 0;
	अटल स्थिर काष्ठा snd_ac97_bus_ops ops = अणु
		.ग_लिखो = snd_riptide_codec_ग_लिखो,
		.पढ़ो = snd_riptide_codec_पढ़ो,
	पूर्ण;

	स_रखो(&ac97, 0, माप(ac97));
	ac97.निजी_data = chip;
	ac97.scaps = AC97_SCAP_SKIP_MODEM;

	अगर ((err = snd_ac97_bus(chip->card, 0, &ops, chip, &pbus)) < 0)
		वापस err;

	chip->ac97_bus = pbus;
	ac97.pci = chip->pci;
	अगर ((err = snd_ac97_mixer(pbus, &ac97, &chip->ac97)) < 0)
		वापस err;
	वापस err;
पूर्ण

#अगर_घोषित SUPPORT_JOYSTICK

अटल पूर्णांक
snd_riptide_joystick_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *id)
अणु
	अटल पूर्णांक dev;
	काष्ठा gameport *gameport;
	पूर्णांक ret;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;

	अगर (!enable[dev]) अणु
		ret = -ENOENT;
		जाओ inc_dev;
	पूर्ण

	अगर (!joystick_port[dev]) अणु
		ret = 0;
		जाओ inc_dev;
	पूर्ण

	gameport = gameport_allocate_port();
	अगर (!gameport) अणु
		ret = -ENOMEM;
		जाओ inc_dev;
	पूर्ण
	अगर (!request_region(joystick_port[dev], 8, "Riptide gameport")) अणु
		snd_prपूर्णांकk(KERN_WARNING
			   "Riptide: cannot grab gameport 0x%x\n",
			   joystick_port[dev]);
		gameport_मुक्त_port(gameport);
		ret = -EBUSY;
		जाओ inc_dev;
	पूर्ण

	gameport->io = joystick_port[dev];
	gameport_रेजिस्टर_port(gameport);
	pci_set_drvdata(pci, gameport);

	ret = 0;
inc_dev:
	dev++;
	वापस ret;
पूर्ण

अटल व्योम snd_riptide_joystick_हटाओ(काष्ठा pci_dev *pci)
अणु
	काष्ठा gameport *gameport = pci_get_drvdata(pci);
	अगर (gameport) अणु
		release_region(gameport->io, 8);
		gameport_unरेजिस्टर_port(gameport);
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक
snd_card_riptide_probe(काष्ठा pci_dev *pci, स्थिर काष्ठा pci_device_id *pci_id)
अणु
	अटल पूर्णांक dev;
	काष्ठा snd_card *card;
	काष्ठा snd_riptide *chip;
	अचिन्हित लघु val;
	पूर्णांक err;

	अगर (dev >= SNDRV_CARDS)
		वापस -ENODEV;
	अगर (!enable[dev]) अणु
		dev++;
		वापस -ENOENT;
	पूर्ण

	err = snd_card_new(&pci->dev, index[dev], id[dev], THIS_MODULE,
			   0, &card);
	अगर (err < 0)
		वापस err;
	err = snd_riptide_create(card, pci, &chip);
	अगर (err < 0)
		जाओ error;
	card->निजी_data = chip;
	err = snd_riptide_pcm(chip, 0);
	अगर (err < 0)
		जाओ error;
	err = snd_riptide_mixer(chip);
	अगर (err < 0)
		जाओ error;

	val = LEGACY_ENABLE_ALL;
	अगर (opl3_port[dev])
		val |= LEGACY_ENABLE_FM;
#अगर_घोषित SUPPORT_JOYSTICK
	अगर (joystick_port[dev])
		val |= LEGACY_ENABLE_GAMEPORT;
#पूर्ण_अगर
	अगर (mpu_port[dev])
		val |= LEGACY_ENABLE_MPU_INT | LEGACY_ENABLE_MPU;
	val |= (chip->irq << 4) & 0xf0;
	pci_ग_लिखो_config_word(chip->pci, PCI_EXT_Legacy_Mask, val);
	अगर (mpu_port[dev]) अणु
		val = mpu_port[dev];
		pci_ग_लिखो_config_word(chip->pci, PCI_EXT_MPU_Base, val);
		err = snd_mpu401_uart_new(card, 0, MPU401_HW_RIPTIDE,
					  val, MPU401_INFO_IRQ_HOOK, -1,
					  &chip->rmidi);
		अगर (err < 0)
			snd_prपूर्णांकk(KERN_WARNING
				   "Riptide: Can't Allocate MPU at 0x%x\n",
				   val);
		अन्यथा
			chip->mpuaddr = val;
	पूर्ण
	अगर (opl3_port[dev]) अणु
		val = opl3_port[dev];
		pci_ग_लिखो_config_word(chip->pci, PCI_EXT_FM_Base, val);
		err = snd_opl3_create(card, val, val + 2,
				      OPL3_HW_RIPTIDE, 0, &chip->opl3);
		अगर (err < 0)
			snd_prपूर्णांकk(KERN_WARNING
				   "Riptide: Can't Allocate OPL3 at 0x%x\n",
				   val);
		अन्यथा अणु
			chip->opladdr = val;
			err = snd_opl3_hwdep_new(chip->opl3, 0, 1, शून्य);
			अगर (err < 0)
				snd_prपूर्णांकk(KERN_WARNING
					   "Riptide: Can't Allocate OPL3-HWDEP\n");
		पूर्ण
	पूर्ण
#अगर_घोषित SUPPORT_JOYSTICK
	अगर (joystick_port[dev]) अणु
		val = joystick_port[dev];
		pci_ग_लिखो_config_word(chip->pci, PCI_EXT_Game_Base, val);
		chip->gameaddr = val;
	पूर्ण
#पूर्ण_अगर

	म_नकल(card->driver, "RIPTIDE");
	म_नकल(card->लघुname, "Riptide");
#अगर_घोषित SUPPORT_JOYSTICK
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s at 0x%lx, irq %i mpu 0x%x opl3 0x%x gameport 0x%x",
		 card->लघुname, chip->port, chip->irq, chip->mpuaddr,
		 chip->opladdr, chip->gameaddr);
#अन्यथा
	snम_लिखो(card->दीर्घname, माप(card->दीर्घname),
		 "%s at 0x%lx, irq %i mpu 0x%x opl3 0x%x",
		 card->लघुname, chip->port, chip->irq, chip->mpuaddr,
		 chip->opladdr);
#पूर्ण_अगर
	snd_riptide_proc_init(chip);
	err = snd_card_रेजिस्टर(card);
	अगर (err < 0)
		जाओ error;
	pci_set_drvdata(pci, card);
	dev++;
	वापस 0;

 error:
	snd_card_मुक्त(card);
	वापस err;
पूर्ण

अटल व्योम snd_card_riptide_हटाओ(काष्ठा pci_dev *pci)
अणु
	snd_card_मुक्त(pci_get_drvdata(pci));
पूर्ण

अटल काष्ठा pci_driver driver = अणु
	.name = KBUILD_MODNAME,
	.id_table = snd_riptide_ids,
	.probe = snd_card_riptide_probe,
	.हटाओ = snd_card_riptide_हटाओ,
	.driver = अणु
		.pm = RIPTIDE_PM_OPS,
	पूर्ण,
पूर्ण;

#अगर_घोषित SUPPORT_JOYSTICK
अटल काष्ठा pci_driver joystick_driver = अणु
	.name = KBUILD_MODNAME "-joystick",
	.id_table = snd_riptide_joystick_ids,
	.probe = snd_riptide_joystick_probe,
	.हटाओ = snd_riptide_joystick_हटाओ,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक __init alsa_card_riptide_init(व्योम)
अणु
	पूर्णांक err;
	err = pci_रेजिस्टर_driver(&driver);
	अगर (err < 0)
		वापस err;
#अगर defined(SUPPORT_JOYSTICK)
	err = pci_रेजिस्टर_driver(&joystick_driver);
	/* On failure unरेजिस्टर क्रमmerly रेजिस्टरed audio driver */
	अगर (err < 0)
		pci_unरेजिस्टर_driver(&driver);
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम __निकास alsa_card_riptide_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&driver);
#अगर defined(SUPPORT_JOYSTICK)
	pci_unरेजिस्टर_driver(&joystick_driver);
#पूर्ण_अगर
पूर्ण

module_init(alsa_card_riptide_init);
module_निकास(alsa_card_riptide_निकास);
