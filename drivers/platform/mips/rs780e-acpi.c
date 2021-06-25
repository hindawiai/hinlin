<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/export.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

अटल अचिन्हित दीर्घ acpi_iobase;

#घोषणा ACPI_PM_EVT_BLK         (acpi_iobase + 0x00) /* 4 bytes */
#घोषणा ACPI_PM_CNT_BLK         (acpi_iobase + 0x04) /* 2 bytes */
#घोषणा ACPI_PMA_CNT_BLK        (acpi_iobase + 0x0F) /* 1 byte */
#घोषणा ACPI_PM_TMR_BLK         (acpi_iobase + 0x18) /* 4 bytes */
#घोषणा ACPI_GPE0_BLK           (acpi_iobase + 0x10) /* 8 bytes */
#घोषणा ACPI_END                (acpi_iobase + 0x80)

#घोषणा PM_INDEX        0xCD6
#घोषणा PM_DATA         0xCD7
#घोषणा PM2_INDEX       0xCD0
#घोषणा PM2_DATA        0xCD1

अटल व्योम pmio_ग_लिखो_index(u16 index, u8 reg, u8 value)
अणु
	outb(reg, index);
	outb(value, index + 1);
पूर्ण

अटल u8 pmio_पढ़ो_index(u16 index, u8 reg)
अणु
	outb(reg, index);
	वापस inb(index + 1);
पूर्ण

व्योम pm_ioग_लिखो(u8 reg, u8 value)
अणु
	pmio_ग_लिखो_index(PM_INDEX, reg, value);
पूर्ण
EXPORT_SYMBOL(pm_ioग_लिखो);

u8 pm_ioपढ़ो(u8 reg)
अणु
	वापस pmio_पढ़ो_index(PM_INDEX, reg);
पूर्ण
EXPORT_SYMBOL(pm_ioपढ़ो);

व्योम pm2_ioग_लिखो(u8 reg, u8 value)
अणु
	pmio_ग_लिखो_index(PM2_INDEX, reg, value);
पूर्ण
EXPORT_SYMBOL(pm2_ioग_लिखो);

u8 pm2_ioपढ़ो(u8 reg)
अणु
	वापस pmio_पढ़ो_index(PM2_INDEX, reg);
पूर्ण
EXPORT_SYMBOL(pm2_ioपढ़ो);

अटल व्योम acpi_hw_clear_status(व्योम)
अणु
	u16 value;

	/* PMStatus: Clear WakeStatus/PwrBtnStatus */
	value = inw(ACPI_PM_EVT_BLK);
	value |= (1 << 8 | 1 << 15);
	outw(value, ACPI_PM_EVT_BLK);

	/* GPEStatus: Clear all generated events */
	outl(inl(ACPI_GPE0_BLK), ACPI_GPE0_BLK);
पूर्ण

अटल व्योम acpi_रेजिस्टरs_setup(व्योम)
अणु
	u32 value;

	/* PM Status Base */
	pm_ioग_लिखो(0x20, ACPI_PM_EVT_BLK & 0xff);
	pm_ioग_लिखो(0x21, ACPI_PM_EVT_BLK >> 8);

	/* PM Control Base */
	pm_ioग_लिखो(0x22, ACPI_PM_CNT_BLK & 0xff);
	pm_ioग_लिखो(0x23, ACPI_PM_CNT_BLK >> 8);

	/* GPM Base */
	pm_ioग_लिखो(0x28, ACPI_GPE0_BLK & 0xff);
	pm_ioग_लिखो(0x29, ACPI_GPE0_BLK >> 8);

	/* ACPI End */
	pm_ioग_लिखो(0x2e, ACPI_END & 0xff);
	pm_ioग_लिखो(0x2f, ACPI_END >> 8);

	/* IO Decode: When AcpiDecodeEnable set, South-Bridge uses the contents
	 * of the PM रेजिस्टरs at index 0x20~0x2B to decode ACPI I/O address. */
	pm_ioग_लिखो(0x0e, 1 << 3);

	/* SCI_EN set */
	outw(1, ACPI_PM_CNT_BLK);

	/* Enable to generate SCI */
	pm_ioग_लिखो(0x10, pm_ioपढ़ो(0x10) | 1);

	/* GPM3/GPM9 enable */
	value = inl(ACPI_GPE0_BLK + 4);
	outl(value | (1 << 14) | (1 << 22), ACPI_GPE0_BLK + 4);

	/* Set GPM9 as input */
	pm_ioग_लिखो(0x8d, pm_ioपढ़ो(0x8d) & (~(1 << 1)));

	/* Set GPM9 as non-output */
	pm_ioग_लिखो(0x94, pm_ioपढ़ो(0x94) | (1 << 3));

	/* GPM3 config ACPI trigger SCIOUT */
	pm_ioग_लिखो(0x33, pm_ioपढ़ो(0x33) & (~(3 << 4)));

	/* GPM9 config ACPI trigger SCIOUT */
	pm_ioग_लिखो(0x3d, pm_ioपढ़ो(0x3d) & (~(3 << 2)));

	/* GPM3 config falling edge trigger */
	pm_ioग_लिखो(0x37, pm_ioपढ़ो(0x37) & (~(1 << 6)));

	/* No रुको क्रम STPGNT# in ACPI Sx state */
	pm_ioग_लिखो(0x7c, pm_ioपढ़ो(0x7c) | (1 << 6));

	/* Set GPM3 pull-करोwn enable */
	value = pm2_ioपढ़ो(0xf6);
	value |= ((1 << 7) | (1 << 3));
	pm2_ioग_लिखो(0xf6, value);

	/* Set GPM9 pull-करोwn enable */
	value = pm2_ioपढ़ो(0xf8);
	value |= ((1 << 5) | (1 << 1));
	pm2_ioग_लिखो(0xf8, value);
पूर्ण

अटल पूर्णांक rs780e_acpi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!res)
		वापस -ENODEV;

	/* SCI पूर्णांकerrupt need acpi space, allocate here */
	अगर (!request_region(res->start, resource_size(res), "acpi")) अणु
		pr_err("RS780E-ACPI: Failed to request IO Region\n");
		वापस -EBUSY;
	पूर्ण

	acpi_iobase = res->start;

	acpi_रेजिस्टरs_setup();
	acpi_hw_clear_status();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rs780e_acpi_match[] = अणु
	अणु .compatible = "loongson,rs780e-acpi" पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver rs780e_acpi_driver = अणु
	.probe = rs780e_acpi_probe,
	.driver = अणु
		.name = "RS780E-ACPI",
		.of_match_table = rs780e_acpi_match,
	पूर्ण,
पूर्ण;
builtin_platक्रमm_driver(rs780e_acpi_driver);
