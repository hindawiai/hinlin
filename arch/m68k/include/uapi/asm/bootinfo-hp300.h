<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
** यंत्र/bootinfo-hp300.h -- HP9000/300-specअगरic boot inक्रमmation definitions
*/

#अगर_अघोषित _UAPI_ASM_M68K_BOOTINFO_HP300_H
#घोषणा _UAPI_ASM_M68K_BOOTINFO_HP300_H


    /*
     *  HP9000/300-specअगरic tags
     */

#घोषणा BI_HP300_MODEL		0x8000	/* model (__be32) */
#घोषणा BI_HP300_UART_SCODE	0x8001	/* UART select code (__be32) */
#घोषणा BI_HP300_UART_ADDR	0x8002	/* phys. addr of UART (__be32) */


    /*
     *  HP9000/300 and /400 models (BI_HP300_MODEL)
     *
     * This inक्रमmation was taken from NetBSD
     */

#घोषणा HP_320		0	/* 16MHz 68020+HP MMU+16K बाह्यal cache */
#घोषणा HP_330		1	/* 16MHz 68020+68851 MMU */
#घोषणा HP_340		2	/* 16MHz 68030 */
#घोषणा HP_345		3	/* 50MHz 68030+32K बाह्यal cache */
#घोषणा HP_350		4	/* 25MHz 68020+HP MMU+32K बाह्यal cache */
#घोषणा HP_360		5	/* 25MHz 68030 */
#घोषणा HP_370		6	/* 33MHz 68030+64K बाह्यal cache */
#घोषणा HP_375		7	/* 50MHz 68030+32K बाह्यal cache */
#घोषणा HP_380		8	/* 25MHz 68040 */
#घोषणा HP_385		9	/* 33MHz 68040 */

#घोषणा HP_400		10	/* 50MHz 68030+32K बाह्यal cache */
#घोषणा HP_425T		11	/* 25MHz 68040 - model 425t */
#घोषणा HP_425S		12	/* 25MHz 68040 - model 425s */
#घोषणा HP_425E		13	/* 25MHz 68040 - model 425e */
#घोषणा HP_433T		14	/* 33MHz 68040 - model 433t */
#घोषणा HP_433S		15	/* 33MHz 68040 - model 433s */


    /*
     *  Latest HP9000/300 bootinfo version
     */

#घोषणा HP300_BOOTI_VERSION	MK_BI_VERSION(2, 0)


#पूर्ण_अगर /* _UAPI_ASM_M68K_BOOTINFO_HP300_H */
