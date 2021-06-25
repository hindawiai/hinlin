<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * I/O delay strategies क्रम inb_p/outb_p
 *
 * Allow क्रम a DMI based override of port 0x80, needed क्रम certain HP laptops
 * and possibly other प्रणालीs. Also allow क्रम the gradual elimination of
 * outb_p/inb_p API uses.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/dmi.h>
#समावेश <linux/पन.स>

#घोषणा IO_DELAY_TYPE_0X80	0
#घोषणा IO_DELAY_TYPE_0XED	1
#घोषणा IO_DELAY_TYPE_UDELAY	2
#घोषणा IO_DELAY_TYPE_NONE	3

#अगर defined(CONFIG_IO_DELAY_0X80)
#घोषणा DEFAULT_IO_DELAY_TYPE	IO_DELAY_TYPE_0X80
#या_अगर defined(CONFIG_IO_DELAY_0XED)
#घोषणा DEFAULT_IO_DELAY_TYPE	IO_DELAY_TYPE_0XED
#या_अगर defined(CONFIG_IO_DELAY_UDELAY)
#घोषणा DEFAULT_IO_DELAY_TYPE	IO_DELAY_TYPE_UDELAY
#या_अगर defined(CONFIG_IO_DELAY_NONE)
#घोषणा DEFAULT_IO_DELAY_TYPE	IO_DELAY_TYPE_NONE
#पूर्ण_अगर

पूर्णांक io_delay_type __पढ़ो_mostly = DEFAULT_IO_DELAY_TYPE;

अटल पूर्णांक __initdata io_delay_override;

/*
 * Paravirt wants native_io_delay to be a स्थिरant.
 */
व्योम native_io_delay(व्योम)
अणु
	चयन (io_delay_type) अणु
	शेष:
	हाल IO_DELAY_TYPE_0X80:
		यंत्र अस्थिर ("outb %al, $0x80");
		अवरोध;
	हाल IO_DELAY_TYPE_0XED:
		यंत्र अस्थिर ("outb %al, $0xed");
		अवरोध;
	हाल IO_DELAY_TYPE_UDELAY:
		/*
		 * 2 usecs is an upper-bound क्रम the outb delay but
		 * note that udelay करोesn't have the bus-level
		 * side-effects that outb करोes, nor करोes udelay() have
		 * precise timings during very early bootup (the delays
		 * are लघुer until calibrated):
		 */
		udelay(2);
		अवरोध;
	हाल IO_DELAY_TYPE_NONE:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(native_io_delay);

अटल पूर्णांक __init dmi_io_delay_0xed_port(स्थिर काष्ठा dmi_प्रणाली_id *id)
अणु
	अगर (io_delay_type == IO_DELAY_TYPE_0X80) अणु
		pr_notice("%s: using 0xed I/O delay port\n", id->ident);
		io_delay_type = IO_DELAY_TYPE_0XED;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Quirk table क्रम प्रणालीs that misbehave (lock up, etc.) अगर port
 * 0x80 is used:
 */
अटल स्थिर काष्ठा dmi_प्रणाली_id io_delay_0xed_port_dmi_table[] __initस्थिर = अणु
	अणु
		.callback	= dmi_io_delay_0xed_port,
		.ident		= "Compaq Presario V6000",
		.matches	= अणु
			DMI_MATCH(DMI_BOARD_VENDOR,	"Quanta"),
			DMI_MATCH(DMI_BOARD_NAME,	"30B7")
		पूर्ण
	पूर्ण,
	अणु
		.callback	= dmi_io_delay_0xed_port,
		.ident		= "HP Pavilion dv9000z",
		.matches	= अणु
			DMI_MATCH(DMI_BOARD_VENDOR,	"Quanta"),
			DMI_MATCH(DMI_BOARD_NAME,	"30B9")
		पूर्ण
	पूर्ण,
	अणु
		.callback	= dmi_io_delay_0xed_port,
		.ident		= "HP Pavilion dv6000",
		.matches	= अणु
			DMI_MATCH(DMI_BOARD_VENDOR,	"Quanta"),
			DMI_MATCH(DMI_BOARD_NAME,	"30B8")
		पूर्ण
	पूर्ण,
	अणु
		.callback	= dmi_io_delay_0xed_port,
		.ident		= "HP Pavilion tx1000",
		.matches	= अणु
			DMI_MATCH(DMI_BOARD_VENDOR,	"Quanta"),
			DMI_MATCH(DMI_BOARD_NAME,	"30BF")
		पूर्ण
	पूर्ण,
	अणु
		.callback	= dmi_io_delay_0xed_port,
		.ident		= "Presario F700",
		.matches	= अणु
			DMI_MATCH(DMI_BOARD_VENDOR,	"Quanta"),
			DMI_MATCH(DMI_BOARD_NAME,	"30D3")
		पूर्ण
	पूर्ण,
	अणु पूर्ण
पूर्ण;

व्योम __init io_delay_init(व्योम)
अणु
	अगर (!io_delay_override)
		dmi_check_प्रणाली(io_delay_0xed_port_dmi_table);
पूर्ण

अटल पूर्णांक __init io_delay_param(अक्षर *s)
अणु
	अगर (!s)
		वापस -EINVAL;

	अगर (!म_भेद(s, "0x80"))
		io_delay_type = IO_DELAY_TYPE_0X80;
	अन्यथा अगर (!म_भेद(s, "0xed"))
		io_delay_type = IO_DELAY_TYPE_0XED;
	अन्यथा अगर (!म_भेद(s, "udelay"))
		io_delay_type = IO_DELAY_TYPE_UDELAY;
	अन्यथा अगर (!म_भेद(s, "none"))
		io_delay_type = IO_DELAY_TYPE_NONE;
	अन्यथा
		वापस -EINVAL;

	io_delay_override = 1;
	वापस 0;
पूर्ण

early_param("io_delay", io_delay_param);
