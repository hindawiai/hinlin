<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LINUX_SSB_MIPSCORE_H_
#घोषणा LINUX_SSB_MIPSCORE_H_

#अगर_घोषित CONFIG_SSB_DRIVER_MIPS

काष्ठा ssb_device;

काष्ठा ssb_serial_port अणु
	व्योम *regs;
	अचिन्हित दीर्घ घड़ीspeed;
	अचिन्हित पूर्णांक irq;
	अचिन्हित पूर्णांक baud_base;
	अचिन्हित पूर्णांक reg_shअगरt;
पूर्ण;

काष्ठा ssb_pflash अणु
	bool present;
	u8 buswidth;
	u32 winकरोw;
	u32 winकरोw_size;
पूर्ण;

#अगर_घोषित CONFIG_SSB_SFLASH
काष्ठा ssb_sflash अणु
	bool present;
	u32 winकरोw;
	u32 blocksize;
	u16 numblocks;
	u32 size;

	व्योम *priv;
पूर्ण;
#पूर्ण_अगर

काष्ठा ssb_mipscore अणु
	काष्ठा ssb_device *dev;

	पूर्णांक nr_serial_ports;
	काष्ठा ssb_serial_port serial_ports[4];

	काष्ठा ssb_pflash pflash;
#अगर_घोषित CONFIG_SSB_SFLASH
	काष्ठा ssb_sflash sflash;
#पूर्ण_अगर
पूर्ण;

बाह्य व्योम ssb_mipscore_init(काष्ठा ssb_mipscore *mcore);
बाह्य u32 ssb_cpu_घड़ी(काष्ठा ssb_mipscore *mcore);

बाह्य अचिन्हित पूर्णांक ssb_mips_irq(काष्ठा ssb_device *dev);


#अन्यथा /* CONFIG_SSB_DRIVER_MIPS */

काष्ठा ssb_mipscore अणु
पूर्ण;

अटल अंतरभूत
व्योम ssb_mipscore_init(काष्ठा ssb_mipscore *mcore)
अणु
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ssb_mips_irq(काष्ठा ssb_device *dev)
अणु
	वापस 0;
पूर्ण

#पूर्ण_अगर /* CONFIG_SSB_DRIVER_MIPS */

#पूर्ण_अगर /* LINUX_SSB_MIPSCORE_H_ */
