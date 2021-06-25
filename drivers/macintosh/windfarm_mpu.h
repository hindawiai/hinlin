<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Windfarm PowerMac thermal control
 *
 * Copyright 2012 Benjamin Herrenschmidt, IBM Corp.
 */

#अगर_अघोषित __WINDFARM_MPU_H
#घोषणा __WINDFARM_MPU_H

प्रकार अचिन्हित लघु fu16;
प्रकार पूर्णांक fs32;
प्रकार लघु fs16;

/* Definition of the MPU data काष्ठाure which contains per CPU
 * calibration inक्रमmation (among others) क्रम the G5 machines
 */
काष्ठा mpu_data
अणु
	u8	signature;		/* 0x00 - EEPROM sig. */
	u8	bytes_used;		/* 0x01 - Bytes used in eeprom (160 ?) */
	u8	size;			/* 0x02 - EEPROM size (256 ?) */
	u8	version;		/* 0x03 - EEPROM version */
	u32	data_revision;		/* 0x04 - Dataset revision */
	u8	processor_bin_code[3];	/* 0x08 - Processor BIN code */
	u8	bin_code_expansion;	/* 0x0b - ??? (padding ?) */
	u8	processor_num;		/* 0x0c - Number of CPUs on this MPU */
	u8	input_mul_bus_भाग;	/* 0x0d - Clock input multiplier/bus भागider */
	u8	reserved1[2];		/* 0x0e - */
	u32	input_clk_freq_high;	/* 0x10 - Input घड़ी frequency high */
	u8	cpu_nb_target_cycles;	/* 0x14 - ??? */
	u8	cpu_statlat;		/* 0x15 - ??? */
	u8	cpu_snooplat;		/* 0x16 - ??? */
	u8	cpu_snoopacc;		/* 0x17 - ??? */
	u8	nb_paamwin;		/* 0x18 - ??? */
	u8	nb_statlat;		/* 0x19 - ??? */
	u8	nb_snooplat;		/* 0x1a - ??? */
	u8	nb_snoopwin;		/* 0x1b - ??? */
	u8	api_bus_mode;		/* 0x1c - ??? */
	u8	reserved2[3];		/* 0x1d - */
	u32	input_clk_freq_low;	/* 0x20 - Input घड़ी frequency low */
	u8	processor_card_slot;	/* 0x24 - Processor card slot number */
	u8	reserved3[2];		/* 0x25 - */
	u8	padjmax;       		/* 0x27 - Max घातer adjusपंचांगent (Not in OF!) */
	u8	ttarget;		/* 0x28 - Target temperature */
	u8	पंचांगax;			/* 0x29 - Max temperature */
	u8	pmaxh;			/* 0x2a - Max घातer */
	u8	tguardband;		/* 0x2b - Guardband temp ??? Hist. len in OSX */
	fs32	pid_gp;			/* 0x2c - PID proportional gain */
	fs32	pid_gr;			/* 0x30 - PID reset gain */
	fs32	pid_gd;			/* 0x34 - PID derivative gain */
	fu16	voph;			/* 0x38 - Vop High */
	fu16	vopl;			/* 0x3a - Vop Low */
	fs16	nactual_die;		/* 0x3c - nActual Die */
	fs16	nactual_heatsink;	/* 0x3e - nActual Heatsink */
	fs16	nactual_प्रणाली;		/* 0x40 - nActual System */
	u16	calibration_flags;	/* 0x42 - Calibration flags */
	fu16	mdiode;			/* 0x44 - Diode M value (scaling factor) */
	fs16	bdiode;			/* 0x46 - Diode B value (offset) */
	fs32	theta_heat_sink;	/* 0x48 - Theta heat sink */
	u16	rminn_पूर्णांकake_fan;	/* 0x4c - Intake fan min RPM */
	u16	rmaxn_पूर्णांकake_fan;	/* 0x4e - Intake fan max RPM */
	u16	rminn_exhaust_fan;	/* 0x50 - Exhaust fan min RPM */
	u16	rmaxn_exhaust_fan;	/* 0x52 - Exhaust fan max RPM */
	u8	processor_part_num[8];	/* 0x54 - Processor part number XX pumps min/max */
	u32	processor_lot_num;	/* 0x5c - Processor lot number */
	u8	orig_card_sernum[0x10];	/* 0x60 - Card original serial number */
	u8	curr_card_sernum[0x10];	/* 0x70 - Card current serial number */
	u8	mlb_sernum[0x18];	/* 0x80 - MLB serial number */
	u32	checksum1;		/* 0x98 - */
	u32	checksum2;		/* 0x9c - */	
पूर्ण; /* Total size = 0xa0 */

अटल अंतरभूत स्थिर काष्ठा mpu_data *wf_get_mpu(पूर्णांक cpu)
अणु
	काष्ठा device_node *np;
	अक्षर nodename[64];
	स्थिर व्योम *data;
	पूर्णांक len;

	/*
	 * prom.c routine क्रम finding a node by path is a bit brain dead
	 * and requires exact @xxx unit numbers. This is a bit ugly but
	 * will work क्रम these machines
	 */
	प्र_लिखो(nodename, "/u3@0,f8000000/i2c@f8001000/cpuid@a%d", cpu ? 2 : 0);
	np = of_find_node_by_path(nodename);
	अगर (!np)
		वापस शून्य;
	data = of_get_property(np, "cpuid", &len);	
	of_node_put(np);
	अगर (!data)
		वापस शून्य;

	/*
	 * We are naughty, we have dropped the reference to the device
	 * node and still वापस a poपूर्णांकer to the content. We know we
	 * can करो that though as this is only ever called on PowerMac
	 * which cannot हटाओ those nodes
	 */
	वापस data;
पूर्ण

#पूर्ण_अगर /*  __WINDFARM_MPU_H */
