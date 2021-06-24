<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2000, 2001 Broadcom Corporation
 *
 * Copyright (C) 2002 MontaVista Software Inc.
 * Author: jsun@mvista.com or jsun@junsun.net
 */
#समावेश <linux/bcd.h>
#समावेश <linux/types.h>
#समावेश <linux/समय.स>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/addrspace.h>
#समावेश <यंत्र/पन.स>

#समावेश <यंत्र/sibyte/sb1250.h>
#समावेश <यंत्र/sibyte/sb1250_regs.h>
#समावेश <यंत्र/sibyte/sb1250_smbus.h>


/* M41T81 definitions */

/*
 * Register bits
 */

#घोषणा M41T81REG_SC_ST		0x80		/* stop bit */
#घोषणा M41T81REG_HR_CB		0x40		/* century bit */
#घोषणा M41T81REG_HR_CEB	0x80		/* century enable bit */
#घोषणा M41T81REG_CTL_S		0x20		/* sign bit */
#घोषणा M41T81REG_CTL_FT	0x40		/* frequency test bit */
#घोषणा M41T81REG_CTL_OUT	0x80		/* output level */
#घोषणा M41T81REG_WD_RB0	0x01		/* watchकरोg resolution bit 0 */
#घोषणा M41T81REG_WD_RB1	0x02		/* watchकरोg resolution bit 1 */
#घोषणा M41T81REG_WD_BMB0	0x04		/* watchकरोg multiplier bit 0 */
#घोषणा M41T81REG_WD_BMB1	0x08		/* watchकरोg multiplier bit 1 */
#घोषणा M41T81REG_WD_BMB2	0x10		/* watchकरोg multiplier bit 2 */
#घोषणा M41T81REG_WD_BMB3	0x20		/* watchकरोg multiplier bit 3 */
#घोषणा M41T81REG_WD_BMB4	0x40		/* watchकरोg multiplier bit 4 */
#घोषणा M41T81REG_AMO_ABE	0x20		/* alarm in "battery back-up mode" enable bit */
#घोषणा M41T81REG_AMO_SQWE	0x40		/* square wave enable */
#घोषणा M41T81REG_AMO_AFE	0x80		/* alarm flag enable flag */
#घोषणा M41T81REG_ADT_RPT5	0x40		/* alarm repeat mode bit 5 */
#घोषणा M41T81REG_ADT_RPT4	0x80		/* alarm repeat mode bit 4 */
#घोषणा M41T81REG_AHR_RPT3	0x80		/* alarm repeat mode bit 3 */
#घोषणा M41T81REG_AHR_HT	0x40		/* halt update bit */
#घोषणा M41T81REG_AMN_RPT2	0x80		/* alarm repeat mode bit 2 */
#घोषणा M41T81REG_ASC_RPT1	0x80		/* alarm repeat mode bit 1 */
#घोषणा M41T81REG_FLG_AF	0x40		/* alarm flag (पढ़ो only) */
#घोषणा M41T81REG_FLG_WDF	0x80		/* watchकरोg flag (पढ़ो only) */
#घोषणा M41T81REG_SQW_RS0	0x10		/* sqw frequency bit 0 */
#घोषणा M41T81REG_SQW_RS1	0x20		/* sqw frequency bit 1 */
#घोषणा M41T81REG_SQW_RS2	0x40		/* sqw frequency bit 2 */
#घोषणा M41T81REG_SQW_RS3	0x80		/* sqw frequency bit 3 */


/*
 * Register numbers
 */

#घोषणा M41T81REG_TSC	0x00		/* tenths/hundredths of second */
#घोषणा M41T81REG_SC	0x01		/* seconds */
#घोषणा M41T81REG_MN	0x02		/* minute */
#घोषणा M41T81REG_HR	0x03		/* hour/century */
#घोषणा M41T81REG_DY	0x04		/* day of week */
#घोषणा M41T81REG_DT	0x05		/* date of month */
#घोषणा M41T81REG_MO	0x06		/* month */
#घोषणा M41T81REG_YR	0x07		/* year */
#घोषणा M41T81REG_CTL	0x08		/* control */
#घोषणा M41T81REG_WD	0x09		/* watchकरोg */
#घोषणा M41T81REG_AMO	0x0A		/* alarm: month */
#घोषणा M41T81REG_ADT	0x0B		/* alarm: date */
#घोषणा M41T81REG_AHR	0x0C		/* alarm: hour */
#घोषणा M41T81REG_AMN	0x0D		/* alarm: minute */
#घोषणा M41T81REG_ASC	0x0E		/* alarm: second */
#घोषणा M41T81REG_FLG	0x0F		/* flags */
#घोषणा M41T81REG_SQW	0x13		/* square wave रेजिस्टर */

#घोषणा M41T81_CCR_ADDRESS	0x68

#घोषणा SMB_CSR(reg)	IOADDR(A_SMB_REGISTER(1, reg))

अटल पूर्णांक m41t81_पढ़ो(uपूर्णांक8_t addr)
अणु
	जबतक (__raw_पढ़ोq(SMB_CSR(R_SMB_STATUS)) & M_SMB_BUSY)
		;

	__raw_ग_लिखोq(addr & 0xff, SMB_CSR(R_SMB_CMD));
	__raw_ग_लिखोq(V_SMB_ADDR(M41T81_CCR_ADDRESS) | V_SMB_TT_WR1BYTE,
		     SMB_CSR(R_SMB_START));

	जबतक (__raw_पढ़ोq(SMB_CSR(R_SMB_STATUS)) & M_SMB_BUSY)
		;

	__raw_ग_लिखोq(V_SMB_ADDR(M41T81_CCR_ADDRESS) | V_SMB_TT_RD1BYTE,
		     SMB_CSR(R_SMB_START));

	जबतक (__raw_पढ़ोq(SMB_CSR(R_SMB_STATUS)) & M_SMB_BUSY)
		;

	अगर (__raw_पढ़ोq(SMB_CSR(R_SMB_STATUS)) & M_SMB_ERROR) अणु
		/* Clear error bit by writing a 1 */
		__raw_ग_लिखोq(M_SMB_ERROR, SMB_CSR(R_SMB_STATUS));
		वापस -1;
	पूर्ण

	वापस __raw_पढ़ोq(SMB_CSR(R_SMB_DATA)) & 0xff;
पूर्ण

अटल पूर्णांक m41t81_ग_लिखो(uपूर्णांक8_t addr, पूर्णांक b)
अणु
	जबतक (__raw_पढ़ोq(SMB_CSR(R_SMB_STATUS)) & M_SMB_BUSY)
		;

	__raw_ग_लिखोq(addr & 0xff, SMB_CSR(R_SMB_CMD));
	__raw_ग_लिखोq(b & 0xff, SMB_CSR(R_SMB_DATA));
	__raw_ग_लिखोq(V_SMB_ADDR(M41T81_CCR_ADDRESS) | V_SMB_TT_WR2BYTE,
		     SMB_CSR(R_SMB_START));

	जबतक (__raw_पढ़ोq(SMB_CSR(R_SMB_STATUS)) & M_SMB_BUSY)
		;

	अगर (__raw_पढ़ोq(SMB_CSR(R_SMB_STATUS)) & M_SMB_ERROR) अणु
		/* Clear error bit by writing a 1 */
		__raw_ग_लिखोq(M_SMB_ERROR, SMB_CSR(R_SMB_STATUS));
		वापस -1;
	पूर्ण

	/* पढ़ो the same byte again to make sure it is written */
	__raw_ग_लिखोq(V_SMB_ADDR(M41T81_CCR_ADDRESS) | V_SMB_TT_RD1BYTE,
		     SMB_CSR(R_SMB_START));

	जबतक (__raw_पढ़ोq(SMB_CSR(R_SMB_STATUS)) & M_SMB_BUSY)
		;

	वापस 0;
पूर्ण

पूर्णांक m41t81_set_समय(समय64_t t)
अणु
	काष्ठा rtc_समय पंचांग;
	अचिन्हित दीर्घ flags;

	/* Note we करोn't care about the century */
	rtc_समय64_to_पंचांग(t, &पंचांग);

	/*
	 * Note the ग_लिखो order matters as it ensures the correctness.
	 * When we ग_लिखो sec, 10th sec is clear.  It is reasonable to
	 * believe we should finish writing min within a second.
	 */

	spin_lock_irqsave(&rtc_lock, flags);
	पंचांग.पंचांग_sec = bin2bcd(पंचांग.पंचांग_sec);
	m41t81_ग_लिखो(M41T81REG_SC, पंचांग.पंचांग_sec);

	पंचांग.पंचांग_min = bin2bcd(पंचांग.पंचांग_min);
	m41t81_ग_लिखो(M41T81REG_MN, पंचांग.पंचांग_min);

	पंचांग.पंचांग_hour = bin2bcd(पंचांग.पंचांग_hour);
	पंचांग.पंचांग_hour = (पंचांग.पंचांग_hour & 0x3f) | (m41t81_पढ़ो(M41T81REG_HR) & 0xc0);
	m41t81_ग_लिखो(M41T81REG_HR, पंचांग.पंचांग_hour);

	/* पंचांग_wday starts from 0 to 6 */
	अगर (पंचांग.पंचांग_wday == 0) पंचांग.पंचांग_wday = 7;
	पंचांग.पंचांग_wday = bin2bcd(पंचांग.पंचांग_wday);
	m41t81_ग_लिखो(M41T81REG_DY, पंचांग.पंचांग_wday);

	पंचांग.पंचांग_mday = bin2bcd(पंचांग.पंचांग_mday);
	m41t81_ग_लिखो(M41T81REG_DT, पंचांग.पंचांग_mday);

	/* पंचांग_mon starts from 0, *ick* */
	पंचांग.पंचांग_mon ++;
	पंचांग.पंचांग_mon = bin2bcd(पंचांग.पंचांग_mon);
	m41t81_ग_लिखो(M41T81REG_MO, पंचांग.पंचांग_mon);

	/* we करोn't करो century, everything is beyond 2000 */
	पंचांग.पंचांग_year %= 100;
	पंचांग.पंचांग_year = bin2bcd(पंचांग.पंचांग_year);
	m41t81_ग_लिखो(M41T81REG_YR, पंचांग.पंचांग_year);
	spin_unlock_irqrestore(&rtc_lock, flags);

	वापस 0;
पूर्ण

समय64_t m41t81_get_समय(व्योम)
अणु
	अचिन्हित पूर्णांक year, mon, day, hour, min, sec;
	अचिन्हित दीर्घ flags;

	/*
	 * min is valid अगर two पढ़ोs of sec are the same.
	 */
	क्रम (;;) अणु
		spin_lock_irqsave(&rtc_lock, flags);
		sec = m41t81_पढ़ो(M41T81REG_SC);
		min = m41t81_पढ़ो(M41T81REG_MN);
		अगर (sec == m41t81_पढ़ो(M41T81REG_SC)) अवरोध;
		spin_unlock_irqrestore(&rtc_lock, flags);
	पूर्ण
	hour = m41t81_पढ़ो(M41T81REG_HR) & 0x3f;
	day = m41t81_पढ़ो(M41T81REG_DT);
	mon = m41t81_पढ़ो(M41T81REG_MO);
	year = m41t81_पढ़ो(M41T81REG_YR);
	spin_unlock_irqrestore(&rtc_lock, flags);

	sec = bcd2bin(sec);
	min = bcd2bin(min);
	hour = bcd2bin(hour);
	day = bcd2bin(day);
	mon = bcd2bin(mon);
	year = bcd2bin(year);

	year += 2000;

	वापस स_गढ़ो64(year, mon, day, hour, min, sec);
पूर्ण

पूर्णांक m41t81_probe(व्योम)
अणु
	अचिन्हित पूर्णांक पंचांगp;

	/* enable chip अगर it is not enabled yet */
	पंचांगp = m41t81_पढ़ो(M41T81REG_SC);
	m41t81_ग_लिखो(M41T81REG_SC, पंचांगp & 0x7f);

	वापस m41t81_पढ़ो(M41T81REG_SC) != -1;
पूर्ण
