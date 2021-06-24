<शैली गुरु>
/*
** यंत्र-m68k/amigahw.h -- This header defines some macros and poपूर्णांकers क्रम
**                    the various Amiga custom hardware रेजिस्टरs.
**                    The naming conventions used here conक्रमm to those
**                    used in the Amiga Hardware Reference Manual, 3rd Edition
**
** Copyright 1992 by Greg Harp
**
** This file is subject to the terms and conditions of the GNU General Public
** License.  See the file COPYING in the मुख्य directory of this archive
** क्रम more details.
**
** Created: 9/24/92 by Greg Harp
*/

#अगर_अघोषित _M68K_AMIGAHW_H
#घोषणा _M68K_AMIGAHW_H

#समावेश <linux/ioport.h>

#समावेश <यंत्र/bootinfo-amiga.h>


    /*
     *  Chipsets
     */

बाह्य अचिन्हित दीर्घ amiga_chipset;


    /*
     *  Miscellaneous
     */

बाह्य अचिन्हित दीर्घ amiga_eघड़ी;	/* 700 kHz E Peripheral Clock */
बाह्य अचिन्हित दीर्घ amiga_colorघड़ी;	/* 3.5 MHz Color Clock */
बाह्य अचिन्हित दीर्घ amiga_chip_size;	/* Chip RAM Size (bytes) */
बाह्य अचिन्हित अक्षर amiga_vblank;	/* VBLANK Frequency */


#घोषणा AMIGAHW_DECLARE(name)	अचिन्हित name : 1
#घोषणा AMIGAHW_SET(name)	(amiga_hw_present.name = 1)
#घोषणा AMIGAHW_PRESENT(name)	(amiga_hw_present.name)

काष्ठा amiga_hw_present अणु
    /* video hardware */
    AMIGAHW_DECLARE(AMI_VIDEO);		/* Amiga Video */
    AMIGAHW_DECLARE(AMI_BLITTER);	/* Amiga Blitter */
    AMIGAHW_DECLARE(AMBER_FF);		/* Amber Flicker Fixer */
    /* sound hardware */
    AMIGAHW_DECLARE(AMI_AUDIO);		/* Amiga Audio */
    /* disk storage पूर्णांकerfaces */
    AMIGAHW_DECLARE(AMI_FLOPPY);	/* Amiga Floppy */
    AMIGAHW_DECLARE(A3000_SCSI);	/* SCSI (wd33c93, A3000 alike) */
    AMIGAHW_DECLARE(A4000_SCSI);	/* SCSI (ncr53c710, A4000T alike) */
    AMIGAHW_DECLARE(A1200_IDE);		/* IDE (A1200 alike) */
    AMIGAHW_DECLARE(A4000_IDE);		/* IDE (A4000 alike) */
    AMIGAHW_DECLARE(CD_ROM);		/* CD ROM drive */
    /* other I/O hardware */
    AMIGAHW_DECLARE(AMI_KEYBOARD);	/* Amiga Keyboard */
    AMIGAHW_DECLARE(AMI_MOUSE);		/* Amiga Mouse */
    AMIGAHW_DECLARE(AMI_SERIAL);	/* Amiga Serial */
    AMIGAHW_DECLARE(AMI_PARALLEL);	/* Amiga Parallel */
    /* real समय घड़ीs */
    AMIGAHW_DECLARE(A2000_CLK);		/* Hardware Clock (A2000 alike) */
    AMIGAHW_DECLARE(A3000_CLK);		/* Hardware Clock (A3000 alike) */
    /* supporting hardware */
    AMIGAHW_DECLARE(CHIP_RAM);		/* Chip RAM */
    AMIGAHW_DECLARE(PAULA);		/* Paula (8364) */
    AMIGAHW_DECLARE(DENISE);		/* Denise (8362) */
    AMIGAHW_DECLARE(DENISE_HR);		/* Denise (8373) */
    AMIGAHW_DECLARE(LISA);		/* Lisa (8375) */
    AMIGAHW_DECLARE(AGNUS_PAL);		/* Normal/Fat PAL Agnus (8367/8371) */
    AMIGAHW_DECLARE(AGNUS_NTSC);	/* Normal/Fat NTSC Agnus (8361/8370) */
    AMIGAHW_DECLARE(AGNUS_HR_PAL);	/* Fat Hires PAL Agnus (8372) */
    AMIGAHW_DECLARE(AGNUS_HR_NTSC);	/* Fat Hires NTSC Agnus (8372) */
    AMIGAHW_DECLARE(ALICE_PAL);		/* PAL Alice (8374) */
    AMIGAHW_DECLARE(ALICE_NTSC);	/* NTSC Alice (8374) */
    AMIGAHW_DECLARE(MAGIC_REKICK);	/* A3000 Magic Hard Rekick */
    AMIGAHW_DECLARE(PCMCIA);		/* PCMCIA Slot */
    AMIGAHW_DECLARE(ZORRO);		/* Zorro AutoConfig */
    AMIGAHW_DECLARE(ZORRO3);		/* Zorro III */
पूर्ण;

बाह्य काष्ठा amiga_hw_present amiga_hw_present;

काष्ठा CUSTOM अणु
    अचिन्हित लघु bltddat;
    अचिन्हित लघु dmaconr;
    अचिन्हित लघु vposr;
    अचिन्हित लघु vhposr;
    अचिन्हित लघु dskdatr;
    अचिन्हित लघु joy0dat;
    अचिन्हित लघु joy1dat;
    अचिन्हित लघु clxdat;
    अचिन्हित लघु adkconr;
    अचिन्हित लघु pot0dat;
    अचिन्हित लघु pot1dat;
    अचिन्हित लघु potgor;
    अचिन्हित लघु serdatr;
    अचिन्हित लघु dskbytr;
    अचिन्हित लघु पूर्णांकenar;
    अचिन्हित लघु पूर्णांकreqr;
    अचिन्हित अक्षर  *dskptr;
    अचिन्हित लघु dsklen;
    अचिन्हित लघु dskdat;
    अचिन्हित लघु refptr;
    अचिन्हित लघु vposw;
    अचिन्हित लघु vhposw;
    अचिन्हित लघु copcon;
    अचिन्हित लघु serdat;
    अचिन्हित लघु serper;
    अचिन्हित लघु potgo;
    अचिन्हित लघु joytest;
    अचिन्हित लघु strequ;
    अचिन्हित लघु strvbl;
    अचिन्हित लघु strhor;
    अचिन्हित लघु strदीर्घ;
    अचिन्हित लघु bltcon0;
    अचिन्हित लघु bltcon1;
    अचिन्हित लघु bltafwm;
    अचिन्हित लघु bltalwm;
    अचिन्हित अक्षर  *bltcpt;
    अचिन्हित अक्षर  *bltbpt;
    अचिन्हित अक्षर  *bltapt;
    अचिन्हित अक्षर  *bltdpt;
    अचिन्हित लघु bltsize;
    अचिन्हित अक्षर  pad2d;
    अचिन्हित अक्षर  bltcon0l;
    अचिन्हित लघु bltsizv;
    अचिन्हित लघु bltsizh;
    अचिन्हित लघु bltcmod;
    अचिन्हित लघु bltbmod;
    अचिन्हित लघु bltamod;
    अचिन्हित लघु bltdmod;
    अचिन्हित लघु spare2[4];
    अचिन्हित लघु bltcdat;
    अचिन्हित लघु bltbdat;
    अचिन्हित लघु bltadat;
    अचिन्हित लघु spare3[3];
    अचिन्हित लघु deniseid;
    अचिन्हित लघु dsksync;
    अचिन्हित लघु *cop1lc;
    अचिन्हित लघु *cop2lc;
    अचिन्हित लघु copjmp1;
    अचिन्हित लघु copjmp2;
    अचिन्हित लघु copins;
    अचिन्हित लघु diwstrt;
    अचिन्हित लघु diwstop;
    अचिन्हित लघु ddfstrt;
    अचिन्हित लघु ddfstop;
    अचिन्हित लघु dmacon;
    अचिन्हित लघु clxcon;
    अचिन्हित लघु पूर्णांकena;
    अचिन्हित लघु पूर्णांकreq;
    अचिन्हित लघु adkcon;
    काष्ठा अणु
	अचिन्हित लघु	*audlc;
	अचिन्हित लघु audlen;
	अचिन्हित लघु audper;
	अचिन्हित लघु audvol;
	अचिन्हित लघु auddat;
	अचिन्हित लघु audspare[2];
    पूर्ण aud[4];
    अचिन्हित अक्षर  *bplpt[8];
    अचिन्हित लघु bplcon0;
    अचिन्हित लघु bplcon1;
    अचिन्हित लघु bplcon2;
    अचिन्हित लघु bplcon3;
    अचिन्हित लघु bpl1mod;
    अचिन्हित लघु bpl2mod;
    अचिन्हित लघु bplcon4;
    अचिन्हित लघु clxcon2;
    अचिन्हित लघु bpldat[8];
    अचिन्हित अक्षर  *sprpt[8];
    काष्ठा अणु
	अचिन्हित लघु pos;
	अचिन्हित लघु ctl;
	अचिन्हित लघु dataa;
	अचिन्हित लघु datab;
    पूर्ण spr[8];
    अचिन्हित लघु color[32];
    अचिन्हित लघु htotal;
    अचिन्हित लघु hsstop;
    अचिन्हित लघु hbstrt;
    अचिन्हित लघु hbstop;
    अचिन्हित लघु vtotal;
    अचिन्हित लघु vsstop;
    अचिन्हित लघु vbstrt;
    अचिन्हित लघु vbstop;
    अचिन्हित लघु sprhstrt;
    अचिन्हित लघु sprhstop;
    अचिन्हित लघु bplhstrt;
    अचिन्हित लघु bplhstop;
    अचिन्हित लघु hhposw;
    अचिन्हित लघु hhposr;
    अचिन्हित लघु beamcon0;
    अचिन्हित लघु hsstrt;
    अचिन्हित लघु vsstrt;
    अचिन्हित लघु hcenter;
    अचिन्हित लघु diwhigh;
    अचिन्हित लघु spare4[11];
    अचिन्हित लघु भ_शेषe;
पूर्ण;

/*
 * DMA रेजिस्टर bits
 */
#घोषणा DMAF_SETCLR		(0x8000)
#घोषणा DMAF_AUD0		(0x0001)
#घोषणा DMAF_AUD1		(0x0002)
#घोषणा DMAF_AUD2		(0x0004)
#घोषणा DMAF_AUD3		(0x0008)
#घोषणा DMAF_DISK		(0x0010)
#घोषणा DMAF_SPRITE		(0x0020)
#घोषणा DMAF_BLITTER		(0x0040)
#घोषणा DMAF_COPPER		(0x0080)
#घोषणा DMAF_RASTER		(0x0100)
#घोषणा DMAF_MASTER		(0x0200)
#घोषणा DMAF_BLITHOG		(0x0400)
#घोषणा DMAF_BLTNZERO		(0x2000)
#घोषणा DMAF_BLTDONE		(0x4000)
#घोषणा DMAF_ALL		(0x01FF)

काष्ठा CIA अणु
    अचिन्हित अक्षर pra;		अक्षर pad0[0xff];
    अचिन्हित अक्षर prb;		अक्षर pad1[0xff];
    अचिन्हित अक्षर ddra;		अक्षर pad2[0xff];
    अचिन्हित अक्षर ddrb;		अक्षर pad3[0xff];
    अचिन्हित अक्षर talo;		अक्षर pad4[0xff];
    अचिन्हित अक्षर tahi;		अक्षर pad5[0xff];
    अचिन्हित अक्षर tblo;		अक्षर pad6[0xff];
    अचिन्हित अक्षर tbhi;		अक्षर pad7[0xff];
    अचिन्हित अक्षर todlo;	अक्षर pad8[0xff];
    अचिन्हित अक्षर todmid;	अक्षर pad9[0xff];
    अचिन्हित अक्षर todhi;	अक्षर pada[0x1ff];
    अचिन्हित अक्षर sdr;		अक्षर padb[0xff];
    अचिन्हित अक्षर icr;		अक्षर padc[0xff];
    अचिन्हित अक्षर cra;		अक्षर padd[0xff];
    अचिन्हित अक्षर crb;		अक्षर pade[0xff];
पूर्ण;

#घोषणा zTwoBase (0x80000000)
#घोषणा ZTWO_PADDR(x) (((अचिन्हित दीर्घ)(x))-zTwoBase)
#घोषणा ZTWO_VADDR(x) ((व्योम __iomem *)(((अचिन्हित दीर्घ)(x))+zTwoBase))

#घोषणा CUSTOM_PHYSADDR     (0xdff000)
#घोषणा amiga_custom ((*(अस्थिर काष्ठा CUSTOM *)(zTwoBase+CUSTOM_PHYSADDR)))

#घोषणा CIAA_PHYSADDR	  (0xbfe001)
#घोषणा CIAB_PHYSADDR	  (0xbfd000)
#घोषणा ciaa   ((*(अस्थिर काष्ठा CIA *)(zTwoBase + CIAA_PHYSADDR)))
#घोषणा ciab   ((*(अस्थिर काष्ठा CIA *)(zTwoBase + CIAB_PHYSADDR)))

#घोषणा CHIP_PHYSADDR	    (0x000000)

व्योम amiga_chip_init (व्योम);
व्योम *amiga_chip_alloc(अचिन्हित दीर्घ size, स्थिर अक्षर *name);
व्योम *amiga_chip_alloc_res(अचिन्हित दीर्घ size, काष्ठा resource *res);
व्योम amiga_chip_मुक्त(व्योम *ptr);
अचिन्हित दीर्घ amiga_chip_avail( व्योम ); /*MILAN*/
बाह्य अस्थिर अचिन्हित लघु amiga_audio_min_period;

अटल अंतरभूत व्योम amअगरb_video_off(व्योम)
अणु
	अगर (amiga_chipset == CS_ECS || amiga_chipset == CS_AGA) अणु
		/* program Denise/Lisa क्रम a higher maximum play rate */
		amiga_custom.htotal = 113;        /* 31 kHz */
		amiga_custom.vtotal = 223;        /* 70 Hz */
		amiga_custom.beamcon0 = 0x4390;   /* HARDDIS, VARअणुBEAM,VSY,HSY,CSYपूर्णEN */
		/* suspend the monitor */
		amiga_custom.hsstrt = amiga_custom.hsstop = 116;
		amiga_custom.vsstrt = amiga_custom.vsstop = 226;
		amiga_audio_min_period = 57;
	पूर्ण
पूर्ण

काष्ठा tod3000 अणु
  अचिन्हित पूर्णांक  :28, second2:4;	/* lower digit */
  अचिन्हित पूर्णांक  :28, second1:4;	/* upper digit */
  अचिन्हित पूर्णांक  :28, minute2:4;	/* lower digit */
  अचिन्हित पूर्णांक  :28, minute1:4;	/* upper digit */
  अचिन्हित पूर्णांक  :28, hour2:4;	/* lower digit */
  अचिन्हित पूर्णांक  :28, hour1:4;	/* upper digit */
  अचिन्हित पूर्णांक  :28, weekday:4;
  अचिन्हित पूर्णांक  :28, day2:4;	/* lower digit */
  अचिन्हित पूर्णांक  :28, day1:4;	/* upper digit */
  अचिन्हित पूर्णांक  :28, month2:4;	/* lower digit */
  अचिन्हित पूर्णांक  :28, month1:4;	/* upper digit */
  अचिन्हित पूर्णांक  :28, year2:4;	/* lower digit */
  अचिन्हित पूर्णांक  :28, year1:4;	/* upper digit */
  अचिन्हित पूर्णांक  :28, cntrl1:4;	/* control-byte 1 */
  अचिन्हित पूर्णांक  :28, cntrl2:4;	/* control-byte 2 */
  अचिन्हित पूर्णांक  :28, cntrl3:4;	/* control-byte 3 */
पूर्ण;
#घोषणा TOD3000_CNTRL1_HOLD	0
#घोषणा TOD3000_CNTRL1_FREE	9
#घोषणा tod_3000 ((*(अस्थिर काष्ठा tod3000 *)(zTwoBase+0xDC0000)))

काष्ठा tod2000 अणु
  अचिन्हित पूर्णांक  :28, second2:4;	/* lower digit */
  अचिन्हित पूर्णांक  :28, second1:4;	/* upper digit */
  अचिन्हित पूर्णांक  :28, minute2:4;	/* lower digit */
  अचिन्हित पूर्णांक  :28, minute1:4;	/* upper digit */
  अचिन्हित पूर्णांक  :28, hour2:4;	/* lower digit */
  अचिन्हित पूर्णांक  :28, hour1:4;	/* upper digit */
  अचिन्हित पूर्णांक  :28, day2:4;	/* lower digit */
  अचिन्हित पूर्णांक  :28, day1:4;	/* upper digit */
  अचिन्हित पूर्णांक  :28, month2:4;	/* lower digit */
  अचिन्हित पूर्णांक  :28, month1:4;	/* upper digit */
  अचिन्हित पूर्णांक  :28, year2:4;	/* lower digit */
  अचिन्हित पूर्णांक  :28, year1:4;	/* upper digit */
  अचिन्हित पूर्णांक  :28, weekday:4;
  अचिन्हित पूर्णांक  :28, cntrl1:4;	/* control-byte 1 */
  अचिन्हित पूर्णांक  :28, cntrl2:4;	/* control-byte 2 */
  अचिन्हित पूर्णांक  :28, cntrl3:4;	/* control-byte 3 */
पूर्ण;

#घोषणा TOD2000_CNTRL1_HOLD	(1<<0)
#घोषणा TOD2000_CNTRL1_BUSY	(1<<1)
#घोषणा TOD2000_CNTRL3_24HMODE	(1<<2)
#घोषणा TOD2000_HOUR1_PM	(1<<2)
#घोषणा tod_2000 ((*(अस्थिर काष्ठा tod2000 *)(zTwoBase+0xDC0000)))

#पूर्ण_अगर /* _M68K_AMIGAHW_H */
