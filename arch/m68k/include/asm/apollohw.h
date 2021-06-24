<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* apollohw.h : some काष्ठाures to access apollo HW */

#अगर_अघोषित _ASMm68k_APOLLOHW_H_
#घोषणा _ASMm68k_APOLLOHW_H_

#समावेश <linux/types.h>

#समावेश <यंत्र/bootinfo-apollo.h>


बाह्य u_दीर्घ apollo_model;


/*
   see scn2681 data sheet क्रम more info.
   member names are पढ़ो_ग_लिखो.
*/

#घोषणा DECLARE_2681_FIELD(x) अचिन्हित अक्षर x; अचिन्हित अक्षर dummy##x

काष्ठा SCN2681 अणु

	DECLARE_2681_FIELD(mra);
	DECLARE_2681_FIELD(sra_csra);
	DECLARE_2681_FIELD(BRGtest_cra);
	DECLARE_2681_FIELD(rhra_thra);
	DECLARE_2681_FIELD(ipcr_acr);
	DECLARE_2681_FIELD(isr_imr);
	DECLARE_2681_FIELD(ctu_ctur);
	DECLARE_2681_FIELD(ctl_ctlr);
	DECLARE_2681_FIELD(mrb);
	DECLARE_2681_FIELD(srb_csrb);
	DECLARE_2681_FIELD(tst_crb);
	DECLARE_2681_FIELD(rhrb_thrb);
	DECLARE_2681_FIELD(reserved);
	DECLARE_2681_FIELD(ip_opcr);
	DECLARE_2681_FIELD(startCnt_setOutBit);
	DECLARE_2681_FIELD(stopCnt_resetOutBit);

पूर्ण;

काष्ठा mc146818 अणु
        अचिन्हित अक्षर second, alarm_second;
        अचिन्हित अक्षर minute, alarm_minute;
        अचिन्हित अक्षर hours, alarm_hours;
        अचिन्हित अक्षर day_of_week, day_of_month;
        अचिन्हित अक्षर month, year;
पूर्ण;


#घोषणा IO_BASE 0x80000000

बाह्य u_दीर्घ sio01_physaddr;
बाह्य u_दीर्घ sio23_physaddr;
बाह्य u_दीर्घ rtc_physaddr;
बाह्य u_दीर्घ pica_physaddr;
बाह्य u_दीर्घ picb_physaddr;
बाह्य u_दीर्घ cpuctrl_physaddr;
बाह्य u_दीर्घ समयr_physaddr;

#घोषणा SAU7_SIO01_PHYSADDR 0x10400
#घोषणा SAU7_SIO23_PHYSADDR 0x10500
#घोषणा SAU7_RTC_PHYSADDR 0x10900
#घोषणा SAU7_PICA 0x11000
#घोषणा SAU7_PICB 0x11100
#घोषणा SAU7_CPUCTRL 0x10100
#घोषणा SAU7_TIMER 0x010800

#घोषणा SAU8_SIO01_PHYSADDR 0x8400
#घोषणा SAU8_RTC_PHYSADDR 0x8900
#घोषणा SAU8_PICA 0x9400
#घोषणा SAU8_PICB 0x9500
#घोषणा SAU8_CPUCTRL 0x8100
#घोषणा SAU8_TIMER 0x8800

#घोषणा sio01 ((*(अस्थिर काष्ठा SCN2681 *)(IO_BASE + sio01_physaddr)))
#घोषणा sio23 ((*(अस्थिर काष्ठा SCN2681 *)(IO_BASE + sio23_physaddr)))
#घोषणा rtc (((अस्थिर काष्ठा mc146818 *)(IO_BASE + rtc_physaddr)))
#घोषणा cpuctrl (*(अस्थिर अचिन्हित पूर्णांक *)(IO_BASE + cpuctrl_physaddr))
#घोषणा pica (IO_BASE + pica_physaddr)
#घोषणा picb (IO_BASE + picb_physaddr)
#घोषणा apollo_समयr (IO_BASE + समयr_physaddr)
#घोषणा addr_xlat_map ((अचिन्हित लघु *)(IO_BASE + 0x17000))

#घोषणा isaIO2mem(x) (((((x) & 0x3f8)  << 7) | (((x) & 0xfc00) >> 6) | ((x) & 0x7)) + 0x40000 + IO_BASE)

#घोषणा IRQ_APOLLO	IRQ_USER

#पूर्ण_अगर
