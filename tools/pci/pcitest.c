<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/**
 * Userspace PCI Endpoपूर्णांक Test Module
 *
 * Copyright (C) 2017 Texas Instruments
 * Author: Kishon Vijay Abraham I <kishon@ti.com>
 */

#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <sys/ioctl.h>
#समावेश <unistd.h>

#समावेश <linux/pcitest.h>

#घोषणा BILLION 1E9

अटल अक्षर *result[] = अणु "NOT OKAY", "OKAY" पूर्ण;
अटल अक्षर *irq[] = अणु "LEGACY", "MSI", "MSI-X" पूर्ण;

काष्ठा pci_test अणु
	अक्षर		*device;
	अक्षर		barnum;
	bool		legacyirq;
	अचिन्हित पूर्णांक	msinum;
	अचिन्हित पूर्णांक	msixnum;
	पूर्णांक		irqtype;
	bool		set_irqtype;
	bool		get_irqtype;
	bool		clear_irq;
	bool		पढ़ो;
	bool		ग_लिखो;
	bool		copy;
	अचिन्हित दीर्घ	size;
	bool		use_dma;
पूर्ण;

अटल पूर्णांक run_test(काष्ठा pci_test *test)
अणु
	काष्ठा pci_endpoपूर्णांक_test_xfer_param param;
	पूर्णांक ret = -EINVAL;
	पूर्णांक fd;

	fd = खोलो(test->device, O_RDWR);
	अगर (fd < 0) अणु
		लिखो_त्रुटि("can't open PCI Endpoint Test device");
		वापस -ENODEV;
	पूर्ण

	अगर (test->barnum >= 0 && test->barnum <= 5) अणु
		ret = ioctl(fd, PCITEST_BAR, test->barnum);
		ख_लिखो(मानक_निकास, "BAR%d:\t\t", test->barnum);
		अगर (ret < 0)
			ख_लिखो(मानक_निकास, "TEST FAILED\n");
		अन्यथा
			ख_लिखो(मानक_निकास, "%s\n", result[ret]);
	पूर्ण

	अगर (test->set_irqtype) अणु
		ret = ioctl(fd, PCITEST_SET_IRQTYPE, test->irqtype);
		ख_लिखो(मानक_निकास, "SET IRQ TYPE TO %s:\t\t", irq[test->irqtype]);
		अगर (ret < 0)
			ख_लिखो(मानक_निकास, "FAILED\n");
		अन्यथा
			ख_लिखो(मानक_निकास, "%s\n", result[ret]);
	पूर्ण

	अगर (test->get_irqtype) अणु
		ret = ioctl(fd, PCITEST_GET_IRQTYPE);
		ख_लिखो(मानक_निकास, "GET IRQ TYPE:\t\t");
		अगर (ret < 0)
			ख_लिखो(मानक_निकास, "FAILED\n");
		अन्यथा
			ख_लिखो(मानक_निकास, "%s\n", irq[ret]);
	पूर्ण

	अगर (test->clear_irq) अणु
		ret = ioctl(fd, PCITEST_CLEAR_IRQ);
		ख_लिखो(मानक_निकास, "CLEAR IRQ:\t\t");
		अगर (ret < 0)
			ख_लिखो(मानक_निकास, "FAILED\n");
		अन्यथा
			ख_लिखो(मानक_निकास, "%s\n", result[ret]);
	पूर्ण

	अगर (test->legacyirq) अणु
		ret = ioctl(fd, PCITEST_LEGACY_IRQ, 0);
		ख_लिखो(मानक_निकास, "LEGACY IRQ:\t");
		अगर (ret < 0)
			ख_लिखो(मानक_निकास, "TEST FAILED\n");
		अन्यथा
			ख_लिखो(मानक_निकास, "%s\n", result[ret]);
	पूर्ण

	अगर (test->msinum > 0 && test->msinum <= 32) अणु
		ret = ioctl(fd, PCITEST_MSI, test->msinum);
		ख_लिखो(मानक_निकास, "MSI%d:\t\t", test->msinum);
		अगर (ret < 0)
			ख_लिखो(मानक_निकास, "TEST FAILED\n");
		अन्यथा
			ख_लिखो(मानक_निकास, "%s\n", result[ret]);
	पूर्ण

	अगर (test->msixnum > 0 && test->msixnum <= 2048) अणु
		ret = ioctl(fd, PCITEST_MSIX, test->msixnum);
		ख_लिखो(मानक_निकास, "MSI-X%d:\t\t", test->msixnum);
		अगर (ret < 0)
			ख_लिखो(मानक_निकास, "TEST FAILED\n");
		अन्यथा
			ख_लिखो(मानक_निकास, "%s\n", result[ret]);
	पूर्ण

	अगर (test->ग_लिखो) अणु
		param.size = test->size;
		अगर (test->use_dma)
			param.flags = PCITEST_FLAGS_USE_DMA;
		ret = ioctl(fd, PCITEST_WRITE, &param);
		ख_लिखो(मानक_निकास, "WRITE (%7ld bytes):\t\t", test->size);
		अगर (ret < 0)
			ख_लिखो(मानक_निकास, "TEST FAILED\n");
		अन्यथा
			ख_लिखो(मानक_निकास, "%s\n", result[ret]);
	पूर्ण

	अगर (test->पढ़ो) अणु
		param.size = test->size;
		अगर (test->use_dma)
			param.flags = PCITEST_FLAGS_USE_DMA;
		ret = ioctl(fd, PCITEST_READ, &param);
		ख_लिखो(मानक_निकास, "READ (%7ld bytes):\t\t", test->size);
		अगर (ret < 0)
			ख_लिखो(मानक_निकास, "TEST FAILED\n");
		अन्यथा
			ख_लिखो(मानक_निकास, "%s\n", result[ret]);
	पूर्ण

	अगर (test->copy) अणु
		param.size = test->size;
		अगर (test->use_dma)
			param.flags = PCITEST_FLAGS_USE_DMA;
		ret = ioctl(fd, PCITEST_COPY, &param);
		ख_लिखो(मानक_निकास, "COPY (%7ld bytes):\t\t", test->size);
		अगर (ret < 0)
			ख_लिखो(मानक_निकास, "TEST FAILED\n");
		अन्यथा
			ख_लिखो(मानक_निकास, "%s\n", result[ret]);
	पूर्ण

	ख_साफ(मानक_निकास);
	बंद(fd);
	वापस (ret < 0) ? ret : 1 - ret; /* वापस 0 अगर test succeeded */
पूर्ण

पूर्णांक मुख्य(पूर्णांक argc, अक्षर **argv)
अणु
	पूर्णांक c;
	काष्ठा pci_test *test;

	test = सुस्मृति(1, माप(*test));
	अगर (!test) अणु
		लिखो_त्रुटि("Fail to allocate memory for pci_test\n");
		वापस -ENOMEM;
	पूर्ण

	/* since '0' is a valid BAR number, initialize it to -1 */
	test->barnum = -1;

	/* set शेष size as 100KB */
	test->size = 0x19000;

	/* set शेष endpoपूर्णांक device */
	test->device = "/dev/pci-endpoint-test.0";

	जबतक ((c = getopt(argc, argv, "D:b:m:x:i:deIlhrwcs:")) != खातापूर्ण)
	चयन (c) अणु
	हाल 'D':
		test->device = optarg;
		जारी;
	हाल 'b':
		test->barnum = म_से_प(optarg);
		अगर (test->barnum < 0 || test->barnum > 5)
			जाओ usage;
		जारी;
	हाल 'l':
		test->legacyirq = true;
		जारी;
	हाल 'm':
		test->msinum = म_से_प(optarg);
		अगर (test->msinum < 1 || test->msinum > 32)
			जाओ usage;
		जारी;
	हाल 'x':
		test->msixnum = म_से_प(optarg);
		अगर (test->msixnum < 1 || test->msixnum > 2048)
			जाओ usage;
		जारी;
	हाल 'i':
		test->irqtype = म_से_प(optarg);
		अगर (test->irqtype < 0 || test->irqtype > 2)
			जाओ usage;
		test->set_irqtype = true;
		जारी;
	हाल 'I':
		test->get_irqtype = true;
		जारी;
	हाल 'r':
		test->पढ़ो = true;
		जारी;
	हाल 'w':
		test->ग_लिखो = true;
		जारी;
	हाल 'c':
		test->copy = true;
		जारी;
	हाल 'e':
		test->clear_irq = true;
		जारी;
	हाल 's':
		test->size = म_से_अदीर्घ(optarg, शून्य, 0);
		जारी;
	हाल 'd':
		test->use_dma = true;
		जारी;
	हाल 'h':
	शेष:
usage:
		ख_लिखो(मानक_त्रुटि,
			"usage: %s [options]\n"
			"Options:\n"
			"\t-D <dev>		PCI endpoint test device {default: /dev/pci-endpoint-test.0}\n"
			"\t-b <bar num>		BAR test (bar number between 0..5)\n"
			"\t-m <msi num>		MSI test (msi number between 1..32)\n"
			"\t-x <msix num>	\tMSI-X test (msix number between 1..2048)\n"
			"\t-i <irq type>	\tSet IRQ type (0 - Legacy, 1 - MSI, 2 - MSI-X)\n"
			"\t-e			Clear IRQ\n"
			"\t-I			Get current IRQ type configured\n"
			"\t-d			Use DMA\n"
			"\t-l			Legacy IRQ test\n"
			"\t-r			Read buffer test\n"
			"\t-w			Write buffer test\n"
			"\t-c			Copy buffer test\n"
			"\t-s <size>		Size of buffer {default: 100KB}\n"
			"\t-h			Print this help message\n",
			argv[0]);
		वापस -EINVAL;
	पूर्ण

	वापस run_test(test);
पूर्ण
