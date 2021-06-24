<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * comedi_8254.h
 * Generic 8254 समयr/counter support
 * Copyright (C) 2014 H Hartley Sweeten <hsweeten@visionengravers.com>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

#अगर_अघोषित _COMEDI_8254_H
#घोषणा _COMEDI_8254_H

#समावेश <linux/types.h>

काष्ठा comedi_device;
काष्ठा comedi_insn;
काष्ठा comedi_subdevice;

/*
 * Common oscillator base values in nanoseconds
 */
#घोषणा I8254_OSC_BASE_10MHZ	100
#घोषणा I8254_OSC_BASE_5MHZ	200
#घोषणा I8254_OSC_BASE_4MHZ	250
#घोषणा I8254_OSC_BASE_2MHZ	500
#घोषणा I8254_OSC_BASE_1MHZ	1000
#घोषणा I8254_OSC_BASE_100KHZ	10000
#घोषणा I8254_OSC_BASE_10KHZ	100000
#घोषणा I8254_OSC_BASE_1KHZ	1000000

/*
 * I/O access size used to पढ़ो/ग_लिखो रेजिस्टरs
 */
#घोषणा I8254_IO8		1
#घोषणा I8254_IO16		2
#घोषणा I8254_IO32		4

/*
 * Register map क्रम generic 8254 समयr (I8254_IO8 with 0 regshअगरt)
 */
#घोषणा I8254_COUNTER0_REG		0x00
#घोषणा I8254_COUNTER1_REG		0x01
#घोषणा I8254_COUNTER2_REG		0x02
#घोषणा I8254_CTRL_REG			0x03
#घोषणा I8254_CTRL_SEL_CTR(x)		((x) << 6)
#घोषणा I8254_CTRL_READBACK(x)		(I8254_CTRL_SEL_CTR(3) | BIT(x))
#घोषणा I8254_CTRL_READBACK_COUNT	I8254_CTRL_READBACK(4)
#घोषणा I8254_CTRL_READBACK_STATUS	I8254_CTRL_READBACK(5)
#घोषणा I8254_CTRL_READBACK_SEL_CTR(x)	(2 << (x))
#घोषणा I8254_CTRL_RW(x)		(((x) & 0x3) << 4)
#घोषणा I8254_CTRL_LATCH		I8254_CTRL_RW(0)
#घोषणा I8254_CTRL_LSB_ONLY		I8254_CTRL_RW(1)
#घोषणा I8254_CTRL_MSB_ONLY		I8254_CTRL_RW(2)
#घोषणा I8254_CTRL_LSB_MSB		I8254_CTRL_RW(3)

/* counter maps zero to 0x10000 */
#घोषणा I8254_MAX_COUNT			0x10000

/**
 * काष्ठा comedi_8254 - निजी data used by this module
 * @iobase:		PIO base address of the रेजिस्टरs (in/out)
 * @mmio:		MMIO base address of the रेजिस्टरs (पढ़ो/ग_लिखो)
 * @iosize:		I/O size used to access the रेजिस्टरs (b/w/l)
 * @regshअगरt:		रेजिस्टर gap shअगरt
 * @osc_base:		cascaded oscillator speed in ns
 * @भागisor:		भागisor क्रम single counter
 * @भागisor1:		भागisor loaded पूर्णांकo first cascaded counter
 * @भागisor2:		भागisor loaded पूर्णांकo second cascaded counter
 * #next_भाग:		next भागisor क्रम single counter
 * @next_भाग1:		next भागisor to use क्रम first cascaded counter
 * @next_भाग2:		next भागisor to use क्रम second cascaded counter
 * @घड़ी_src;		current घड़ी source क्रम each counter (driver specअगरic)
 * @gate_src;		current gate source  क्रम each counter (driver specअगरic)
 * @busy:		flags used to indicate that a counter is "busy"
 * @insn_config:	driver specअगरic (*insn_config) callback
 */
काष्ठा comedi_8254 अणु
	अचिन्हित दीर्घ iobase;
	व्योम __iomem *mmio;
	अचिन्हित पूर्णांक iosize;
	अचिन्हित पूर्णांक regshअगरt;
	अचिन्हित पूर्णांक osc_base;
	अचिन्हित पूर्णांक भागisor;
	अचिन्हित पूर्णांक भागisor1;
	अचिन्हित पूर्णांक भागisor2;
	अचिन्हित पूर्णांक next_भाग;
	अचिन्हित पूर्णांक next_भाग1;
	अचिन्हित पूर्णांक next_भाग2;
	अचिन्हित पूर्णांक घड़ी_src[3];
	अचिन्हित पूर्णांक gate_src[3];
	bool busy[3];

	पूर्णांक (*insn_config)(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data);
पूर्ण;

अचिन्हित पूर्णांक comedi_8254_status(काष्ठा comedi_8254 *i8254,
				अचिन्हित पूर्णांक counter);
अचिन्हित पूर्णांक comedi_8254_पढ़ो(काष्ठा comedi_8254 *i8254, अचिन्हित पूर्णांक counter);
व्योम comedi_8254_ग_लिखो(काष्ठा comedi_8254 *i8254,
		       अचिन्हित पूर्णांक counter, अचिन्हित पूर्णांक val);

पूर्णांक comedi_8254_set_mode(काष्ठा comedi_8254 *i8254,
			 अचिन्हित पूर्णांक counter, अचिन्हित पूर्णांक mode);
पूर्णांक comedi_8254_load(काष्ठा comedi_8254 *i8254,
		     अचिन्हित पूर्णांक counter, अचिन्हित पूर्णांक val, अचिन्हित पूर्णांक mode);

व्योम comedi_8254_pacer_enable(काष्ठा comedi_8254 *i8254,
			      अचिन्हित पूर्णांक counter1, अचिन्हित पूर्णांक counter2,
			      bool enable);
व्योम comedi_8254_update_भागisors(काष्ठा comedi_8254 *i8254);
व्योम comedi_8254_cascade_ns_to_समयr(काष्ठा comedi_8254 *i8254,
				     अचिन्हित पूर्णांक *nanosec, अचिन्हित पूर्णांक flags);
व्योम comedi_8254_ns_to_समयr(काष्ठा comedi_8254 *i8254,
			     अचिन्हित पूर्णांक *nanosec, अचिन्हित पूर्णांक flags);

व्योम comedi_8254_set_busy(काष्ठा comedi_8254 *i8254,
			  अचिन्हित पूर्णांक counter, bool busy);

व्योम comedi_8254_subdevice_init(काष्ठा comedi_subdevice *s,
				काष्ठा comedi_8254 *i8254);

काष्ठा comedi_8254 *comedi_8254_init(अचिन्हित दीर्घ iobase,
				     अचिन्हित पूर्णांक osc_base,
				     अचिन्हित पूर्णांक iosize,
				     अचिन्हित पूर्णांक regshअगरt);
काष्ठा comedi_8254 *comedi_8254_mm_init(व्योम __iomem *mmio,
					अचिन्हित पूर्णांक osc_base,
					अचिन्हित पूर्णांक iosize,
					अचिन्हित पूर्णांक regshअगरt);

#पूर्ण_अगर	/* _COMEDI_8254_H */
