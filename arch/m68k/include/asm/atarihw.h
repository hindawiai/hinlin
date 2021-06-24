<शैली गुरु>
/*
** linux/atarihw.h -- This header defines some macros and poपूर्णांकers क्रम
**                    the various Atari custom hardware रेजिस्टरs.
**
** Copyright 1994 by Bjथघrn Brauel
**
** 5/1/94 Roman Hodek:
**   Added definitions क्रम TT specअगरic chips.
**
** 1996-09-13 lars brinkhoff <f93labr@dd.chalmers.se>:
**   Finally added definitions क्रम the matrix/codec and the DSP56001 host
**   पूर्णांकerface.
**
** This file is subject to the terms and conditions of the GNU General Public
** License.  See the file COPYING in the मुख्य directory of this archive
** क्रम more details.
**
*/

#अगर_अघोषित _LINUX_ATARIHW_H_
#घोषणा _LINUX_ATARIHW_H_

#समावेश <linux/types.h>
#समावेश <यंत्र/bootinfo-atari.h>
#समावेश <यंत्र/kmap.h>

बाह्य u_दीर्घ atari_mch_cookie;
बाह्य u_दीर्घ atari_mch_type;
बाह्य u_दीर्घ atari_चयनes;
बाह्य पूर्णांक atari_rtc_year_offset;
बाह्य पूर्णांक atari_करोnt_touch_floppy_select;

बाह्य पूर्णांक atari_SCC_reset_करोne;

बाह्य sमाप_प्रकार atari_nvram_पढ़ो(अक्षर *, माप_प्रकार, loff_t *);
बाह्य sमाप_प्रकार atari_nvram_ग_लिखो(अक्षर *, माप_प्रकार, loff_t *);
बाह्य sमाप_प्रकार atari_nvram_get_size(व्योम);
बाह्य दीर्घ atari_nvram_set_checksum(व्योम);
बाह्य दीर्घ atari_nvram_initialize(व्योम);

/* convenience macros क्रम testing machine type */
#घोषणा MACH_IS_ST	((atari_mch_cookie >> 16) == ATARI_MCH_ST)
#घोषणा MACH_IS_STE	((atari_mch_cookie >> 16) == ATARI_MCH_STE && \
			 (atari_mch_cookie & 0xffff) == 0)
#घोषणा MACH_IS_MSTE	((atari_mch_cookie >> 16) == ATARI_MCH_STE && \
			 (atari_mch_cookie & 0xffff) == 0x10)
#घोषणा MACH_IS_TT	((atari_mch_cookie >> 16) == ATARI_MCH_TT)
#घोषणा MACH_IS_FALCON	((atari_mch_cookie >> 16) == ATARI_MCH_FALCON)
#घोषणा MACH_IS_MEDUSA	(atari_mch_type == ATARI_MACH_MEDUSA)
#घोषणा MACH_IS_AB40	(atari_mch_type == ATARI_MACH_AB40)

/* values क्रम atari_चयनes */
#घोषणा ATARI_SWITCH_IKBD	0x01
#घोषणा ATARI_SWITCH_MIDI	0x02
#घोषणा ATARI_SWITCH_SND6	0x04
#घोषणा ATARI_SWITCH_SND7	0x08
#घोषणा ATARI_SWITCH_OVSC_SHIFT	16
#घोषणा ATARI_SWITCH_OVSC_IKBD	(ATARI_SWITCH_IKBD << ATARI_SWITCH_OVSC_SHIFT)
#घोषणा ATARI_SWITCH_OVSC_MIDI	(ATARI_SWITCH_MIDI << ATARI_SWITCH_OVSC_SHIFT)
#घोषणा ATARI_SWITCH_OVSC_SND6	(ATARI_SWITCH_SND6 << ATARI_SWITCH_OVSC_SHIFT)
#घोषणा ATARI_SWITCH_OVSC_SND7	(ATARI_SWITCH_SND7 << ATARI_SWITCH_OVSC_SHIFT)
#घोषणा ATARI_SWITCH_OVSC_MASK	0xffff0000

/*
 * Define several Hardware-Chips क्रम indication so that क्रम the ATARI we करो
 * no दीर्घer decide whether it is a Falcon or other machine . It's just
 * important what hardware the machine uses
 */

/* ++roman 08/08/95: rewritten from ORing स्थिरants to a C bitfield */

#घोषणा ATARIHW_DECLARE(name)	अचिन्हित name : 1
#घोषणा ATARIHW_SET(name)	(atari_hw_present.name = 1)
#घोषणा ATARIHW_PRESENT(name)	(atari_hw_present.name)

काष्ठा atari_hw_present अणु
    /* video hardware */
    ATARIHW_DECLARE(STND_SHIFTER);	/* ST-Shअगरter - no base low ! */
    ATARIHW_DECLARE(EXTD_SHIFTER);	/* STe-Shअगरter - 24 bit address */
    ATARIHW_DECLARE(TT_SHIFTER);	/* TT-Shअगरter */
    ATARIHW_DECLARE(VIDEL_SHIFTER);	/* Falcon-Shअगरter */
    /* sound hardware */
    ATARIHW_DECLARE(YM_2149);		/* Yamaha YM 2149 */
    ATARIHW_DECLARE(PCM_8BIT);		/* PCM-Sound in STe-ATARI */
    ATARIHW_DECLARE(CODEC);		/* CODEC Sound (Falcon) */
    /* disk storage पूर्णांकerfaces */
    ATARIHW_DECLARE(TT_SCSI);		/* Directly mapped NCR5380 */
    ATARIHW_DECLARE(ST_SCSI);		/* NCR5380 via ST-DMA (Falcon) */
    ATARIHW_DECLARE(ACSI);		/* Standard ACSI like in STs */
    ATARIHW_DECLARE(IDE);		/* IDE Interface */
    ATARIHW_DECLARE(FDCSPEED);		/* 8/16 MHz चयन क्रम FDC */
    /* other I/O hardware */
    ATARIHW_DECLARE(ST_MFP);		/* The ST-MFP (there should be no Atari
					   without it... but who knows?) */
    ATARIHW_DECLARE(TT_MFP);		/* 2nd MFP */
    ATARIHW_DECLARE(SCC);		/* Serial Communications Contr. */
    ATARIHW_DECLARE(ST_ESCC);		/* SCC Z83230 in an ST */
    ATARIHW_DECLARE(ANALOG_JOY);	/* Paddle Interface क्रम STe
					   and Falcon */
    ATARIHW_DECLARE(MICROWIRE);		/* Microwire Interface */
    /* DMA */
    ATARIHW_DECLARE(STND_DMA);		/* 24 Bit limited ST-DMA */
    ATARIHW_DECLARE(EXTD_DMA);		/* 32 Bit ST-DMA */
    ATARIHW_DECLARE(SCSI_DMA);		/* DMA क्रम the NCR5380 */
    ATARIHW_DECLARE(SCC_DMA);		/* DMA क्रम the SCC */
    /* real समय घड़ीs */
    ATARIHW_DECLARE(TT_CLK);		/* TT compatible घड़ी chip */
    ATARIHW_DECLARE(MSTE_CLK);		/* Mega ST(E) घड़ी chip */
    /* supporting hardware */
    ATARIHW_DECLARE(SCU);		/* System Control Unit */
    ATARIHW_DECLARE(BLITTER);		/* Blitter */
    ATARIHW_DECLARE(VME);		/* VME Bus */
    ATARIHW_DECLARE(DSP56K);		/* DSP56k processor in Falcon */
पूर्ण;

बाह्य काष्ठा atari_hw_present atari_hw_present;


/* Reading the MFP port रेजिस्टर gives a machine independent delay, since the
 * MFP always has a 8 MHz घड़ी. This aव्योमs problems with the varying length
 * of nops on various machines. Somebody claimed that the tstb takes 600 ns.
 */
#घोषणा	MFPDELAY() \
	__यंत्र__ __अस्थिर__ ( "tstb %0" : : "m" (st_mfp.par_dt_reg) : "cc" );

/* Do cache push/invalidate क्रम DMA पढ़ो/ग_लिखो. This function obeys the
 * snooping on some machines (Medusa) and processors: The Medusa itself can
 * snoop, but only the '040 can source data from its cache to DMA ग_लिखोs i.e.,
 * पढ़ोs from memory). Both '040 and '060 invalidate cache entries on snooped
 * DMA पढ़ोs (i.e., ग_लिखोs to memory).
 */


#समावेश <linux/mm.h>
#समावेश <यंत्र/cacheflush.h>

अटल अंतरभूत व्योम dma_cache_मुख्यtenance( अचिन्हित दीर्घ paddr,
					  अचिन्हित दीर्घ len,
					  पूर्णांक ग_लिखोflag )

अणु
	अगर (ग_लिखोflag) अणु
		अगर (!MACH_IS_MEDUSA || CPU_IS_060)
			cache_push( paddr, len );
	पूर्ण
	अन्यथा अणु
		अगर (!MACH_IS_MEDUSA)
			cache_clear( paddr, len );
	पूर्ण
पूर्ण


/*
** Shअगरter
 */
#घोषणा ST_LOW  0
#घोषणा ST_MID  1
#घोषणा ST_HIGH 2
#घोषणा TT_LOW  7
#घोषणा TT_MID  4
#घोषणा TT_HIGH 6

#घोषणा SHF_BAS (0xffff8200)
काष्ठा SHIFTER_ST
 अणु
	u_अक्षर pad1;
	u_अक्षर bas_hi;
	u_अक्षर pad2;
	u_अक्षर bas_md;
	u_अक्षर pad3;
	u_अक्षर अस्थिर vcounthi;
	u_अक्षर pad4;
	u_अक्षर अस्थिर vcounपंचांगid;
	u_अक्षर pad5;
	u_अक्षर अस्थिर vcountlow;
	u_अक्षर अस्थिर syncmode;
	u_अक्षर pad6;
	u_अक्षर pad7;
	u_अक्षर bas_lo;
 पूर्ण;
# define shअगरter_st ((*(अस्थिर काष्ठा SHIFTER_ST *)SHF_BAS))

#घोषणा SHF_FBAS (0xffff820e)
काष्ठा SHIFTER_F030
 अणु
  u_लघु off_next;
  u_लघु scn_width;
 पूर्ण;
# define shअगरter_f030 ((*(अस्थिर काष्ठा SHIFTER_F030 *)SHF_FBAS))


#घोषणा	SHF_TBAS (0xffff8200)
काष्ठा SHIFTER_TT अणु
	u_अक्षर	अक्षर_dummy0;
	u_अक्षर	bas_hi;			/* video mem base addr, high and mid byte */
	u_अक्षर	अक्षर_dummy1;
	u_अक्षर	bas_md;
	u_अक्षर	अक्षर_dummy2;
	u_अक्षर	vcount_hi;		/* poपूर्णांकer to currently displayed byte */
	u_अक्षर	अक्षर_dummy3;
	u_अक्षर	vcount_md;
	u_अक्षर	अक्षर_dummy4;
	u_अक्षर	vcount_lo;
	u_लघु	st_sync;		/* ST compatible sync mode रेजिस्टर, unused */
	u_अक्षर	अक्षर_dummy5;
	u_अक्षर	bas_lo;			/* video mem addr, low byte */
	u_अक्षर	अक्षर_dummy6[2+3*16];
	/* $ffff8240: */
	u_लघु	color_reg[16];	/* 16 color रेजिस्टरs */
	u_अक्षर	st_shअगरपंचांगode;	/* ST compatible shअगरt mode रेजिस्टर, unused */
	u_अक्षर  अक्षर_dummy7;
	u_लघु tt_shअगरपंचांगode;	/* TT shअगरt mode रेजिस्टर */


पूर्ण;
#घोषणा	shअगरter_tt	((*(अस्थिर काष्ठा SHIFTER_TT *)SHF_TBAS))

/* values क्रम shअगरter_tt->tt_shअगरपंचांगode */
#घोषणा	TT_SHIFTER_STLOW		0x0000
#घोषणा	TT_SHIFTER_STMID		0x0100
#घोषणा	TT_SHIFTER_STHIGH		0x0200
#घोषणा	TT_SHIFTER_TTLOW		0x0700
#घोषणा	TT_SHIFTER_TTMID		0x0400
#घोषणा	TT_SHIFTER_TTHIGH		0x0600
#घोषणा	TT_SHIFTER_MODEMASK	0x0700
#घोषणा TT_SHIFTER_NUMMODE	0x0008
#घोषणा	TT_SHIFTER_PALETTE_MASK	0x000f
#घोषणा	TT_SHIFTER_GRAYMODE		0x1000

/* 256 TT palette रेजिस्टरs */
#घोषणा	TT_PALETTE_BASE	(0xffff8400)
#घोषणा	tt_palette	((अस्थिर u_लघु *)TT_PALETTE_BASE)

#घोषणा	TT_PALETTE_RED_MASK		0x0f00
#घोषणा	TT_PALETTE_GREEN_MASK	0x00f0
#घोषणा	TT_PALETTE_BLUE_MASK	0x000f

/*
** Falcon030 VIDEL Video Controller
** क्रम description see File 'linux\टools\चtari\hardware.txt
 */
#घोषणा f030_col ((u_दीर्घ *)		0xffff9800)
#घोषणा f030_xreg ((u_लघु*)		0xffff8282)
#घोषणा f030_yreg ((u_लघु*)		0xffff82a2)
#घोषणा f030_creg ((u_लघु*)		0xffff82c0)
#घोषणा f030_sreg ((u_लघु*)		0xffff8260)
#घोषणा f030_mreg ((u_लघु*)		0xffff820a)
#घोषणा f030_linewidth ((u_लघु*)      0xffff820e)
#घोषणा f030_hscroll ((u_अक्षर*)		0xffff8265)

#घोषणा VIDEL_BAS (0xffff8260)
काष्ठा VIDEL अणु
	u_लघु st_shअगरt;
	u_लघु pad1;
	u_अक्षर  xoffset_s;
	u_अक्षर  xoffset;
	u_लघु f_shअगरt;
	u_अक्षर  pad2[0x1a];
	u_लघु hht;
	u_लघु hbb;
	u_लघु hbe;
	u_लघु hdb;
	u_लघु hde;
	u_लघु hss;
	u_अक्षर  pad3[0x14];
	u_लघु vft;
	u_लघु vbb;
	u_लघु vbe;
	u_लघु vdb;
	u_लघु vde;
	u_लघु vss;
	u_अक्षर  pad4[0x12];
	u_लघु control;
	u_लघु mode;
पूर्ण;
#घोषणा	videl	((*(अस्थिर काष्ठा VIDEL *)VIDEL_BAS))

/*
** DMA/WD1772 Disk Controller
 */

#घोषणा FWD_BAS (0xffff8604)
काष्ठा DMA_WD
 अणु
  u_लघु fdc_acces_seccount;
  u_लघु dma_mode_status;
  u_अक्षर dma_vhi;	/* Some extended ST-DMAs can handle 32 bit addresses */
  u_अक्षर dma_hi;
  u_अक्षर अक्षर_dummy2;
  u_अक्षर dma_md;
  u_अक्षर अक्षर_dummy3;
  u_अक्षर dma_lo;
  u_लघु fdc_speed;
 पूर्ण;
# define dma_wd ((*(अस्थिर काष्ठा DMA_WD *)FWD_BAS))
/* alias */
#घोषणा	st_dma dma_wd
/* The two highest bytes of an extended DMA as a लघु; this is a must
 * क्रम the Medusa.
 */
#घोषणा st_dma_ext_dmahi (*((अस्थिर अचिन्हित लघु *)0xffff8608))

/*
** YM2149 Sound Chip
** access in bytes
 */

#घोषणा YM_BAS (0xffff8800)
काष्ठा SOUND_YM
 अणु
  u_अक्षर rd_data_reg_sel;
  u_अक्षर अक्षर_dummy1;
  u_अक्षर wd_data;
 पूर्ण;
#घोषणा sound_ym ((*(अस्थिर काष्ठा SOUND_YM *)YM_BAS))

/* TT SCSI DMA */

#घोषणा	TT_SCSI_DMA_BAS	(0xffff8700)
काष्ठा TT_DMA अणु
	u_अक्षर	अक्षर_dummy0;
	u_अक्षर	dma_addr_hi;
	u_अक्षर	अक्षर_dummy1;
	u_अक्षर	dma_addr_hmd;
	u_अक्षर	अक्षर_dummy2;
	u_अक्षर	dma_addr_lmd;
	u_अक्षर	अक्षर_dummy3;
	u_अक्षर	dma_addr_lo;
	u_अक्षर	अक्षर_dummy4;
	u_अक्षर	dma_cnt_hi;
	u_अक्षर	अक्षर_dummy5;
	u_अक्षर	dma_cnt_hmd;
	u_अक्षर	अक्षर_dummy6;
	u_अक्षर	dma_cnt_lmd;
	u_अक्षर	अक्षर_dummy7;
	u_अक्षर	dma_cnt_lo;
	u_दीर्घ	dma_restdata;
	u_लघु	dma_ctrl;
पूर्ण;
#घोषणा	tt_scsi_dma	((*(अस्थिर काष्ठा TT_DMA *)TT_SCSI_DMA_BAS))

/* TT SCSI Controller 5380 */

#घोषणा	TT_5380_BAS	(0xffff8781)
काष्ठा TT_5380 अणु
	u_अक्षर	scsi_data;
	u_अक्षर	अक्षर_dummy1;
	u_अक्षर	scsi_icr;
	u_अक्षर	अक्षर_dummy2;
	u_अक्षर	scsi_mode;
	u_अक्षर	अक्षर_dummy3;
	u_अक्षर	scsi_tcr;
	u_अक्षर	अक्षर_dummy4;
	u_अक्षर	scsi_idstat;
	u_अक्षर	अक्षर_dummy5;
	u_अक्षर	scsi_dmastat;
	u_अक्षर	अक्षर_dummy6;
	u_अक्षर	scsi_targrcv;
	u_अक्षर	अक्षर_dummy7;
	u_अक्षर	scsi_inircv;
पूर्ण;
#घोषणा	tt_scsi			((*(अस्थिर काष्ठा TT_5380 *)TT_5380_BAS))
#घोषणा	tt_scsi_regp	((अस्थिर अक्षर *)TT_5380_BAS)


/*
** Falcon DMA Sound Subप्रणाली
 */

#घोषणा MATRIX_BASE (0xffff8930)
काष्ठा MATRIX
अणु
  u_लघु source;
  u_लघु destination;
  u_अक्षर बाह्यal_frequency_भागider;
  u_अक्षर पूर्णांकernal_frequency_भागider;
पूर्ण;
#घोषणा falcon_matrix (*(अस्थिर काष्ठा MATRIX *)MATRIX_BASE)

#घोषणा CODEC_BASE (0xffff8936)
काष्ठा CODEC
अणु
  u_अक्षर tracks;
  u_अक्षर input_source;
#घोषणा CODEC_SOURCE_ADC        1
#घोषणा CODEC_SOURCE_MATRIX     2
  u_अक्षर adc_source;
#घोषणा ADC_SOURCE_RIGHT_PSG    1
#घोषणा ADC_SOURCE_LEFT_PSG     2
  u_अक्षर gain;
#घोषणा CODEC_GAIN_RIGHT        0x0f
#घोषणा CODEC_GAIN_LEFT         0xf0
  u_अक्षर attenuation;
#घोषणा CODEC_ATTENUATION_RIGHT 0x0f
#घोषणा CODEC_ATTENUATION_LEFT  0xf0
  u_अक्षर unused1;
  u_अक्षर status;
#घोषणा CODEC_OVERFLOW_RIGHT    1
#घोषणा CODEC_OVERFLOW_LEFT     2
  u_अक्षर unused2, unused3, unused4, unused5;
  u_अक्षर gpio_directions;
#घोषणा CODEC_GPIO_IN           0
#घोषणा CODEC_GPIO_OUT          1
  u_अक्षर unused6;
  u_अक्षर gpio_data;
पूर्ण;
#घोषणा falcon_codec (*(अस्थिर काष्ठा CODEC *)CODEC_BASE)

/*
** Falcon Blitter
*/

#घोषणा BLT_BAS (0xffff8a00)

काष्ठा BLITTER
 अणु
  u_लघु halftone[16];
  u_लघु src_x_inc;
  u_लघु src_y_inc;
  u_दीर्घ src_address;
  u_लघु endmask1;
  u_लघु endmask2;
  u_लघु endmask3;
  u_लघु dst_x_inc;
  u_लघु dst_y_inc;
  u_दीर्घ dst_address;
  u_लघु wd_per_line;
  u_लघु ln_per_bb;
  u_लघु hlf_op_reg;
  u_लघु log_op_reg;
  u_लघु lin_nm_reg;
  u_लघु skew_reg;
 पूर्ण;
# define blitter ((*(अस्थिर काष्ठा BLITTER *)BLT_BAS))


/*
** SCC Z8530
 */

#घोषणा SCC_BAS (0xffff8c81)
काष्ठा SCC
 अणु
  u_अक्षर cha_a_ctrl;
  u_अक्षर अक्षर_dummy1;
  u_अक्षर cha_a_data;
  u_अक्षर अक्षर_dummy2;
  u_अक्षर cha_b_ctrl;
  u_अक्षर अक्षर_dummy3;
  u_अक्षर cha_b_data;
 पूर्ण;
# define atari_scc ((*(अस्थिर काष्ठा SCC*)SCC_BAS))

/* The ESCC (Z85230) in an Atari ST. The channels are reversed! */
# define st_escc ((*(अस्थिर काष्ठा SCC*)0xfffffa31))
# define st_escc_dsr ((*(अस्थिर अक्षर *)0xfffffa39))

/* TT SCC DMA Controller (same chip as SCSI DMA) */

#घोषणा	TT_SCC_DMA_BAS	(0xffff8c00)
#घोषणा	tt_scc_dma	((*(अस्थिर काष्ठा TT_DMA *)TT_SCC_DMA_BAS))

/*
** VIDEL Palette Register
 */

#घोषणा FPL_BAS (0xffff9800)
काष्ठा VIDEL_PALETTE
 अणु
  u_दीर्घ reg[256];
 पूर्ण;
# define videl_palette ((*(अस्थिर काष्ठा VIDEL_PALETTE*)FPL_BAS))


/*
** Falcon DSP Host Interface
 */

#घोषणा DSP56K_HOST_INTERFACE_BASE (0xffffa200)
काष्ठा DSP56K_HOST_INTERFACE अणु
  u_अक्षर icr;
#घोषणा DSP56K_ICR_RREQ	0x01
#घोषणा DSP56K_ICR_TREQ	0x02
#घोषणा DSP56K_ICR_HF0	0x08
#घोषणा DSP56K_ICR_HF1	0x10
#घोषणा DSP56K_ICR_HM0	0x20
#घोषणा DSP56K_ICR_HM1	0x40
#घोषणा DSP56K_ICR_INIT	0x80

  u_अक्षर cvr;
#घोषणा DSP56K_CVR_HV_MASK 0x1f
#घोषणा DSP56K_CVR_HC	0x80

  u_अक्षर isr;
#घोषणा DSP56K_ISR_RXDF	0x01
#घोषणा DSP56K_ISR_TXDE	0x02
#घोषणा DSP56K_ISR_TRDY	0x04
#घोषणा DSP56K_ISR_HF2	0x08
#घोषणा DSP56K_ISR_HF3	0x10
#घोषणा DSP56K_ISR_DMA	0x40
#घोषणा DSP56K_ISR_HREQ	0x80

  u_अक्षर ivr;

  जोड़ अणु
    u_अक्षर b[4];
    u_लघु w[2];
    u_दीर्घ l;
  पूर्ण data;
पूर्ण;
#घोषणा dsp56k_host_पूर्णांकerface ((*(अस्थिर काष्ठा DSP56K_HOST_INTERFACE *)DSP56K_HOST_INTERFACE_BASE))

/*
** MFP 68901
 */

#घोषणा MFP_BAS (0xfffffa01)
काष्ठा MFP
 अणु
  u_अक्षर par_dt_reg;
  u_अक्षर अक्षर_dummy1;
  u_अक्षर active_edge;
  u_अक्षर अक्षर_dummy2;
  u_अक्षर data_dir;
  u_अक्षर अक्षर_dummy3;
  u_अक्षर पूर्णांक_en_a;
  u_अक्षर अक्षर_dummy4;
  u_अक्षर पूर्णांक_en_b;
  u_अक्षर अक्षर_dummy5;
  u_अक्षर पूर्णांक_pn_a;
  u_अक्षर अक्षर_dummy6;
  u_अक्षर पूर्णांक_pn_b;
  u_अक्षर अक्षर_dummy7;
  u_अक्षर पूर्णांक_sv_a;
  u_अक्षर अक्षर_dummy8;
  u_अक्षर पूर्णांक_sv_b;
  u_अक्षर अक्षर_dummy9;
  u_अक्षर पूर्णांक_mk_a;
  u_अक्षर अक्षर_dummy10;
  u_अक्षर पूर्णांक_mk_b;
  u_अक्षर अक्षर_dummy11;
  u_अक्षर vec_adr;
  u_अक्षर अक्षर_dummy12;
  u_अक्षर tim_ct_a;
  u_अक्षर अक्षर_dummy13;
  u_अक्षर tim_ct_b;
  u_अक्षर अक्षर_dummy14;
  u_अक्षर tim_ct_cd;
  u_अक्षर अक्षर_dummy15;
  u_अक्षर tim_dt_a;
  u_अक्षर अक्षर_dummy16;
  u_अक्षर tim_dt_b;
  u_अक्षर अक्षर_dummy17;
  u_अक्षर tim_dt_c;
  u_अक्षर अक्षर_dummy18;
  u_अक्षर tim_dt_d;
  u_अक्षर अक्षर_dummy19;
  u_अक्षर sync_अक्षर;
  u_अक्षर अक्षर_dummy20;
  u_अक्षर usart_ctr;
  u_अक्षर अक्षर_dummy21;
  u_अक्षर rcv_stat;
  u_अक्षर अक्षर_dummy22;
  u_अक्षर trn_stat;
  u_अक्षर अक्षर_dummy23;
  u_अक्षर usart_dta;
 पूर्ण;
# define st_mfp ((*(अस्थिर काष्ठा MFP*)MFP_BAS))

/* TT's second MFP */

#घोषणा	TT_MFP_BAS	(0xfffffa81)
# define tt_mfp ((*(अस्थिर काष्ठा MFP*)TT_MFP_BAS))


/* TT System Control Unit */

#घोषणा	TT_SCU_BAS	(0xffff8e01)
काष्ठा TT_SCU अणु
	u_अक्षर	sys_mask;
	u_अक्षर	अक्षर_dummy1;
	u_अक्षर	sys_stat;
	u_अक्षर	अक्षर_dummy2;
	u_अक्षर	softपूर्णांक;
	u_अक्षर	अक्षर_dummy3;
	u_अक्षर	vmeपूर्णांक;
	u_अक्षर	अक्षर_dummy4;
	u_अक्षर	gp_reg1;
	u_अक्षर	अक्षर_dummy5;
	u_अक्षर	gp_reg2;
	u_अक्षर	अक्षर_dummy6;
	u_अक्षर	vme_mask;
	u_अक्षर	अक्षर_dummy7;
	u_अक्षर	vme_stat;
पूर्ण;
#घोषणा	tt_scu	((*(अस्थिर काष्ठा TT_SCU *)TT_SCU_BAS))

/* TT real समय घड़ी */

#घोषणा	TT_RTC_BAS	(0xffff8961)
काष्ठा TT_RTC अणु
	u_अक्षर	regsel;
	u_अक्षर	dummy;
	u_अक्षर	data;
पूर्ण;
#घोषणा	tt_rtc	((*(अस्थिर काष्ठा TT_RTC *)TT_RTC_BAS))


/*
** ACIA 6850
 */
/* स्थिरants क्रम the ACIA रेजिस्टरs */

/* baudrate selection and reset (Baudrate = घड़ी/factor) */
#घोषणा ACIA_DIV1  0
#घोषणा ACIA_DIV16 1
#घोषणा ACIA_DIV64 2
#घोषणा ACIA_RESET 3

/* अक्षरacter क्रमmat */
#घोषणा ACIA_D7E2S (0<<2)	/* 7 data, even parity, 2 stop */
#घोषणा ACIA_D7O2S (1<<2)	/* 7 data, odd parity, 2 stop */
#घोषणा ACIA_D7E1S (2<<2)	/* 7 data, even parity, 1 stop */
#घोषणा ACIA_D7O1S (3<<2)	/* 7 data, odd parity, 1 stop */
#घोषणा ACIA_D8N2S (4<<2)	/* 8 data, no parity, 2 stop */
#घोषणा ACIA_D8N1S (5<<2)	/* 8 data, no parity, 1 stop */
#घोषणा ACIA_D8E1S (6<<2)	/* 8 data, even parity, 1 stop */
#घोषणा ACIA_D8O1S (7<<2)	/* 8 data, odd parity, 1 stop */

/* transmit control */
#घोषणा ACIA_RLTID (0<<5)	/* RTS low, TxINT disabled */
#घोषणा ACIA_RLTIE (1<<5)	/* RTS low, TxINT enabled */
#घोषणा ACIA_RHTID (2<<5)	/* RTS high, TxINT disabled */
#घोषणा ACIA_RLTIDSB (3<<5)	/* RTS low, TxINT disabled, send अवरोध */

/* receive control */
#घोषणा ACIA_RID (0<<7)		/* RxINT disabled */
#घोषणा ACIA_RIE (1<<7)		/* RxINT enabled */

/* status fields of the ACIA */
#घोषणा ACIA_RDRF 1		/* Receive Data Register Full */
#घोषणा ACIA_TDRE (1<<1)	/* Transmit Data Register Empty */
#घोषणा ACIA_DCD  (1<<2)	/* Data Carrier Detect */
#घोषणा ACIA_CTS  (1<<3)	/* Clear To Send */
#घोषणा ACIA_FE   (1<<4)	/* Framing Error */
#घोषणा ACIA_OVRN (1<<5)	/* Receiver Overrun */
#घोषणा ACIA_PE   (1<<6)	/* Parity Error */
#घोषणा ACIA_IRQ  (1<<7)	/* Interrupt Request */

#घोषणा ACIA_BAS (0xfffffc00)
काष्ठा ACIA
 अणु
  u_अक्षर key_ctrl;
  u_अक्षर अक्षर_dummy1;
  u_अक्षर key_data;
  u_अक्षर अक्षर_dummy2;
  u_अक्षर mid_ctrl;
  u_अक्षर अक्षर_dummy3;
  u_अक्षर mid_data;
 पूर्ण;
# define acia ((*(अस्थिर काष्ठा ACIA*)ACIA_BAS))

#घोषणा	TT_DMASND_BAS (0xffff8900)
काष्ठा TT_DMASND अणु
	u_अक्षर	पूर्णांक_ctrl;	/* Falcon: Interrupt control */
	u_अक्षर	ctrl;
	u_अक्षर	pad2;
	u_अक्षर	bas_hi;
	u_अक्षर	pad3;
	u_अक्षर	bas_mid;
	u_अक्षर	pad4;
	u_अक्षर	bas_low;
	u_अक्षर	pad5;
	u_अक्षर	addr_hi;
	u_अक्षर	pad6;
	u_अक्षर	addr_mid;
	u_अक्षर	pad7;
	u_अक्षर	addr_low;
	u_अक्षर	pad8;
	u_अक्षर	end_hi;
	u_अक्षर	pad9;
	u_अक्षर	end_mid;
	u_अक्षर	pad10;
	u_अक्षर	end_low;
	u_अक्षर	pad11[12];
	u_अक्षर	track_select;	/* Falcon */
	u_अक्षर	mode;
	u_अक्षर	pad12[14];
	/* Falcon only: */
	u_लघु	cbar_src;
	u_लघु cbar_dst;
	u_अक्षर	ext_भाग;
	u_अक्षर	पूर्णांक_भाग;
	u_अक्षर	rec_track_select;
	u_अक्षर	dac_src;
	u_अक्षर	adc_src;
	u_अक्षर	input_gain;
	u_लघु	output_atten;
पूर्ण;
# define tt_dmasnd ((*(अस्थिर काष्ठा TT_DMASND *)TT_DMASND_BAS))

#घोषणा DMASND_MFP_INT_REPLAY     0x01
#घोषणा DMASND_MFP_INT_RECORD     0x02
#घोषणा DMASND_TIMERA_INT_REPLAY  0x04
#घोषणा DMASND_TIMERA_INT_RECORD  0x08

#घोषणा	DMASND_CTRL_OFF		  0x00
#घोषणा	DMASND_CTRL_ON		  0x01
#घोषणा	DMASND_CTRL_REPEAT	  0x02
#घोषणा DMASND_CTRL_RECORD_ON     0x10
#घोषणा DMASND_CTRL_RECORD_OFF    0x00
#घोषणा DMASND_CTRL_RECORD_REPEAT 0x20
#घोषणा DMASND_CTRL_SELECT_REPLAY 0x00
#घोषणा DMASND_CTRL_SELECT_RECORD 0x80
#घोषणा	DMASND_MODE_MONO	  0x80
#घोषणा	DMASND_MODE_STEREO	  0x00
#घोषणा DMASND_MODE_8BIT	  0x00
#घोषणा DMASND_MODE_16BIT	  0x40	/* Falcon only */
#घोषणा	DMASND_MODE_6KHZ	  0x00	/* Falcon: mute */
#घोषणा	DMASND_MODE_12KHZ	  0x01
#घोषणा	DMASND_MODE_25KHZ	  0x02
#घोषणा	DMASND_MODE_50KHZ	  0x03


#घोषणा DMASNDSetBase(bufstart)						\
    करो अणु								\
	tt_dmasnd.bas_hi  = (अचिन्हित अक्षर)(((bufstart) & 0xff0000) >> 16); \
	tt_dmasnd.bas_mid = (अचिन्हित अक्षर)(((bufstart) & 0x00ff00) >> 8); \
	tt_dmasnd.bas_low = (अचिन्हित अक्षर) ((bufstart) & 0x0000ff); \
    पूर्ण जबतक( 0 )

#घोषणा DMASNDGetAdr() ((tt_dmasnd.addr_hi << 16) +	\
			(tt_dmasnd.addr_mid << 8) +	\
			(tt_dmasnd.addr_low))

#घोषणा DMASNDSetEnd(bufend)				\
    करो अणु						\
	tt_dmasnd.end_hi  = (अचिन्हित अक्षर)(((bufend) & 0xff0000) >> 16); \
	tt_dmasnd.end_mid = (अचिन्हित अक्षर)(((bufend) & 0x00ff00) >> 8); \
	tt_dmasnd.end_low = (अचिन्हित अक्षर) ((bufend) & 0x0000ff); \
    पूर्ण जबतक( 0 )


#घोषणा	TT_MICROWIRE_BAS	(0xffff8922)
काष्ठा TT_MICROWIRE अणु
	u_लघु	data;
	u_लघु	mask;
पूर्ण;
# define tt_microwire ((*(अस्थिर काष्ठा TT_MICROWIRE *)TT_MICROWIRE_BAS))

#घोषणा	MW_LM1992_ADDR		0x0400

#घोषणा	MW_LM1992_VOLUME(dB)	\
    (0x0c0 | ((dB) < -80 ? 0 : (dB) > 0 ? 40 : (((dB) + 80) / 2)))
#घोषणा	MW_LM1992_BALLEFT(dB)	\
    (0x140 | ((dB) < -40 ? 0 : (dB) > 0 ? 20 : (((dB) + 40) / 2)))
#घोषणा	MW_LM1992_BALRIGHT(dB)	\
    (0x100 | ((dB) < -40 ? 0 : (dB) > 0 ? 20 : (((dB) + 40) / 2)))
#घोषणा	MW_LM1992_TREBLE(dB)	\
    (0x080 | ((dB) < -12 ? 0 : (dB) > 12 ? 12 : (((dB) / 2) + 6)))
#घोषणा	MW_LM1992_BASS(dB)	\
    (0x040 | ((dB) < -12 ? 0 : (dB) > 12 ? 12 : (((dB) / 2) + 6)))

#घोषणा	MW_LM1992_PSG_LOW	0x000
#घोषणा	MW_LM1992_PSG_HIGH	0x001
#घोषणा	MW_LM1992_PSG_OFF	0x002

#घोषणा MSTE_RTC_BAS	(0xfffffc21)

काष्ठा MSTE_RTC अणु
	u_अक्षर sec_ones;
	u_अक्षर dummy1;
	u_अक्षर sec_tens;
	u_अक्षर dummy2;
	u_अक्षर min_ones;
	u_अक्षर dummy3;
	u_अक्षर min_tens;
	u_अक्षर dummy4;
	u_अक्षर hr_ones;
	u_अक्षर dummy5;
	u_अक्षर hr_tens;
	u_अक्षर dummy6;
	u_अक्षर weekday;
	u_अक्षर dummy7;
	u_अक्षर day_ones;
	u_अक्षर dummy8;
	u_अक्षर day_tens;
	u_अक्षर dummy9;
	u_अक्षर mon_ones;
	u_अक्षर dummy10;
	u_अक्षर mon_tens;
	u_अक्षर dummy11;
	u_अक्षर year_ones;
	u_अक्षर dummy12;
	u_अक्षर year_tens;
	u_अक्षर dummy13;
	u_अक्षर mode;
	u_अक्षर dummy14;
	u_अक्षर test;
	u_अक्षर dummy15;
	u_अक्षर reset;
पूर्ण;

#घोषणा mste_rtc ((*(अस्थिर काष्ठा MSTE_RTC *)MSTE_RTC_BAS))

/*
** EtherNAT add-on card क्रम Falcon - combined ethernet and USB adapter
*/

#घोषणा ATARI_ETHERNAT_PHYS_ADDR	0x80000000

#पूर्ण_अगर /* linux/atarihw.h */

