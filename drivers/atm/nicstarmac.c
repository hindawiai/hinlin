<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * this file included by nicstar.c
 */

/*
 * nicstarmac.c
 * Read this ForeRunner's MAC address from eprom/eeprom
 */

#समावेश <linux/kernel.h>

प्रकार व्योम __iomem *virt_addr_t;

#घोषणा CYCLE_DELAY 5

/*
   This was the original definition
#घोषणा osp_MicroDelay(microsec) \
    करो अणु पूर्णांक _i = 4*microsec; जबतक (--_i > 0) अणु __SLOW_DOWN_IO; पूर्णपूर्ण जबतक (0)
*/
#घोषणा osp_MicroDelay(microsec) अणुअचिन्हित दीर्घ useconds = (microsec); \
                                  udelay((useconds));पूर्ण
/*
 * The following tables represent the timing diagrams found in
 * the Data Sheet क्रम the Xicor X25020 EEProm.  The #घोषणाs below
 * represent the bits in the NICStAR's General Purpose रेजिस्टर
 * that must be toggled क्रम the corresponding actions on the EEProm
 * to occur.
 */

/* Write Data To EEProm from SI line on rising edge of CLK */
/* Read Data From EEProm on falling edge of CLK */

#घोषणा CS_HIGH		0x0002	/* Chip select high */
#घोषणा CS_LOW		0x0000	/* Chip select low (active low) */
#घोषणा CLK_HIGH	0x0004	/* Clock high */
#घोषणा CLK_LOW		0x0000	/* Clock low  */
#घोषणा SI_HIGH		0x0001	/* Serial input data high */
#घोषणा SI_LOW		0x0000	/* Serial input data low */

/* Read Status Register = 0000 0101b */
#अगर 0
अटल u_पूर्णांक32_t rdsrtab[] = अणु
	CS_HIGH | CLK_HIGH,
	CS_LOW | CLK_LOW,
	CLK_HIGH,		/* 0 */
	CLK_LOW,
	CLK_HIGH,		/* 0 */
	CLK_LOW,
	CLK_HIGH,		/* 0 */
	CLK_LOW,
	CLK_HIGH,		/* 0 */
	CLK_LOW,
	CLK_HIGH,		/* 0 */
	CLK_LOW | SI_HIGH,
	CLK_HIGH | SI_HIGH,	/* 1 */
	CLK_LOW | SI_LOW,
	CLK_HIGH,		/* 0 */
	CLK_LOW | SI_HIGH,
	CLK_HIGH | SI_HIGH	/* 1 */
पूर्ण;
#पूर्ण_अगर /*  0  */

/* Read from EEPROM = 0000 0011b */
अटल u_पूर्णांक32_t पढ़ोtab[] = अणु
	/*
	   CS_HIGH | CLK_HIGH,
	 */
	CS_LOW | CLK_LOW,
	CLK_HIGH,		/* 0 */
	CLK_LOW,
	CLK_HIGH,		/* 0 */
	CLK_LOW,
	CLK_HIGH,		/* 0 */
	CLK_LOW,
	CLK_HIGH,		/* 0 */
	CLK_LOW,
	CLK_HIGH,		/* 0 */
	CLK_LOW,
	CLK_HIGH,		/* 0 */
	CLK_LOW | SI_HIGH,
	CLK_HIGH | SI_HIGH,	/* 1 */
	CLK_LOW | SI_HIGH,
	CLK_HIGH | SI_HIGH	/* 1 */
पूर्ण;

/* Clock to पढ़ो from/ग_लिखो to the eeprom */
अटल u_पूर्णांक32_t घड़ीtab[] = अणु
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW,
	CLK_HIGH,
	CLK_LOW
पूर्ण;

#घोषणा NICSTAR_REG_WRITE(bs, reg, val) \
	जबतक ( पढ़ोl(bs + STAT) & 0x0200 ) ; \
	ग_लिखोl((val),(base)+(reg))
#घोषणा NICSTAR_REG_READ(bs, reg) \
	पढ़ोl((base)+(reg))
#घोषणा NICSTAR_REG_GENERAL_PURPOSE GP

/*
 * This routine will घड़ी the Read_Status_reg function पूर्णांकo the X2520
 * eeprom, then pull the result from bit 16 of the NicSTaR's General Purpose 
 * रेजिस्टर.  
 */
#अगर 0
u_पूर्णांक32_t nicstar_पढ़ो_eprom_status(virt_addr_t base)
अणु
	u_पूर्णांक32_t val;
	u_पूर्णांक32_t rbyte;
	पूर्णांक32_t i, j;

	/* Send पढ़ो inकाष्ठाion */
	val = NICSTAR_REG_READ(base, NICSTAR_REG_GENERAL_PURPOSE) & 0xFFFFFFF0;

	क्रम (i = 0; i < ARRAY_SIZE(rdsrtab); i++) अणु
		NICSTAR_REG_WRITE(base, NICSTAR_REG_GENERAL_PURPOSE,
				  (val | rdsrtab[i]));
		osp_MicroDelay(CYCLE_DELAY);
	पूर्ण

	/* Done sending inकाष्ठाion - now pull data off of bit 16, MSB first */
	/* Data घड़ीed out of eeprom on falling edge of घड़ी */

	rbyte = 0;
	क्रम (i = 7, j = 0; i >= 0; i--) अणु
		NICSTAR_REG_WRITE(base, NICSTAR_REG_GENERAL_PURPOSE,
				  (val | घड़ीtab[j++]));
		rbyte |= (((NICSTAR_REG_READ(base, NICSTAR_REG_GENERAL_PURPOSE)
			    & 0x00010000) >> 16) << i);
		NICSTAR_REG_WRITE(base, NICSTAR_REG_GENERAL_PURPOSE,
				  (val | घड़ीtab[j++]));
		osp_MicroDelay(CYCLE_DELAY);
	पूर्ण
	NICSTAR_REG_WRITE(base, NICSTAR_REG_GENERAL_PURPOSE, 2);
	osp_MicroDelay(CYCLE_DELAY);
	वापस rbyte;
पूर्ण
#पूर्ण_अगर /*  0  */

/*
 * This routine will घड़ी the Read_data function पूर्णांकo the X2520
 * eeprom, followed by the address to पढ़ो from, through the NicSTaR's General
 * Purpose रेजिस्टर.  
 */

अटल u_पूर्णांक8_t पढ़ो_eprom_byte(virt_addr_t base, u_पूर्णांक8_t offset)
अणु
	u_पूर्णांक32_t val = 0;
	पूर्णांक i, j = 0;
	u_पूर्णांक8_t tempपढ़ो = 0;

	val = NICSTAR_REG_READ(base, NICSTAR_REG_GENERAL_PURPOSE) & 0xFFFFFFF0;

	/* Send READ inकाष्ठाion */
	क्रम (i = 0; i < ARRAY_SIZE(पढ़ोtab); i++) अणु
		NICSTAR_REG_WRITE(base, NICSTAR_REG_GENERAL_PURPOSE,
				  (val | पढ़ोtab[i]));
		osp_MicroDelay(CYCLE_DELAY);
	पूर्ण

	/* Next, we need to send the byte address to पढ़ो from */
	क्रम (i = 7; i >= 0; i--) अणु
		NICSTAR_REG_WRITE(base, NICSTAR_REG_GENERAL_PURPOSE,
				  (val | घड़ीtab[j++] | ((offset >> i) & 1)));
		osp_MicroDelay(CYCLE_DELAY);
		NICSTAR_REG_WRITE(base, NICSTAR_REG_GENERAL_PURPOSE,
				  (val | घड़ीtab[j++] | ((offset >> i) & 1)));
		osp_MicroDelay(CYCLE_DELAY);
	पूर्ण

	j = 0;

	/* Now, we can पढ़ो data from the eeprom by घड़ीing it in */
	क्रम (i = 7; i >= 0; i--) अणु
		NICSTAR_REG_WRITE(base, NICSTAR_REG_GENERAL_PURPOSE,
				  (val | घड़ीtab[j++]));
		osp_MicroDelay(CYCLE_DELAY);
		tempपढ़ो |=
		    (((NICSTAR_REG_READ(base, NICSTAR_REG_GENERAL_PURPOSE)
		       & 0x00010000) >> 16) << i);
		NICSTAR_REG_WRITE(base, NICSTAR_REG_GENERAL_PURPOSE,
				  (val | घड़ीtab[j++]));
		osp_MicroDelay(CYCLE_DELAY);
	पूर्ण

	NICSTAR_REG_WRITE(base, NICSTAR_REG_GENERAL_PURPOSE, 2);
	osp_MicroDelay(CYCLE_DELAY);
	वापस tempपढ़ो;
पूर्ण

अटल व्योम nicstar_init_eprom(virt_addr_t base)
अणु
	u_पूर्णांक32_t val;

	/*
	 * turn chip select off
	 */
	val = NICSTAR_REG_READ(base, NICSTAR_REG_GENERAL_PURPOSE) & 0xFFFFFFF0;

	NICSTAR_REG_WRITE(base, NICSTAR_REG_GENERAL_PURPOSE,
			  (val | CS_HIGH | CLK_HIGH));
	osp_MicroDelay(CYCLE_DELAY);

	NICSTAR_REG_WRITE(base, NICSTAR_REG_GENERAL_PURPOSE,
			  (val | CS_HIGH | CLK_LOW));
	osp_MicroDelay(CYCLE_DELAY);

	NICSTAR_REG_WRITE(base, NICSTAR_REG_GENERAL_PURPOSE,
			  (val | CS_HIGH | CLK_HIGH));
	osp_MicroDelay(CYCLE_DELAY);

	NICSTAR_REG_WRITE(base, NICSTAR_REG_GENERAL_PURPOSE,
			  (val | CS_HIGH | CLK_LOW));
	osp_MicroDelay(CYCLE_DELAY);
पूर्ण

/*
 * This routine will be the पूर्णांकerface to the ReadPromByte function
 * above.
 */

अटल व्योम
nicstar_पढ़ो_eprom(virt_addr_t base,
		   u_पूर्णांक8_t prom_offset, u_पूर्णांक8_t * buffer, u_पूर्णांक32_t nbytes)
अणु
	u_पूर्णांक i;

	क्रम (i = 0; i < nbytes; i++) अणु
		buffer[i] = पढ़ो_eprom_byte(base, prom_offset);
		++prom_offset;
		osp_MicroDelay(CYCLE_DELAY);
	पूर्ण
पूर्ण
