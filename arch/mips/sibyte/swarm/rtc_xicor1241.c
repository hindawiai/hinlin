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


/* Xicor 1241 definitions */

/*
 * Register bits
 */

#घोषणा X1241REG_SR_BAT 0x80		/* currently on battery घातer */
#घोषणा X1241REG_SR_RWEL 0x04		/* r/w latch is enabled, can ग_लिखो RTC */
#घोषणा X1241REG_SR_WEL 0x02		/* r/w latch is unlocked, can enable r/w now */
#घोषणा X1241REG_SR_RTCF 0x01		/* घड़ी failed */
#घोषणा X1241REG_BL_BP2 0x80		/* block protect 2 */
#घोषणा X1241REG_BL_BP1 0x40		/* block protect 1 */
#घोषणा X1241REG_BL_BP0 0x20		/* block protect 0 */
#घोषणा X1241REG_BL_WD1 0x10
#घोषणा X1241REG_BL_WD0 0x08
#घोषणा X1241REG_HR_MIL 0x80		/* military समय क्रमmat */

/*
 * Register numbers
 */

#घोषणा X1241REG_BL	0x10		/* block protect bits */
#घोषणा X1241REG_INT	0x11		/*  */
#घोषणा X1241REG_SC	0x30		/* Seconds */
#घोषणा X1241REG_MN	0x31		/* Minutes */
#घोषणा X1241REG_HR	0x32		/* Hours */
#घोषणा X1241REG_DT	0x33		/* Day of month */
#घोषणा X1241REG_MO	0x34		/* Month */
#घोषणा X1241REG_YR	0x35		/* Year */
#घोषणा X1241REG_DW	0x36		/* Day of Week */
#घोषणा X1241REG_Y2K	0x37		/* Year 2K */
#घोषणा X1241REG_SR	0x3F		/* Status रेजिस्टर */

#घोषणा X1241_CCR_ADDRESS	0x6F

#घोषणा SMB_CSR(reg)	IOADDR(A_SMB_REGISTER(1, reg))

अटल पूर्णांक xicor_पढ़ो(uपूर्णांक8_t addr)
अणु
	जबतक (__raw_पढ़ोq(SMB_CSR(R_SMB_STATUS)) & M_SMB_BUSY)
		;

	__raw_ग_लिखोq((addr >> 8) & 0x7, SMB_CSR(R_SMB_CMD));
	__raw_ग_लिखोq(addr & 0xff, SMB_CSR(R_SMB_DATA));
	__raw_ग_लिखोq(V_SMB_ADDR(X1241_CCR_ADDRESS) | V_SMB_TT_WR2BYTE,
		     SMB_CSR(R_SMB_START));

	जबतक (__raw_पढ़ोq(SMB_CSR(R_SMB_STATUS)) & M_SMB_BUSY)
		;

	__raw_ग_लिखोq(V_SMB_ADDR(X1241_CCR_ADDRESS) | V_SMB_TT_RD1BYTE,
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

अटल पूर्णांक xicor_ग_लिखो(uपूर्णांक8_t addr, पूर्णांक b)
अणु
	जबतक (__raw_पढ़ोq(SMB_CSR(R_SMB_STATUS)) & M_SMB_BUSY)
		;

	__raw_ग_लिखोq(addr, SMB_CSR(R_SMB_CMD));
	__raw_ग_लिखोq((addr & 0xff) | ((b & 0xff) << 8), SMB_CSR(R_SMB_DATA));
	__raw_ग_लिखोq(V_SMB_ADDR(X1241_CCR_ADDRESS) | V_SMB_TT_WR3BYTE,
		     SMB_CSR(R_SMB_START));

	जबतक (__raw_पढ़ोq(SMB_CSR(R_SMB_STATUS)) & M_SMB_BUSY)
		;

	अगर (__raw_पढ़ोq(SMB_CSR(R_SMB_STATUS)) & M_SMB_ERROR) अणु
		/* Clear error bit by writing a 1 */
		__raw_ग_लिखोq(M_SMB_ERROR, SMB_CSR(R_SMB_STATUS));
		वापस -1;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

पूर्णांक xicor_set_समय(समय64_t t)
अणु
	काष्ठा rtc_समय पंचांग;
	पूर्णांक पंचांगp;
	अचिन्हित दीर्घ flags;

	rtc_समय64_to_पंचांग(t, &पंचांग);
	पंचांग.पंचांग_year += 1900;

	spin_lock_irqsave(&rtc_lock, flags);
	/* unlock ग_लिखोs to the CCR */
	xicor_ग_लिखो(X1241REG_SR, X1241REG_SR_WEL);
	xicor_ग_लिखो(X1241REG_SR, X1241REG_SR_WEL | X1241REG_SR_RWEL);

	/* trivial ones */
	पंचांग.पंचांग_sec = bin2bcd(पंचांग.पंचांग_sec);
	xicor_ग_लिखो(X1241REG_SC, पंचांग.पंचांग_sec);

	पंचांग.पंचांग_min = bin2bcd(पंचांग.पंचांग_min);
	xicor_ग_लिखो(X1241REG_MN, पंचांग.पंचांग_min);

	पंचांग.पंचांग_mday = bin2bcd(पंचांग.पंचांग_mday);
	xicor_ग_लिखो(X1241REG_DT, पंचांग.पंचांग_mday);

	/* पंचांग_mon starts from 0, *ick* */
	पंचांग.पंचांग_mon ++;
	पंचांग.पंचांग_mon = bin2bcd(पंचांग.पंचांग_mon);
	xicor_ग_लिखो(X1241REG_MO, पंचांग.पंचांग_mon);

	/* year is split */
	पंचांगp = पंचांग.पंचांग_year / 100;
	पंचांग.पंचांग_year %= 100;
	xicor_ग_लिखो(X1241REG_YR, पंचांग.पंचांग_year);
	xicor_ग_लिखो(X1241REG_Y2K, पंचांगp);

	/* hour is the most tricky one */
	पंचांगp = xicor_पढ़ो(X1241REG_HR);
	अगर (पंचांगp & X1241REG_HR_MIL) अणु
		/* 24 hour क्रमmat */
		पंचांग.पंचांग_hour = bin2bcd(पंचांग.पंचांग_hour);
		पंचांगp = (पंचांगp & ~0x3f) | (पंचांग.पंचांग_hour & 0x3f);
	पूर्ण अन्यथा अणु
		/* 12 hour क्रमmat, with 0x2 क्रम pm */
		पंचांगp = पंचांगp & ~0x3f;
		अगर (पंचांग.पंचांग_hour >= 12) अणु
			पंचांगp |= 0x20;
			पंचांग.पंचांग_hour -= 12;
		पूर्ण
		पंचांग.पंचांग_hour = bin2bcd(पंचांग.पंचांग_hour);
		पंचांगp |= पंचांग.पंचांग_hour;
	पूर्ण
	xicor_ग_लिखो(X1241REG_HR, पंचांगp);

	xicor_ग_लिखो(X1241REG_SR, 0);
	spin_unlock_irqrestore(&rtc_lock, flags);

	वापस 0;
पूर्ण

समय64_t xicor_get_समय(व्योम)
अणु
	अचिन्हित पूर्णांक year, mon, day, hour, min, sec, y2k;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtc_lock, flags);
	sec = xicor_पढ़ो(X1241REG_SC);
	min = xicor_पढ़ो(X1241REG_MN);
	hour = xicor_पढ़ो(X1241REG_HR);

	अगर (hour & X1241REG_HR_MIL) अणु
		hour &= 0x3f;
	पूर्ण अन्यथा अणु
		अगर (hour & 0x20)
			hour = (hour & 0xf) + 0x12;
	पूर्ण

	day = xicor_पढ़ो(X1241REG_DT);
	mon = xicor_पढ़ो(X1241REG_MO);
	year = xicor_पढ़ो(X1241REG_YR);
	y2k = xicor_पढ़ो(X1241REG_Y2K);
	spin_unlock_irqrestore(&rtc_lock, flags);

	sec = bcd2bin(sec);
	min = bcd2bin(min);
	hour = bcd2bin(hour);
	day = bcd2bin(day);
	mon = bcd2bin(mon);
	year = bcd2bin(year);
	y2k = bcd2bin(y2k);

	year += (y2k * 100);

	वापस स_गढ़ो64(year, mon, day, hour, min, sec);
पूर्ण

पूर्णांक xicor_probe(व्योम)
अणु
	वापस xicor_पढ़ो(X1241REG_SC) != -1;
पूर्ण
