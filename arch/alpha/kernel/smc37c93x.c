<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SMC 37C93X initialization code
 */

#समावेश <linux/kernel.h>

#समावेश <linux/mm.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/hwrpb.h>
#समावेश <यंत्र/पन.स>

#घोषणा SMC_DEBUG 0

#अगर SMC_DEBUG
# define DBG_DEVS(args)         prपूर्णांकk args
#अन्यथा
# define DBG_DEVS(args)
#पूर्ण_अगर

#घोषणा KB              1024
#घोषणा MB              (1024*KB)
#घोषणा GB              (1024*MB)

/* device "activate" रेजिस्टर contents */
#घोषणा DEVICE_ON		1
#घोषणा DEVICE_OFF		0

/* configuration on/off keys */
#घोषणा CONFIG_ON_KEY		0x55
#घोषणा CONFIG_OFF_KEY		0xaa

/* configuration space device definitions */
#घोषणा FDC			0
#घोषणा IDE1			1
#घोषणा IDE2			2
#घोषणा PARP			3
#घोषणा SER1			4
#घोषणा SER2			5
#घोषणा RTCL			6
#घोषणा KYBD			7
#घोषणा AUXIO			8

/* Chip रेजिस्टर offsets from base */
#घोषणा CONFIG_CONTROL		0x02
#घोषणा INDEX_ADDRESS		0x03
#घोषणा LOGICAL_DEVICE_NUMBER	0x07
#घोषणा DEVICE_ID		0x20
#घोषणा DEVICE_REV		0x21
#घोषणा POWER_CONTROL		0x22
#घोषणा POWER_MGMT		0x23
#घोषणा OSC			0x24

#घोषणा ACTIVATE		0x30
#घोषणा ADDR_HI			0x60
#घोषणा ADDR_LO			0x61
#घोषणा INTERRUPT_SEL		0x70
#घोषणा INTERRUPT_SEL_2		0x72 /* KYBD/MOUS only */
#घोषणा DMA_CHANNEL_SEL		0x74 /* FDC/PARP only */

#घोषणा FDD_MODE_REGISTER	0x90
#घोषणा FDD_OPTION_REGISTER	0x91

/* values that we पढ़ो back that are expected ... */
#घोषणा VALID_DEVICE_ID		2

/* शेष device addresses */
#घोषणा KYBD_INTERRUPT		1
#घोषणा MOUS_INTERRUPT		12
#घोषणा COM2_BASE		0x2f8
#घोषणा COM2_INTERRUPT		3
#घोषणा COM1_BASE		0x3f8
#घोषणा COM1_INTERRUPT		4
#घोषणा PARP_BASE		0x3bc
#घोषणा PARP_INTERRUPT		7

अटल अचिन्हित दीर्घ __init SMCConfigState(अचिन्हित दीर्घ baseAddr)
अणु
	अचिन्हित अक्षर devId;

	अचिन्हित दीर्घ configPort;
	अचिन्हित दीर्घ indexPort;
	अचिन्हित दीर्घ dataPort;

	पूर्णांक i;

	configPort = indexPort = baseAddr;
	dataPort = configPort + 1;

#घोषणा NUM_RETRIES 5

	क्रम (i = 0; i < NUM_RETRIES; i++)
	अणु
		outb(CONFIG_ON_KEY, configPort);
		outb(CONFIG_ON_KEY, configPort);
		outb(DEVICE_ID, indexPort);
		devId = inb(dataPort);
		अगर (devId == VALID_DEVICE_ID) अणु
			outb(DEVICE_REV, indexPort);
			/* अचिन्हित अक्षर devRev = */ inb(dataPort);
			अवरोध;
		पूर्ण
		अन्यथा
			udelay(100);
	पूर्ण
	वापस (i != NUM_RETRIES) ? baseAddr : 0L;
पूर्ण

अटल व्योम __init SMCRunState(अचिन्हित दीर्घ baseAddr)
अणु
	outb(CONFIG_OFF_KEY, baseAddr);
पूर्ण

अटल अचिन्हित दीर्घ __init SMCDetectUltraIO(व्योम)
अणु
	अचिन्हित दीर्घ baseAddr;

	baseAddr = 0x3F0;
	अगर ( ( baseAddr = SMCConfigState( baseAddr ) ) == 0x3F0 ) अणु
		वापस( baseAddr );
	पूर्ण
	baseAddr = 0x370;
	अगर ( ( baseAddr = SMCConfigState( baseAddr ) ) == 0x370 ) अणु
		वापस( baseAddr );
	पूर्ण
	वापस( ( अचिन्हित दीर्घ )0 );
पूर्ण

अटल व्योम __init SMCEnableDevice(अचिन्हित दीर्घ baseAddr,
			    अचिन्हित दीर्घ device,
			    अचिन्हित दीर्घ portaddr,
			    अचिन्हित दीर्घ पूर्णांकerrupt)
अणु
	अचिन्हित दीर्घ indexPort;
	अचिन्हित दीर्घ dataPort;

	indexPort = baseAddr;
	dataPort = baseAddr + 1;

	outb(LOGICAL_DEVICE_NUMBER, indexPort);
	outb(device, dataPort);

	outb(ADDR_LO, indexPort);
	outb(( portaddr & 0xFF ), dataPort);

	outb(ADDR_HI, indexPort);
	outb((portaddr >> 8) & 0xFF, dataPort);

	outb(INTERRUPT_SEL, indexPort);
	outb(पूर्णांकerrupt, dataPort);

	outb(ACTIVATE, indexPort);
	outb(DEVICE_ON, dataPort);
पूर्ण

अटल व्योम __init SMCEnableKYBD(अचिन्हित दीर्घ baseAddr)
अणु
	अचिन्हित दीर्घ indexPort;
	अचिन्हित दीर्घ dataPort;

	indexPort = baseAddr;
	dataPort = baseAddr + 1;

	outb(LOGICAL_DEVICE_NUMBER, indexPort);
	outb(KYBD, dataPort);

	outb(INTERRUPT_SEL, indexPort); /* Primary पूर्णांकerrupt select */
	outb(KYBD_INTERRUPT, dataPort);

	outb(INTERRUPT_SEL_2, indexPort); /* Secondary पूर्णांकerrupt select */
	outb(MOUS_INTERRUPT, dataPort);

	outb(ACTIVATE, indexPort);
	outb(DEVICE_ON, dataPort);
पूर्ण

अटल व्योम __init SMCEnableFDC(अचिन्हित दीर्घ baseAddr)
अणु
	अचिन्हित दीर्घ indexPort;
	अचिन्हित दीर्घ dataPort;

	अचिन्हित अक्षर oldValue;

	indexPort = baseAddr;
	dataPort = baseAddr + 1;

	outb(LOGICAL_DEVICE_NUMBER, indexPort);
	outb(FDC, dataPort);

	outb(FDD_MODE_REGISTER, indexPort);
	oldValue = inb(dataPort);

	oldValue |= 0x0E;                   /* Enable burst mode */
	outb(oldValue, dataPort);

	outb(INTERRUPT_SEL, indexPort);	    /* Primary पूर्णांकerrupt select */
	outb(0x06, dataPort );

	outb(DMA_CHANNEL_SEL, indexPort);   /* DMA channel select */
	outb(0x02, dataPort);

	outb(ACTIVATE, indexPort);
	outb(DEVICE_ON, dataPort);
पूर्ण

#अगर SMC_DEBUG
अटल व्योम __init SMCReportDeviceStatus(अचिन्हित दीर्घ baseAddr)
अणु
	अचिन्हित दीर्घ indexPort;
	अचिन्हित दीर्घ dataPort;
	अचिन्हित अक्षर currentControl;

	indexPort = baseAddr;
	dataPort = baseAddr + 1;

	outb(POWER_CONTROL, indexPort);
	currentControl = inb(dataPort);

	prपूर्णांकk(currentControl & (1 << FDC)
	       ? "\t+FDC Enabled\n" : "\t-FDC Disabled\n");
	prपूर्णांकk(currentControl & (1 << IDE1)
	       ? "\t+IDE1 Enabled\n" : "\t-IDE1 Disabled\n");
	prपूर्णांकk(currentControl & (1 << IDE2)
	       ? "\t+IDE2 Enabled\n" : "\t-IDE2 Disabled\n");
	prपूर्णांकk(currentControl & (1 << PARP)
	       ? "\t+PARP Enabled\n" : "\t-PARP Disabled\n");
	prपूर्णांकk(currentControl & (1 << SER1)
	       ? "\t+SER1 Enabled\n" : "\t-SER1 Disabled\n");
	prपूर्णांकk(currentControl & (1 << SER2)
	       ? "\t+SER2 Enabled\n" : "\t-SER2 Disabled\n");

	prपूर्णांकk( "\n" );
पूर्ण
#पूर्ण_अगर

पूर्णांक __init SMC93x_Init(व्योम)
अणु
	अचिन्हित दीर्घ SMCUltraBase;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	अगर ((SMCUltraBase = SMCDetectUltraIO()) != 0UL) अणु
#अगर SMC_DEBUG
		SMCReportDeviceStatus(SMCUltraBase);
#पूर्ण_अगर
		SMCEnableDevice(SMCUltraBase, SER1, COM1_BASE, COM1_INTERRUPT);
		DBG_DEVS(("SMC FDC37C93X: SER1 done\n"));
		SMCEnableDevice(SMCUltraBase, SER2, COM2_BASE, COM2_INTERRUPT);
		DBG_DEVS(("SMC FDC37C93X: SER2 done\n"));
		SMCEnableDevice(SMCUltraBase, PARP, PARP_BASE, PARP_INTERRUPT);
		DBG_DEVS(("SMC FDC37C93X: PARP done\n"));
		/* On PC164, IDE on the SMC is not enabled;
		   CMD646 (PCI) on MB */
		SMCEnableKYBD(SMCUltraBase);
		DBG_DEVS(("SMC FDC37C93X: KYB done\n"));
		SMCEnableFDC(SMCUltraBase);
		DBG_DEVS(("SMC FDC37C93X: FDC done\n"));
#अगर SMC_DEBUG
		SMCReportDeviceStatus(SMCUltraBase);
#पूर्ण_अगर
		SMCRunState(SMCUltraBase);
		local_irq_restore(flags);
		prपूर्णांकk("SMC FDC37C93X Ultra I/O Controller found @ 0x%lx\n",
		       SMCUltraBase);
		वापस 1;
	पूर्ण
	अन्यथा अणु
		local_irq_restore(flags);
		DBG_DEVS(("No SMC FDC37C93X Ultra I/O Controller found\n"));
		वापस 0;
	पूर्ण
पूर्ण
