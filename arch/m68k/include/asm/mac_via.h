<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *	6522 Versatile Interface Adapter (VIA)
 *
 *	There are two of these on the Mac II. Some IRQ's are vectored
 *	via them as are assorted bits and bobs - eg rtc, adb. The picture
 *	is a bit incomplete as the Mac करोcumentation करोesn't cover this well
 */

#अगर_अघोषित _ASM_MAC_VIA_H_
#घोषणा _ASM_MAC_VIA_H_

/*
 * Base addresses क्रम the VIAs. There are two in every machine,
 * although on some machines the second is an RBV or an OSS.
 * The OSS is dअगरferent enough that it's handled separately.
 *
 * Do not use these values directly; use the via1 and via2 variables
 * instead (and करोn't क्रमget to check rbv_present when using via2!)
 */

#घोषणा VIA1_BASE	(0x50F00000)
#घोषणा VIA2_BASE	(0x50F02000)
#घोषणा  RBV_BASE	(0x50F26000)

/*
 *	Not all of these are true post MacII I think.
 *      CSA: probably the ones CHRP marks as 'unused' change purposes
 *      when the IWM becomes the SWIM.
 *      http://www.rs6000.ibm.com/resource/technology/chrpio/via5.mak.hपंचांगl
 *      ftp://ftp.austin.ibm.com/pub/technology/spec/chrp/inwork/CHRP_IORef_1.0.pdf
 *
 * also, http://developer.apple.com/technotes/hw/hw_09.hपंचांगl claims the
 * following changes क्रम IIfx:
 * VIA1A_vSccWrReq not available and that VIA1A_vSync has moved to an IOP.
 * Also, "All of the functionality of VIA2 has been moved to other chips".
 */

#घोषणा VIA1A_vSccWrReq	0x80	/* SCC ग_लिखो. (input)
				 * [CHRP] SCC WREQ: Reflects the state of the
				 * Wait/Request pins from the SCC.
				 * [Macपूर्णांकosh Family Hardware]
				 * as CHRP on SE/30,II,IIx,IIcx,IIci.
				 * on IIfx, "0 means an active request"
				 */
#घोषणा VIA1A_vRev8	0x40	/* Revision 8 board ???
                                 * [CHRP] En WaitReqB: Lets the WaitReq_L
				 * संकेत from port B of the SCC appear on
				 * the PA7 input pin. Output.
				 * [Macपूर्णांकosh Family] On the SE/30, this
				 * is the bit to flip screen buffers.
				 * 0=alternate, 1=मुख्य.
				 * on II,IIx,IIcx,IIci,IIfx this is a bit
				 * क्रम Rev ID. 0=II,IIx, 1=IIcx,IIci,IIfx
				 */
#घोषणा VIA1A_vHeadSel	0x20	/* Head select क्रम IWM.
				 * [CHRP] unused.
				 * [Macपूर्णांकosh Family] "Floppy disk
				 * state-control line SEL" on all but IIfx
				 */
#घोषणा VIA1A_vOverlay	0x10    /* [Macपूर्णांकosh Family] On SE/30,II,IIx,IIcx
				 * this bit enables the "Overlay" address
				 * map in the address decoders as it is on
				 * reset क्रम mapping the ROM over the reset
				 * vector. 1=use overlay map.
				 * On the IIci,IIfx it is another bit of the
				 * CPU ID: 0=normal IIci, 1=IIci with parity
				 * feature or IIfx.
				 * [CHRP] En WaitReqA: Lets the WaitReq_L
				 * संकेत from port A of the SCC appear
				 * on the PA7 input pin (CHRP). Output.
				 * [MkLinux] "Drive Select"
				 *  (with 0x20 being 'disk head select')
				 */
#घोषणा VIA1A_vSync	0x08    /* [CHRP] Sync Modem: modem घड़ी select:
                                 * 1: select the बाह्यal serial घड़ी to
				 *    drive the SCC's /RTxCA pin.
				 * 0: Select the 3.6864MHz घड़ी to drive
				 *    the SCC cell.
				 * [Macपूर्णांकosh Family] Correct on all but IIfx
				 */

/* Macपूर्णांकosh Family Hardware sez: bits 0-2 of VIA1A are volume control
 * on Macs which had the PWM sound hardware.  Reserved on newer models.
 * On IIci,IIfx, bits 1-2 are the rest of the CPU ID:
 * bit 2: 1=IIci, 0=IIfx
 * bit 1: 1 on both IIci and IIfx.
 * MkLinux sez bit 0 is 'burnin flag' in this हाल.
 * CHRP sez: VIA1A bits 0-2 and 5 are 'unused': अगर programmed as
 * inमाला_दो, these bits will पढ़ो 0.
 */
#घोषणा VIA1A_vVolume	0x07	/* Audio volume mask क्रम PWM */
#घोषणा VIA1A_CPUID0	0x02	/* CPU id bit 0 on RBV, others */
#घोषणा VIA1A_CPUID1	0x04	/* CPU id bit 0 on RBV, others */
#घोषणा VIA1A_CPUID2	0x10	/* CPU id bit 0 on RBV, others */
#घोषणा VIA1A_CPUID3	0x40	/* CPU id bit 0 on RBV, others */

/* Info on VIA1B is from Macपूर्णांकosh Family Hardware & MkLinux.
 * CHRP offers no info. */
#घोषणा VIA1B_vSound	0x80	/* Sound enable (क्रम compatibility with
				 * PWM hardware) 0=enabled.
				 * Also, on IIci w/parity, shows parity error
				 * 0=error, 1=OK. */
#घोषणा VIA1B_vMystery	0x40    /* On IIci, parity enable. 0=enabled,1=disabled
				 * On SE/30, vertical sync पूर्णांकerrupt enable.
				 * 0=enabled. This vSync पूर्णांकerrupt shows up
				 * as a slot $E पूर्णांकerrupt. */
#घोषणा VIA1B_vADBS2	0x20	/* ADB state input bit 1 (unused on IIfx) */
#घोषणा VIA1B_vADBS1	0x10	/* ADB state input bit 0 (unused on IIfx) */
#घोषणा VIA1B_vADBInt	0x08	/* ADB पूर्णांकerrupt 0=पूर्णांकerrupt (unused on IIfx)*/
#घोषणा VIA1B_vRTCEnb	0x04	/* Enable Real समय घड़ी. 0=enabled. */
#घोषणा VIA1B_vRTCClk	0x02    /* Real समय घड़ी serial-घड़ी line. */
#घोषणा VIA1B_vRTCData	0x01    /* Real समय घड़ी serial-data line. */

/* MkLinux defines the following "VIA1 Register B contents where they
 * dअगरfer from standard VIA1".  From the naming scheme, we assume they
 * correspond to a VIA work-alike named 'EVR'. */
#घोषणा	EVRB_XCVR	0x08	/* XCVR_SESSION* */
#घोषणा	EVRB_FULL	0x10	/* VIA_FULL */
#घोषणा	EVRB_SYSES	0x20	/* SYS_SESSION */
#घोषणा	EVRB_AUXIE	0x00	/* Enable A/UX Interrupt Scheme */
#घोषणा	EVRB_AUXID	0x40	/* Disable A/UX Interrupt Scheme */
#घोषणा	EVRB_SFTWRIE	0x00	/* Software Interrupt ReQuest */
#घोषणा	EVRB_SFTWRID	0x80	/* Software Interrupt ReQuest */

/*
 *	VIA2 A रेजिस्टर is the पूर्णांकerrupt lines उठाओd off the nubus
 *	slots.
 *      The below info is from 'Macintosh Family Hardware.'
 *      MkLinux calls the 'IIci internal video IRQ' below the 'RBV slot 0 irq.'
 *      It also notes that the slot $9 IRQ is the 'Ethernet IRQ' and
 *      defines the 'Video IRQ' as 0x40 for the 'EVR' VIA work-alike.
 *      Perhaps OSS uses vRAM1 and vRAM2 क्रम ADB.
 */

#घोषणा VIA2A_vRAM1	0x80	/* RAM size bit 1 (IIci: reserved) */
#घोषणा VIA2A_vRAM0	0x40	/* RAM size bit 0 (IIci: पूर्णांकernal video IRQ) */
#घोषणा VIA2A_vIRQE	0x20	/* IRQ from slot $E */
#घोषणा VIA2A_vIRQD	0x10	/* IRQ from slot $D */
#घोषणा VIA2A_vIRQC	0x08	/* IRQ from slot $C */
#घोषणा VIA2A_vIRQB	0x04	/* IRQ from slot $B */
#घोषणा VIA2A_vIRQA	0x02	/* IRQ from slot $A */
#घोषणा VIA2A_vIRQ9	0x01	/* IRQ from slot $9 */

/* RAM size bits decoded as follows:
 * bit1 bit0  size of ICs in bank A
 *  0    0    256 kbit
 *  0    1    1 Mbit
 *  1    0    4 Mbit
 *  1    1   16 Mbit
 */

/*
 *	Register B has the fun stuff in it
 */

#घोषणा VIA2B_vVBL	0x80	/* VBL output to VIA1 (60.15Hz) driven by
				 * समयr T1.
				 * on IIci, parity test: 0=test mode.
				 * [MkLinux] RBV_PARODD: 1=odd,0=even. */
#घोषणा VIA2B_vSndJck	0x40	/* External sound jack status.
				 * 0=plug is inserted.  On SE/30, always 0 */
#घोषणा VIA2B_vTfr0	0x20	/* Transfer mode bit 0 ack from NuBus */
#घोषणा VIA2B_vTfr1	0x10	/* Transfer mode bit 1 ack from NuBus */
#घोषणा VIA2B_vMode32	0x08	/* 24/32bit चयन - द्विगुनs as cache flush
				 * on II, AMU/PMMU control.
				 *   अगर AMU, 0=24bit to 32bit translation
				 *   अगर PMMU, 1=PMMU is accessing page table.
				 * on SE/30 tied low.
				 * on IIx,IIcx,IIfx, unused.
				 * on IIci/RBV, cache control. 0=flush cache.
				 */
#घोषणा VIA2B_vPower	0x04	/* Power off, 0=shut off घातer.
				 * on SE/30 this संकेत sent to PDS card. */
#घोषणा VIA2B_vBusLk	0x02	/* Lock NuBus transactions, 0=locked.
				 * on SE/30 sent to PDS card. */
#घोषणा VIA2B_vCDis	0x01	/* Cache control. On IIci, 1=disable cache card
				 * on others, 0=disable processor's inकाष्ठाion
				 * and data caches. */

/* Apple sez: http://developer.apple.com/technotes/ov/ov_04.hपंचांगl
 * Another example of a valid function that has no ROM support is the use
 * of the alternate video page क्रम page-flipping animation. Since there
 * is no ROM call to flip pages, it is necessary to go play with the
 * right bit in the VIA chip (6522 Versatile Interface Adapter).
 * [CSA: करोn't know which one this is, but it's one of 'em!]
 */

/*
 *	6522 रेजिस्टरs - see databook.
 * CSA: Assignments क्रम VIA1 confirmed from CHRP spec.
 */

/* partial address decode.  0xYYXX : XX part क्रम RBV, YY part क्रम VIA */
/* Note: 15 VIA regs, 8 RBV regs */

#घोषणा vBufB	0x0000	/* [VIA/RBV]  Register B */
#घोषणा vBufAH	0x0200  /* [VIA only] Buffer A, with handshake. DON'T USE! */
#घोषणा vDirB	0x0400  /* [VIA only] Data Direction Register B. */
#घोषणा vDirA	0x0600  /* [VIA only] Data Direction Register A. */
#घोषणा vT1CL	0x0800  /* [VIA only] Timer one counter low. */
#घोषणा vT1CH	0x0a00  /* [VIA only] Timer one counter high. */
#घोषणा vT1LL	0x0c00  /* [VIA only] Timer one latches low. */
#घोषणा vT1LH	0x0e00  /* [VIA only] Timer one latches high. */
#घोषणा vT2CL	0x1000  /* [VIA only] Timer two counter low. */
#घोषणा vT2CH	0x1200  /* [VIA only] Timer two counter high. */
#घोषणा vSR	0x1400  /* [VIA only] Shअगरt रेजिस्टर. */
#घोषणा vACR	0x1600  /* [VIA only] Auxiliary control रेजिस्टर. */
#घोषणा vPCR	0x1800  /* [VIA only] Peripheral control रेजिस्टर. */
                        /*            CHRP sez never ever to *ग_लिखो* this.
			 *            Mac family says never to *change* this.
			 * In fact we need to initialize it once at start. */
#घोषणा vIFR	0x1a00  /* [VIA/RBV]  Interrupt flag रेजिस्टर. */
#घोषणा vIER	0x1c00  /* [VIA/RBV]  Interrupt enable रेजिस्टर. */
#घोषणा vBufA	0x1e00  /* [VIA/RBV] रेजिस्टर A (no handshake) */

/* The RBV only decodes the bottom eight address lines; the VIA करोesn't
 * decode the bottom eight -- so vBufB | rBufB will always get you BufB */
/* CSA: in fact, only bits 0,1, and 4 seem to be decoded.
 * BUT note the values क्रम rIER and rIFR, where the top 8 bits *करो* seem
 * to matter.  In fact *all* of the top 8 bits seem to matter;
 * setting rIER=0x1813 and rIFR=0x1803 करोesn't work, either.
 * Perhaps some sort of 'compatibility mode' is built-in? [21-May-1999]
 */

#घोषणा rBufB   0x0000  /* [VIA/RBV]  Register B */
#घोषणा rExp	0x0001	/* [RBV only] RBV future expansion (always 0) */
#घोषणा rSIFR	0x0002  /* [RBV only] RBV slot पूर्णांकerrupts रेजिस्टर. */
#घोषणा rIFR	0x1a03  /* [VIA/RBV]  RBV पूर्णांकerrupt flag रेजिस्टर. */
#घोषणा rMonP   0x0010  /* [RBV only] RBV video monitor type. */
#घोषणा rChpT   0x0011  /* [RBV only] RBV test mode रेजिस्टर (पढ़ोs as 0). */
#घोषणा rSIER   0x0012  /* [RBV only] RBV slot पूर्णांकerrupt enables. */
#घोषणा rIER    0x1c13  /* [VIA/RBV]  RBV पूर्णांकerrupt flag enable रेजिस्टर. */
#घोषणा rBufA	rSIFR   /* the 'slot interrupts register' is BufA on a VIA */

/*
 * Video monitor parameters, क्रम rMonP:
 */
#घोषणा RBV_DEPTH  0x07	/* bits per pixel: 000=1,001=2,010=4,011=8 */
#घोषणा RBV_MONID  0x38	/* monitor type, as below. */
#घोषणा RBV_VIDOFF 0x40	/* 1 turns off onboard video */
/* Supported monitor types: */
#घोषणा MON_15BW   (1<<3) /* 15" BW portrait. */
#घोषणा MON_IIGS   (2<<3) /* 12" color (modअगरied IIGS monitor). */
#घोषणा MON_15RGB  (5<<3) /* 15" RGB portrait. */
#घोषणा MON_12OR13 (6<<3) /* 12" BW or 13" RGB. */
#घोषणा MON_NONE   (7<<3) /* No monitor attached. */

/* To clarअगरy IER manipulations */
#घोषणा IER_SET_BIT(b) (0x80 | (1<<(b)) )
#घोषणा IER_CLR_BIT(b) (0x7F & (1<<(b)) )

#अगर_अघोषित __ASSEMBLY__

बाह्य अस्थिर __u8 *via1,*via2;
बाह्य पूर्णांक rbv_present,via_alt_mapping;

काष्ठा irq_desc;

बाह्य व्योम via_l2_flush(पूर्णांक ग_लिखोback);
बाह्य व्योम via_रेजिस्टर_पूर्णांकerrupts(व्योम);
बाह्य व्योम via_irq_enable(पूर्णांक);
बाह्य व्योम via_irq_disable(पूर्णांक);
बाह्य व्योम via_nubus_irq_startup(पूर्णांक irq);
बाह्य व्योम via_nubus_irq_shutकरोwn(पूर्णांक irq);
बाह्य व्योम via1_irq(काष्ठा irq_desc *desc);
बाह्य व्योम via1_set_head(पूर्णांक);
बाह्य पूर्णांक via2_scsi_drq_pending(व्योम);

अटल अंतरभूत पूर्णांक rbv_set_video_bpp(पूर्णांक bpp)
अणु
	अक्षर val = (bpp==1)?0:(bpp==2)?1:(bpp==4)?2:(bpp==8)?3:-1;
	अगर (!rbv_present || val<0) वापस -1;
	via2[rMonP] = (via2[rMonP] & ~RBV_DEPTH) | val;
	वापस 0;
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_MAC_VIA_H_ */
