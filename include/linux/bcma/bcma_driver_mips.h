<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_BCMA_DRIVER_MIPS_H_
#घोषणा LINUX_BCMA_DRIVER_MIPS_H_

#घोषणा BCMA_MIPS_IPSFLAG		0x0F08
/* which sbflags get routed to mips पूर्णांकerrupt 1 */
#घोषणा  BCMA_MIPS_IPSFLAG_IRQ1		0x0000003F
#घोषणा  BCMA_MIPS_IPSFLAG_IRQ1_SHIFT	0
/* which sbflags get routed to mips पूर्णांकerrupt 2 */
#घोषणा  BCMA_MIPS_IPSFLAG_IRQ2		0x00003F00
#घोषणा  BCMA_MIPS_IPSFLAG_IRQ2_SHIFT	8
/* which sbflags get routed to mips पूर्णांकerrupt 3 */
#घोषणा  BCMA_MIPS_IPSFLAG_IRQ3		0x003F0000
#घोषणा  BCMA_MIPS_IPSFLAG_IRQ3_SHIFT	16
/* which sbflags get routed to mips पूर्णांकerrupt 4 */
#घोषणा  BCMA_MIPS_IPSFLAG_IRQ4		0x3F000000
#घोषणा  BCMA_MIPS_IPSFLAG_IRQ4_SHIFT	24

/* MIPS 74K core रेजिस्टरs */
#घोषणा BCMA_MIPS_MIPS74K_CORECTL	0x0000
#घोषणा BCMA_MIPS_MIPS74K_EXCEPTBASE	0x0004
#घोषणा BCMA_MIPS_MIPS74K_BIST		0x000C
#घोषणा BCMA_MIPS_MIPS74K_INTMASK_INT0	0x0014
#घोषणा BCMA_MIPS_MIPS74K_INTMASK(पूर्णांक) \
	((पूर्णांक) * 4 + BCMA_MIPS_MIPS74K_INTMASK_INT0)
#घोषणा BCMA_MIPS_MIPS74K_NMIMASK	0x002C
#घोषणा BCMA_MIPS_MIPS74K_GPIOSEL	0x0040
#घोषणा BCMA_MIPS_MIPS74K_GPIOOUT	0x0044
#घोषणा BCMA_MIPS_MIPS74K_GPIOEN	0x0048
#घोषणा BCMA_MIPS_MIPS74K_CLKCTLST	0x01E0

#घोषणा BCMA_MIPS_OOBSELINA74		0x004
#घोषणा BCMA_MIPS_OOBSELOUTA30		0x100

काष्ठा bcma_device;

काष्ठा bcma_drv_mips अणु
	काष्ठा bcma_device *core;
	u8 setup_करोne:1;
	u8 early_setup_करोne:1;
पूर्ण;

बाह्य u32 bcma_cpu_घड़ी(काष्ठा bcma_drv_mips *mcore);

#पूर्ण_अगर /* LINUX_BCMA_DRIVER_MIPS_H_ */
