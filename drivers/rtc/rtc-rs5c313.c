<शैली गुरु>
/*
 * Ricoh RS5C313 RTC device/driver
 *  Copyright (C) 2007 Nobuhiro Iwamatsu
 *
 *  2005-09-19 modअगरed by kogiidena
 *
 * Based on the old drivers/अक्षर/rs5c313_rtc.c  by:
 *  Copyright (C) 2000 Philipp Rumpf <prumpf@tux.org>
 *  Copyright (C) 1999 Tetsuya Okada & Niibe Yutaka
 *
 * Based on code written by Paul Gorपंचांगaker.
 *  Copyright (C) 1996 Paul Gorपंचांगaker
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Based on other minimal अक्षर device drivers, like Alan's
 * watchकरोg, Ted's अक्रमom, etc. etc.
 *
 *	1.07	Paul Gorपंचांगaker.
 *	1.08	Miquel van Smoorenburg: disallow certain things on the
 *		DEC Alpha as the CMOS घड़ी is also used क्रम other things.
 *	1.09	Nikita Schmidt: epoch support and some Alpha cleanup.
 *	1.09a	Pete Zaitcev: Sun SPARC
 *	1.09b	Jeff Garzik: Modularize, init cleanup
 *	1.09c	Jeff Garzik: SMP cleanup
 *	1.10    Paul Barton-Davis: add support क्रम async I/O
 *	1.10a	Andrea Arcangeli: Alpha updates
 *	1.10b	Andrew Morton: SMP lock fix
 *	1.10c	Cesar Barros: SMP locking fixes and cleanup
 *	1.10d	Paul Gorपंचांगaker: delete paranoia check in rtc_निकास
 *	1.10e	Maciej W. Rozycki: Handle DECstation's year weirdness.
 *      1.11    Takashi Iwai: Kernel access functions
 *			      rtc_रेजिस्टर/rtc_unरेजिस्टर/rtc_control
 *      1.11a   Daniele Bellucci: Audit create_proc_पढ़ो_entry in rtc_init
 *	1.12	Venkatesh Pallipadi: Hooks क्रम emulating rtc on HPET base-समयr
 *		CONFIG_HPET_EMULATE_RTC
 *	1.13	Nobuhiro Iwamatsu: Updata driver.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/rtc.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/bcd.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>

#घोषणा DRV_NAME	"rs5c313"

#अगर_घोषित CONFIG_SH_LANDISK
/*****************************************************/
/* LANDISK dependence part of RS5C313                */
/*****************************************************/

#घोषणा SCSMR1		0xFFE00000
#घोषणा SCSCR1		0xFFE00008
#घोषणा SCSMR1_CA	0x80
#घोषणा SCSCR1_CKE	0x03
#घोषणा SCSPTR1		0xFFE0001C
#घोषणा SCSPTR1_EIO	0x80
#घोषणा SCSPTR1_SPB1IO	0x08
#घोषणा SCSPTR1_SPB1DT	0x04
#घोषणा SCSPTR1_SPB0IO	0x02
#घोषणा SCSPTR1_SPB0DT	0x01

#घोषणा SDA_OEN		SCSPTR1_SPB1IO
#घोषणा SDA		SCSPTR1_SPB1DT
#घोषणा SCL_OEN		SCSPTR1_SPB0IO
#घोषणा SCL		SCSPTR1_SPB0DT

/* RICOH RS5C313 CE port */
#घोषणा RS5C313_CE	0xB0000003

/* RICOH RS5C313 CE port bit */
#घोषणा RS5C313_CE_RTCCE	0x02

/* SCSPTR1 data */
अचिन्हित अक्षर scsptr1_data;

#घोषणा RS5C313_CEENABLE    __raw_ग_लिखोb(RS5C313_CE_RTCCE, RS5C313_CE);
#घोषणा RS5C313_CEDISABLE   __raw_ग_लिखोb(0x00, RS5C313_CE)
#घोषणा RS5C313_MISCOP      __raw_ग_लिखोb(0x02, 0xB0000008)

अटल व्योम rs5c313_init_port(व्योम)
अणु
	/* Set SCK as I/O port and Initialize SCSPTR1 data & I/O port. */
	__raw_ग_लिखोb(__raw_पढ़ोb(SCSMR1) & ~SCSMR1_CA, SCSMR1);
	__raw_ग_लिखोb(__raw_पढ़ोb(SCSCR1) & ~SCSCR1_CKE, SCSCR1);

	/* And Initialize SCL क्रम RS5C313 घड़ी */
	scsptr1_data = __raw_पढ़ोb(SCSPTR1) | SCL;	/* SCL:H */
	__raw_ग_लिखोb(scsptr1_data, SCSPTR1);
	scsptr1_data = __raw_पढ़ोb(SCSPTR1) | SCL_OEN;	/* SCL output enable */
	__raw_ग_लिखोb(scsptr1_data, SCSPTR1);
	RS5C313_CEDISABLE;	/* CE:L */
पूर्ण

अटल व्योम rs5c313_ग_लिखो_data(अचिन्हित अक्षर data)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		/* SDA:Write Data */
		scsptr1_data = (scsptr1_data & ~SDA) |
				((((0x80 >> i) & data) >> (7 - i)) << 2);
		__raw_ग_लिखोb(scsptr1_data, SCSPTR1);
		अगर (i == 0) अणु
			scsptr1_data |= SDA_OEN;	/* SDA:output enable */
			__raw_ग_लिखोb(scsptr1_data, SCSPTR1);
		पूर्ण
		ndelay(700);
		scsptr1_data &= ~SCL;	/* SCL:L */
		__raw_ग_लिखोb(scsptr1_data, SCSPTR1);
		ndelay(700);
		scsptr1_data |= SCL;	/* SCL:H */
		__raw_ग_लिखोb(scsptr1_data, SCSPTR1);
	पूर्ण

	scsptr1_data &= ~SDA_OEN;	/* SDA:output disable */
	__raw_ग_लिखोb(scsptr1_data, SCSPTR1);
पूर्ण

अटल अचिन्हित अक्षर rs5c313_पढ़ो_data(व्योम)
अणु
	पूर्णांक i;
	अचिन्हित अक्षर data = 0;

	क्रम (i = 0; i < 8; i++) अणु
		ndelay(700);
		/* SDA:Read Data */
		data |= ((__raw_पढ़ोb(SCSPTR1) & SDA) >> 2) << (7 - i);
		scsptr1_data &= ~SCL;	/* SCL:L */
		__raw_ग_लिखोb(scsptr1_data, SCSPTR1);
		ndelay(700);
		scsptr1_data |= SCL;	/* SCL:H */
		__raw_ग_लिखोb(scsptr1_data, SCSPTR1);
	पूर्ण
	वापस data & 0x0F;
पूर्ण

#पूर्ण_अगर /* CONFIG_SH_LANDISK */

/*****************************************************/
/* machine independence part of RS5C313              */
/*****************************************************/

/* RICOH RS5C313 address */
#घोषणा RS5C313_ADDR_SEC	0x00
#घोषणा RS5C313_ADDR_SEC10	0x01
#घोषणा RS5C313_ADDR_MIN	0x02
#घोषणा RS5C313_ADDR_MIN10	0x03
#घोषणा RS5C313_ADDR_HOUR	0x04
#घोषणा RS5C313_ADDR_HOUR10	0x05
#घोषणा RS5C313_ADDR_WEEK	0x06
#घोषणा RS5C313_ADDR_INTINTVREG	0x07
#घोषणा RS5C313_ADDR_DAY	0x08
#घोषणा RS5C313_ADDR_DAY10	0x09
#घोषणा RS5C313_ADDR_MON	0x0A
#घोषणा RS5C313_ADDR_MON10	0x0B
#घोषणा RS5C313_ADDR_YEAR	0x0C
#घोषणा RS5C313_ADDR_YEAR10	0x0D
#घोषणा RS5C313_ADDR_CNTREG	0x0E
#घोषणा RS5C313_ADDR_TESTREG	0x0F

/* RICOH RS5C313 control रेजिस्टर */
#घोषणा RS5C313_CNTREG_ADJ_BSY	0x01
#घोषणा RS5C313_CNTREG_WTEN_XSTP	0x02
#घोषणा RS5C313_CNTREG_12_24	0x04
#घोषणा RS5C313_CNTREG_CTFG	0x08

/* RICOH RS5C313 test रेजिस्टर */
#घोषणा RS5C313_TESTREG_TEST	0x01

/* RICOH RS5C313 control bit */
#घोषणा RS5C313_CNTBIT_READ	0x40
#घोषणा RS5C313_CNTBIT_AD	0x20
#घोषणा RS5C313_CNTBIT_DT	0x10

अटल अचिन्हित अक्षर rs5c313_पढ़ो_reg(अचिन्हित अक्षर addr)
अणु

	rs5c313_ग_लिखो_data(addr | RS5C313_CNTBIT_READ | RS5C313_CNTBIT_AD);
	वापस rs5c313_पढ़ो_data();
पूर्ण

अटल व्योम rs5c313_ग_लिखो_reg(अचिन्हित अक्षर addr, अचिन्हित अक्षर data)
अणु
	data &= 0x0f;
	rs5c313_ग_लिखो_data(addr | RS5C313_CNTBIT_AD);
	rs5c313_ग_लिखो_data(data | RS5C313_CNTBIT_DT);
	वापस;
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर rs5c313_पढ़ो_cntreg(व्योम)
अणु
	वापस rs5c313_पढ़ो_reg(RS5C313_ADDR_CNTREG);
पूर्ण

अटल अंतरभूत व्योम rs5c313_ग_लिखो_cntreg(अचिन्हित अक्षर data)
अणु
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_CNTREG, data);
पूर्ण

अटल अंतरभूत व्योम rs5c313_ग_लिखो_पूर्णांकपूर्णांकvreg(अचिन्हित अक्षर data)
अणु
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_INTINTVREG, data);
पूर्ण

अटल पूर्णांक rs5c313_rtc_पढ़ो_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	पूर्णांक data;
	पूर्णांक cnt;

	cnt = 0;
	जबतक (1) अणु
		RS5C313_CEENABLE;	/* CE:H */

		/* Initialize control reg. 24 hour */
		rs5c313_ग_लिखो_cntreg(0x04);

		अगर (!(rs5c313_पढ़ो_cntreg() & RS5C313_CNTREG_ADJ_BSY))
			अवरोध;

		RS5C313_CEDISABLE;
		ndelay(700);	/* CE:L */

		अगर (cnt++ > 100) अणु
			dev_err(dev, "%s: timeout error\n", __func__);
			वापस -EIO;
		पूर्ण
	पूर्ण

	data = rs5c313_पढ़ो_reg(RS5C313_ADDR_SEC);
	data |= (rs5c313_पढ़ो_reg(RS5C313_ADDR_SEC10) << 4);
	पंचांग->पंचांग_sec = bcd2bin(data);

	data = rs5c313_पढ़ो_reg(RS5C313_ADDR_MIN);
	data |= (rs5c313_पढ़ो_reg(RS5C313_ADDR_MIN10) << 4);
	पंचांग->पंचांग_min = bcd2bin(data);

	data = rs5c313_पढ़ो_reg(RS5C313_ADDR_HOUR);
	data |= (rs5c313_पढ़ो_reg(RS5C313_ADDR_HOUR10) << 4);
	पंचांग->पंचांग_hour = bcd2bin(data);

	data = rs5c313_पढ़ो_reg(RS5C313_ADDR_DAY);
	data |= (rs5c313_पढ़ो_reg(RS5C313_ADDR_DAY10) << 4);
	पंचांग->पंचांग_mday = bcd2bin(data);

	data = rs5c313_पढ़ो_reg(RS5C313_ADDR_MON);
	data |= (rs5c313_पढ़ो_reg(RS5C313_ADDR_MON10) << 4);
	पंचांग->पंचांग_mon = bcd2bin(data) - 1;

	data = rs5c313_पढ़ो_reg(RS5C313_ADDR_YEAR);
	data |= (rs5c313_पढ़ो_reg(RS5C313_ADDR_YEAR10) << 4);
	पंचांग->पंचांग_year = bcd2bin(data);

	अगर (पंचांग->पंचांग_year < 70)
		पंचांग->पंचांग_year += 100;

	data = rs5c313_पढ़ो_reg(RS5C313_ADDR_WEEK);
	पंचांग->पंचांग_wday = bcd2bin(data);

	RS5C313_CEDISABLE;
	ndelay(700);		/* CE:L */

	वापस 0;
पूर्ण

अटल पूर्णांक rs5c313_rtc_set_समय(काष्ठा device *dev, काष्ठा rtc_समय *पंचांग)
अणु
	पूर्णांक data;
	पूर्णांक cnt;

	cnt = 0;
	/* busy check. */
	जबतक (1) अणु
		RS5C313_CEENABLE;	/* CE:H */

		/* Initiatlize control reg. 24 hour */
		rs5c313_ग_लिखो_cntreg(0x04);

		अगर (!(rs5c313_पढ़ो_cntreg() & RS5C313_CNTREG_ADJ_BSY))
			अवरोध;
		RS5C313_MISCOP;
		RS5C313_CEDISABLE;
		ndelay(700);	/* CE:L */

		अगर (cnt++ > 100) अणु
			dev_err(dev, "%s: timeout error\n", __func__);
			वापस -EIO;
		पूर्ण
	पूर्ण

	data = bin2bcd(पंचांग->पंचांग_sec);
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_SEC, data);
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_SEC10, (data >> 4));

	data = bin2bcd(पंचांग->पंचांग_min);
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_MIN, data);
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_MIN10, (data >> 4));

	data = bin2bcd(पंचांग->पंचांग_hour);
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_HOUR, data);
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_HOUR10, (data >> 4));

	data = bin2bcd(पंचांग->पंचांग_mday);
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_DAY, data);
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_DAY10, (data >> 4));

	data = bin2bcd(पंचांग->पंचांग_mon + 1);
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_MON, data);
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_MON10, (data >> 4));

	data = bin2bcd(पंचांग->पंचांग_year % 100);
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_YEAR, data);
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_YEAR10, (data >> 4));

	data = bin2bcd(पंचांग->पंचांग_wday);
	rs5c313_ग_लिखो_reg(RS5C313_ADDR_WEEK, data);

	RS5C313_CEDISABLE;	/* CE:H */
	ndelay(700);

	वापस 0;
पूर्ण

अटल व्योम rs5c313_check_xstp_bit(व्योम)
अणु
	काष्ठा rtc_समय पंचांग;
	पूर्णांक cnt;

	RS5C313_CEENABLE;	/* CE:H */
	अगर (rs5c313_पढ़ो_cntreg() & RS5C313_CNTREG_WTEN_XSTP) अणु
		/* INT पूर्णांकerval reg. OFF */
		rs5c313_ग_लिखो_पूर्णांकपूर्णांकvreg(0x00);
		/* Initialize control reg. 24 hour & adjust */
		rs5c313_ग_लिखो_cntreg(0x07);

		/* busy check. */
		क्रम (cnt = 0; cnt < 100; cnt++) अणु
			अगर (!(rs5c313_पढ़ो_cntreg() & RS5C313_CNTREG_ADJ_BSY))
				अवरोध;
			RS5C313_MISCOP;
		पूर्ण

		स_रखो(&पंचांग, 0, माप(काष्ठा rtc_समय));
		पंचांग.पंचांग_mday	= 1;
		पंचांग.पंचांग_mon	= 1 - 1;
		पंचांग.पंचांग_year	= 2000 - 1900;

		rs5c313_rtc_set_समय(शून्य, &पंचांग);
		pr_err("invalid value, resetting to 1 Jan 2000\n");
	पूर्ण
	RS5C313_CEDISABLE;
	ndelay(700);		/* CE:L */
पूर्ण

अटल स्थिर काष्ठा rtc_class_ops rs5c313_rtc_ops = अणु
	.पढ़ो_समय = rs5c313_rtc_पढ़ो_समय,
	.set_समय = rs5c313_rtc_set_समय,
पूर्ण;

अटल पूर्णांक rs5c313_rtc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा rtc_device *rtc;

	rs5c313_init_port();
	rs5c313_check_xstp_bit();

	rtc = devm_rtc_device_रेजिस्टर(&pdev->dev, "rs5c313", &rs5c313_rtc_ops,
				       THIS_MODULE);

	वापस PTR_ERR_OR_ZERO(rtc);
पूर्ण

अटल काष्ठा platक्रमm_driver rs5c313_rtc_platक्रमm_driver = अणु
	.driver         = अणु
		.name   = DRV_NAME,
	पूर्ण,
	.probe	= rs5c313_rtc_probe,
पूर्ण;

module_platक्रमm_driver(rs5c313_rtc_platक्रमm_driver);

MODULE_AUTHOR("kogiidena , Nobuhiro Iwamatsu <iwamatsu@nigauri.org>");
MODULE_DESCRIPTION("Ricoh RS5C313 RTC device driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
