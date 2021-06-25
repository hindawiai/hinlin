<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __MACH_SE_MRSHPC_H
#घोषणा __MACH_SE_MRSHPC_H

#समावेश <linux/पन.स>

अटल अंतरभूत व्योम __init mrshpc_setup_winकरोws(व्योम)
अणु
	अगर ((__raw_पढ़ोw(MRSHPC_CSR) & 0x000c) != 0)
		वापस;	/* Not detected */

	अगर ((__raw_पढ़ोw(MRSHPC_CSR) & 0x0080) == 0) अणु
		__raw_ग_लिखोw(0x0674, MRSHPC_CPWCR); /* Card Vcc is 3.3v? */
	पूर्ण अन्यथा अणु
		__raw_ग_लिखोw(0x0678, MRSHPC_CPWCR); /* Card Vcc is 5V */
	पूर्ण

	/*
	 *  PC-Card winकरोw खोलो
	 *  flag == COMMON/ATTRIBUTE/IO
	 */
	/* common winकरोw खोलो */
	__raw_ग_लिखोw(0x8a84, MRSHPC_MW0CR1);
	अगर((__raw_पढ़ोw(MRSHPC_CSR) & 0x4000) != 0)
		/* common mode & bus width 16bit SWAP = 1*/
		__raw_ग_लिखोw(0x0b00, MRSHPC_MW0CR2);
	अन्यथा
		/* common mode & bus width 16bit SWAP = 0*/
		__raw_ग_लिखोw(0x0300, MRSHPC_MW0CR2);

	/* attribute winकरोw खोलो */
	__raw_ग_लिखोw(0x8a85, MRSHPC_MW1CR1);
	अगर ((__raw_पढ़ोw(MRSHPC_CSR) & 0x4000) != 0)
		/* attribute mode & bus width 16bit SWAP = 1*/
		__raw_ग_लिखोw(0x0a00, MRSHPC_MW1CR2);
	अन्यथा
		/* attribute mode & bus width 16bit SWAP = 0*/
		__raw_ग_लिखोw(0x0200, MRSHPC_MW1CR2);

	/* I/O winकरोw खोलो */
	__raw_ग_लिखोw(0x8a86, MRSHPC_IOWCR1);
	__raw_ग_लिखोw(0x0008, MRSHPC_CDCR);	 /* I/O card mode */
	अगर ((__raw_पढ़ोw(MRSHPC_CSR) & 0x4000) != 0)
		__raw_ग_लिखोw(0x0a00, MRSHPC_IOWCR2); /* bus width 16bit SWAP = 1*/
	अन्यथा
		__raw_ग_लिखोw(0x0200, MRSHPC_IOWCR2); /* bus width 16bit SWAP = 0*/

	__raw_ग_लिखोw(0x2000, MRSHPC_ICR);
	__raw_ग_लिखोb(0x00, PA_MRSHPC_MW2 + 0x206);
	__raw_ग_लिखोb(0x42, PA_MRSHPC_MW2 + 0x200);
पूर्ण

#पूर्ण_अगर /* __MACH_SE_MRSHPC_H */
