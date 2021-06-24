<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Alchemy DB/PB1xxx board support.
 */

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-db1x00/bcsr.h>

पूर्णांक __init db1000_board_setup(व्योम);
पूर्णांक __init db1000_dev_setup(व्योम);
पूर्णांक __init db1500_pci_setup(व्योम);
पूर्णांक __init db1200_board_setup(व्योम);
पूर्णांक __init db1200_dev_setup(व्योम);
पूर्णांक __init db1300_board_setup(व्योम);
पूर्णांक __init db1300_dev_setup(व्योम);
पूर्णांक __init db1550_board_setup(व्योम);
पूर्णांक __init db1550_dev_setup(व्योम);
पूर्णांक __init db1550_pci_setup(पूर्णांक);

अटल स्थिर अक्षर *board_type_str(व्योम)
अणु
	चयन (BCSR_WHOAMI_BOARD(bcsr_पढ़ो(BCSR_WHOAMI))) अणु
	हाल BCSR_WHOAMI_DB1000:
		वापस "DB1000";
	हाल BCSR_WHOAMI_DB1500:
		वापस "DB1500";
	हाल BCSR_WHOAMI_DB1100:
		वापस "DB1100";
	हाल BCSR_WHOAMI_PB1500:
	हाल BCSR_WHOAMI_PB1500R2:
		वापस "PB1500";
	हाल BCSR_WHOAMI_PB1100:
		वापस "PB1100";
	हाल BCSR_WHOAMI_PB1200_DDR1:
	हाल BCSR_WHOAMI_PB1200_DDR2:
		वापस "PB1200";
	हाल BCSR_WHOAMI_DB1200:
		वापस "DB1200";
	हाल BCSR_WHOAMI_DB1300:
		वापस "DB1300";
	हाल BCSR_WHOAMI_DB1550:
		वापस "DB1550";
	हाल BCSR_WHOAMI_PB1550_SDR:
	हाल BCSR_WHOAMI_PB1550_DDR:
		वापस "PB1550";
	शेष:
		वापस "(unknown)";
	पूर्ण
पूर्ण

स्थिर अक्षर *get_प्रणाली_type(व्योम)
अणु
	वापस board_type_str();
पूर्ण

व्योम __init board_setup(व्योम)
अणु
	पूर्णांक ret;

	चयन (alchemy_get_cputype()) अणु
	हाल ALCHEMY_CPU_AU1000:
	हाल ALCHEMY_CPU_AU1500:
	हाल ALCHEMY_CPU_AU1100:
		ret = db1000_board_setup();
		अवरोध;
	हाल ALCHEMY_CPU_AU1550:
		ret = db1550_board_setup();
		अवरोध;
	हाल ALCHEMY_CPU_AU1200:
		ret = db1200_board_setup();
		अवरोध;
	हाल ALCHEMY_CPU_AU1300:
		ret = db1300_board_setup();
		अवरोध;
	शेष:
		pr_err("unsupported CPU on board\n");
		ret = -ENODEV;
	पूर्ण
	अगर (ret)
		panic("cannot initialize board support");
पूर्ण

अटल पूर्णांक __init db1xxx_arch_init(व्योम)
अणु
	पूर्णांक id = BCSR_WHOAMI_BOARD(bcsr_पढ़ो(BCSR_WHOAMI));
	अगर (id == BCSR_WHOAMI_DB1550)
		वापस db1550_pci_setup(0);
	अन्यथा अगर ((id == BCSR_WHOAMI_PB1550_SDR) ||
		 (id == BCSR_WHOAMI_PB1550_DDR))
		वापस db1550_pci_setup(1);
	अन्यथा अगर ((id == BCSR_WHOAMI_DB1500) || (id == BCSR_WHOAMI_PB1500) ||
		 (id == BCSR_WHOAMI_PB1500R2))
		वापस db1500_pci_setup();

	वापस 0;
पूर्ण
arch_initcall(db1xxx_arch_init);

अटल पूर्णांक __init db1xxx_dev_init(व्योम)
अणु
	mips_set_machine_name(board_type_str());
	चयन (BCSR_WHOAMI_BOARD(bcsr_पढ़ो(BCSR_WHOAMI))) अणु
	हाल BCSR_WHOAMI_DB1000:
	हाल BCSR_WHOAMI_DB1500:
	हाल BCSR_WHOAMI_DB1100:
	हाल BCSR_WHOAMI_PB1500:
	हाल BCSR_WHOAMI_PB1500R2:
	हाल BCSR_WHOAMI_PB1100:
		वापस db1000_dev_setup();
	हाल BCSR_WHOAMI_PB1200_DDR1:
	हाल BCSR_WHOAMI_PB1200_DDR2:
	हाल BCSR_WHOAMI_DB1200:
		वापस db1200_dev_setup();
	हाल BCSR_WHOAMI_DB1300:
		वापस db1300_dev_setup();
	हाल BCSR_WHOAMI_DB1550:
	हाल BCSR_WHOAMI_PB1550_SDR:
	हाल BCSR_WHOAMI_PB1550_DDR:
		वापस db1550_dev_setup();
	पूर्ण
	वापस 0;
पूर्ण
device_initcall(db1xxx_dev_init);
