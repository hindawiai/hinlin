<शैली गुरु>
/*
 * 1-wire busmaster driver क्रम DS1WM and ASICs with embedded DS1WMs
 * such as HP iPAQs (including h5xxx, h2200, and devices with ASIC3
 * like hx4700).
 *
 * Copyright (c) 2004-2005, Szabolcs Gyurko <szabolcs.gyurko@tlt.hu>
 * Copyright (c) 2004-2007, Matt Reimer <mreimer@vpop.net>
 *
 * Use consistent with the GNU GPL is permitted,
 * provided that this copyright notice is
 * preserved in its entirety in all copies and derived works.
 */

#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/पन.स>
#समावेश <linux/irq.h>
#समावेश <linux/pm.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/err.h>
#समावेश <linux/delay.h>
#समावेश <linux/mfd/core.h>
#समावेश <linux/mfd/ds1wm.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/पन.स>

#समावेश <linux/w1.h>


#घोषणा DS1WM_CMD	0x00	/* R/W 4 bits command */
#घोषणा DS1WM_DATA	0x01	/* R/W 8 bits, transmit/receive buffer */
#घोषणा DS1WM_INT	0x02	/* R/W पूर्णांकerrupt status */
#घोषणा DS1WM_INT_EN	0x03	/* R/W पूर्णांकerrupt enable */
#घोषणा DS1WM_CLKDIV	0x04	/* R/W 5 bits of भागisor and pre-scale */
#घोषणा DS1WM_CNTRL	0x05	/* R/W master control रेजिस्टर (not used yet) */

#घोषणा DS1WM_CMD_1W_RESET  (1 << 0)	/* क्रमce reset on 1-wire bus */
#घोषणा DS1WM_CMD_SRA	    (1 << 1)	/* enable Search ROM accelerator mode */
#घोषणा DS1WM_CMD_DQ_OUTPUT (1 << 2)	/* ग_लिखो only - क्रमces bus low */
#घोषणा DS1WM_CMD_DQ_INPUT  (1 << 3)	/* पढ़ो only - reflects state of bus */
#घोषणा DS1WM_CMD_RST	    (1 << 5)	/* software reset */
#घोषणा DS1WM_CMD_OD	    (1 << 7)	/* overdrive */

#घोषणा DS1WM_INT_PD	    (1 << 0)	/* presence detect */
#घोषणा DS1WM_INT_PDR	    (1 << 1)	/* presence detect result */
#घोषणा DS1WM_INT_TBE	    (1 << 2)	/* tx buffer empty */
#घोषणा DS1WM_INT_TSRE	    (1 << 3)	/* tx shअगरt रेजिस्टर empty */
#घोषणा DS1WM_INT_RBF	    (1 << 4)	/* rx buffer full */
#घोषणा DS1WM_INT_RSRF	    (1 << 5)	/* rx shअगरt रेजिस्टर full */

#घोषणा DS1WM_INTEN_EPD	    (1 << 0)	/* enable presence detect पूर्णांक */
#घोषणा DS1WM_INTEN_IAS	    (1 << 1)	/* INTR active state */
#घोषणा DS1WM_INTEN_ETBE    (1 << 2)	/* enable tx buffer empty पूर्णांक */
#घोषणा DS1WM_INTEN_ETMT    (1 << 3)	/* enable tx shअगरt रेजिस्टर empty पूर्णांक */
#घोषणा DS1WM_INTEN_ERBF    (1 << 4)	/* enable rx buffer full पूर्णांक */
#घोषणा DS1WM_INTEN_ERSRF   (1 << 5)	/* enable rx shअगरt रेजिस्टर full पूर्णांक */
#घोषणा DS1WM_INTEN_DQO	    (1 << 6)	/* enable direct bus driving ops */

#घोषणा DS1WM_INTEN_NOT_IAS (~DS1WM_INTEN_IAS)	/* all but INTR active state */

#घोषणा DS1WM_TIMEOUT (HZ * 5)

अटल काष्ठा अणु
	अचिन्हित दीर्घ freq;
	अचिन्हित दीर्घ भागisor;
पूर्ण freq[] = अणु
	अणु   1000000, 0x80 पूर्ण,
	अणु   2000000, 0x84 पूर्ण,
	अणु   3000000, 0x81 पूर्ण,
	अणु   4000000, 0x88 पूर्ण,
	अणु   5000000, 0x82 पूर्ण,
	अणु   6000000, 0x85 पूर्ण,
	अणु   7000000, 0x83 पूर्ण,
	अणु   8000000, 0x8c पूर्ण,
	अणु  10000000, 0x86 पूर्ण,
	अणु  12000000, 0x89 पूर्ण,
	अणु  14000000, 0x87 पूर्ण,
	अणु  16000000, 0x90 पूर्ण,
	अणु  20000000, 0x8a पूर्ण,
	अणु  24000000, 0x8d पूर्ण,
	अणु  28000000, 0x8b पूर्ण,
	अणु  32000000, 0x94 पूर्ण,
	अणु  40000000, 0x8e पूर्ण,
	अणु  48000000, 0x91 पूर्ण,
	अणु  56000000, 0x8f पूर्ण,
	अणु  64000000, 0x98 पूर्ण,
	अणु  80000000, 0x92 पूर्ण,
	अणु  96000000, 0x95 पूर्ण,
	अणु 112000000, 0x93 पूर्ण,
	अणु 128000000, 0x9c पूर्ण,
/* you can जारी this table, consult the OPERATION - CLOCK DIVISOR
   section of the ds1wm spec sheet. */
पूर्ण;

काष्ठा ds1wm_data अणु
	व्योम     __iomem *map;
	अचिन्हित पूर्णांक      bus_shअगरt; /* # of shअगरts to calc रेजिस्टर offsets */
	bool      is_hw_big_endian;
	काष्ठा platक्रमm_device *pdev;
	स्थिर काष्ठा mfd_cell   *cell;
	पूर्णांक      irq;
	पूर्णांक      slave_present;
	व्योम     *reset_complete;
	व्योम     *पढ़ो_complete;
	व्योम     *ग_लिखो_complete;
	पूर्णांक      पढ़ो_error;
	/* last byte received */
	u8       पढ़ो_byte;
	/* byte to ग_लिखो that makes all पूर्णांकr disabled, */
	/* considering active_state (IAS) (optimization) */
	u8       पूर्णांक_en_reg_none;
	अचिन्हित पूर्णांक reset_recover_delay; /* see ds1wm.h */
पूर्ण;

अटल अंतरभूत व्योम ds1wm_ग_लिखो_रेजिस्टर(काष्ठा ds1wm_data *ds1wm_data, u32 reg,
					u8 val)
अणु
	अगर (ds1wm_data->is_hw_big_endian) अणु
		चयन (ds1wm_data->bus_shअगरt) अणु
		हाल 0:
			ioग_लिखो8(val, ds1wm_data->map + (reg << 0));
			अवरोध;
		हाल 1:
			ioग_लिखो16be((u16)val, ds1wm_data->map + (reg << 1));
			अवरोध;
		हाल 2:
			ioग_लिखो32be((u32)val, ds1wm_data->map + (reg << 2));
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (ds1wm_data->bus_shअगरt) अणु
		हाल 0:
			ioग_लिखो8(val, ds1wm_data->map + (reg << 0));
			अवरोध;
		हाल 1:
			ioग_लिखो16((u16)val, ds1wm_data->map + (reg << 1));
			अवरोध;
		हाल 2:
			ioग_लिखो32((u32)val, ds1wm_data->map + (reg << 2));
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत u8 ds1wm_पढ़ो_रेजिस्टर(काष्ठा ds1wm_data *ds1wm_data, u32 reg)
अणु
	u32 val = 0;

	अगर (ds1wm_data->is_hw_big_endian) अणु
		चयन (ds1wm_data->bus_shअगरt) अणु
		हाल 0:
			val = ioपढ़ो8(ds1wm_data->map + (reg << 0));
			अवरोध;
		हाल 1:
			val = ioपढ़ो16be(ds1wm_data->map + (reg << 1));
			अवरोध;
		हाल 2:
			val = ioपढ़ो32be(ds1wm_data->map + (reg << 2));
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (ds1wm_data->bus_shअगरt) अणु
		हाल 0:
			val = ioपढ़ो8(ds1wm_data->map + (reg << 0));
			अवरोध;
		हाल 1:
			val = ioपढ़ो16(ds1wm_data->map + (reg << 1));
			अवरोध;
		हाल 2:
			val = ioपढ़ो32(ds1wm_data->map + (reg << 2));
			अवरोध;
		पूर्ण
	पूर्ण
	dev_dbg(&ds1wm_data->pdev->dev,
		"ds1wm_read_register reg: %d, 32 bit val:%x\n", reg, val);
	वापस (u8)val;
पूर्ण


अटल irqवापस_t ds1wm_isr(पूर्णांक isr, व्योम *data)
अणु
	काष्ठा ds1wm_data *ds1wm_data = data;
	u8 पूर्णांकr;
	u8 पूर्णांकen = ds1wm_पढ़ो_रेजिस्टर(ds1wm_data, DS1WM_INT_EN);
	/* अगर no bits are set in पूर्णांक enable रेजिस्टर (except the IAS)
	than go no further, पढ़ोing the regs below has side effects */
	अगर (!(पूर्णांकen & DS1WM_INTEN_NOT_IAS))
		वापस IRQ_NONE;

	ds1wm_ग_लिखो_रेजिस्टर(ds1wm_data,
		DS1WM_INT_EN, ds1wm_data->पूर्णांक_en_reg_none);

	/* this पढ़ो action clears the INTR and certain flags in ds1wm */
	पूर्णांकr = ds1wm_पढ़ो_रेजिस्टर(ds1wm_data, DS1WM_INT);

	ds1wm_data->slave_present = (पूर्णांकr & DS1WM_INT_PDR) ? 0 : 1;

	अगर ((पूर्णांकr & DS1WM_INT_TSRE) && ds1wm_data->ग_लिखो_complete) अणु
		पूर्णांकen &= ~DS1WM_INTEN_ETMT;
		complete(ds1wm_data->ग_लिखो_complete);
	पूर्ण
	अगर (पूर्णांकr & DS1WM_INT_RBF) अणु
		/* this पढ़ो clears the RBF flag */
		ds1wm_data->पढ़ो_byte = ds1wm_पढ़ो_रेजिस्टर(ds1wm_data,
		DS1WM_DATA);
		पूर्णांकen &= ~DS1WM_INTEN_ERBF;
		अगर (ds1wm_data->पढ़ो_complete)
			complete(ds1wm_data->पढ़ो_complete);
	पूर्ण
	अगर ((पूर्णांकr & DS1WM_INT_PD) && ds1wm_data->reset_complete) अणु
		पूर्णांकen &= ~DS1WM_INTEN_EPD;
		complete(ds1wm_data->reset_complete);
	पूर्ण

	ds1wm_ग_लिखो_रेजिस्टर(ds1wm_data, DS1WM_INT_EN, पूर्णांकen);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ds1wm_reset(काष्ठा ds1wm_data *ds1wm_data)
अणु
	अचिन्हित दीर्घ समयleft;
	DECLARE_COMPLETION_ONSTACK(reset_करोne);

	ds1wm_data->reset_complete = &reset_करोne;

	/* enable Presence detect only */
	ds1wm_ग_लिखो_रेजिस्टर(ds1wm_data, DS1WM_INT_EN, DS1WM_INTEN_EPD |
	ds1wm_data->पूर्णांक_en_reg_none);

	ds1wm_ग_लिखो_रेजिस्टर(ds1wm_data, DS1WM_CMD, DS1WM_CMD_1W_RESET);

	समयleft = रुको_क्रम_completion_समयout(&reset_करोne, DS1WM_TIMEOUT);
	ds1wm_data->reset_complete = शून्य;
	अगर (!समयleft) अणु
		dev_err(&ds1wm_data->pdev->dev, "reset failed, timed out\n");
		वापस 1;
	पूर्ण

	अगर (!ds1wm_data->slave_present) अणु
		dev_dbg(&ds1wm_data->pdev->dev, "reset: no devices found\n");
		वापस 1;
	पूर्ण

	अगर (ds1wm_data->reset_recover_delay)
		msleep(ds1wm_data->reset_recover_delay);

	वापस 0;
पूर्ण

अटल पूर्णांक ds1wm_ग_लिखो(काष्ठा ds1wm_data *ds1wm_data, u8 data)
अणु
	अचिन्हित दीर्घ समयleft;
	DECLARE_COMPLETION_ONSTACK(ग_लिखो_करोne);
	ds1wm_data->ग_लिखो_complete = &ग_लिखो_करोne;

	ds1wm_ग_लिखो_रेजिस्टर(ds1wm_data, DS1WM_INT_EN,
	ds1wm_data->पूर्णांक_en_reg_none | DS1WM_INTEN_ETMT);

	ds1wm_ग_लिखो_रेजिस्टर(ds1wm_data, DS1WM_DATA, data);

	समयleft = रुको_क्रम_completion_समयout(&ग_लिखो_करोne, DS1WM_TIMEOUT);

	ds1wm_data->ग_लिखो_complete = शून्य;
	अगर (!समयleft) अणु
		dev_err(&ds1wm_data->pdev->dev, "write failed, timed out\n");
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल u8 ds1wm_पढ़ो(काष्ठा ds1wm_data *ds1wm_data, अचिन्हित अक्षर ग_लिखो_data)
अणु
	अचिन्हित दीर्घ समयleft;
	u8 पूर्णांकEnable = DS1WM_INTEN_ERBF | ds1wm_data->पूर्णांक_en_reg_none;
	DECLARE_COMPLETION_ONSTACK(पढ़ो_करोne);

	ds1wm_पढ़ो_रेजिस्टर(ds1wm_data, DS1WM_DATA);

	ds1wm_data->पढ़ो_complete = &पढ़ो_करोne;
	ds1wm_ग_लिखो_रेजिस्टर(ds1wm_data, DS1WM_INT_EN, पूर्णांकEnable);

	ds1wm_ग_लिखो_रेजिस्टर(ds1wm_data, DS1WM_DATA, ग_लिखो_data);
	समयleft = रुको_क्रम_completion_समयout(&पढ़ो_करोne, DS1WM_TIMEOUT);

	ds1wm_data->पढ़ो_complete = शून्य;
	अगर (!समयleft) अणु
		dev_err(&ds1wm_data->pdev->dev, "read failed, timed out\n");
		ds1wm_data->पढ़ो_error = -ETIMEDOUT;
		वापस 0xFF;
	पूर्ण
	ds1wm_data->पढ़ो_error = 0;
	वापस ds1wm_data->पढ़ो_byte;
पूर्ण

अटल पूर्णांक ds1wm_find_भागisor(पूर्णांक gclk)
अणु
	पूर्णांक i;

	क्रम (i = ARRAY_SIZE(freq)-1; i >= 0; --i)
		अगर (gclk >= freq[i].freq)
			वापस freq[i].भागisor;

	वापस 0;
पूर्ण

अटल व्योम ds1wm_up(काष्ठा ds1wm_data *ds1wm_data)
अणु
	पूर्णांक भागisor;
	काष्ठा device *dev = &ds1wm_data->pdev->dev;
	काष्ठा ds1wm_driver_data *plat = dev_get_platdata(dev);

	अगर (ds1wm_data->cell->enable)
		ds1wm_data->cell->enable(ds1wm_data->pdev);

	भागisor = ds1wm_find_भागisor(plat->घड़ी_rate);
	dev_dbg(dev, "found divisor 0x%x for clock %d\n",
		भागisor, plat->घड़ी_rate);
	अगर (भागisor == 0) अणु
		dev_err(dev, "no suitable divisor for %dHz clock\n",
			plat->घड़ी_rate);
		वापस;
	पूर्ण
	ds1wm_ग_लिखो_रेजिस्टर(ds1wm_data, DS1WM_CLKDIV, भागisor);

	/* Let the w1 घड़ी stabilize. */
	msleep(1);

	ds1wm_reset(ds1wm_data);
पूर्ण

अटल व्योम ds1wm_करोwn(काष्ठा ds1wm_data *ds1wm_data)
अणु
	ds1wm_reset(ds1wm_data);

	/* Disable पूर्णांकerrupts. */
	ds1wm_ग_लिखो_रेजिस्टर(ds1wm_data, DS1WM_INT_EN,
		ds1wm_data->पूर्णांक_en_reg_none);

	अगर (ds1wm_data->cell->disable)
		ds1wm_data->cell->disable(ds1wm_data->pdev);
पूर्ण

/* --------------------------------------------------------------------- */
/* w1 methods */

अटल u8 ds1wm_पढ़ो_byte(व्योम *data)
अणु
	काष्ठा ds1wm_data *ds1wm_data = data;

	वापस ds1wm_पढ़ो(ds1wm_data, 0xff);
पूर्ण

अटल व्योम ds1wm_ग_लिखो_byte(व्योम *data, u8 byte)
अणु
	काष्ठा ds1wm_data *ds1wm_data = data;

	ds1wm_ग_लिखो(ds1wm_data, byte);
पूर्ण

अटल u8 ds1wm_reset_bus(व्योम *data)
अणु
	काष्ठा ds1wm_data *ds1wm_data = data;

	ds1wm_reset(ds1wm_data);

	वापस 0;
पूर्ण

अटल व्योम ds1wm_search(व्योम *data, काष्ठा w1_master *master_dev,
			u8 search_type, w1_slave_found_callback slave_found)
अणु
	काष्ठा ds1wm_data *ds1wm_data = data;
	पूर्णांक i;
	पूर्णांक ms_discrep_bit = -1;
	u64 r = 0; /* holds the progress of the search */
	u64 r_prime, d;
	अचिन्हित slaves_found = 0;
	अचिन्हित पूर्णांक pass = 0;

	dev_dbg(&ds1wm_data->pdev->dev, "search begin\n");
	जबतक (true) अणु
		++pass;
		अगर (pass > 100) अणु
			dev_dbg(&ds1wm_data->pdev->dev,
				"too many attempts (100), search aborted\n");
			वापस;
		पूर्ण

		mutex_lock(&master_dev->bus_mutex);
		अगर (ds1wm_reset(ds1wm_data)) अणु
			mutex_unlock(&master_dev->bus_mutex);
			dev_dbg(&ds1wm_data->pdev->dev,
				"pass: %d reset error (or no slaves)\n", pass);
			अवरोध;
		पूर्ण

		dev_dbg(&ds1wm_data->pdev->dev,
			"pass: %d r : %0#18llx writing SEARCH_ROM\n", pass, r);
		ds1wm_ग_लिखो(ds1wm_data, search_type);
		dev_dbg(&ds1wm_data->pdev->dev,
			"pass: %d entering ASM\n", pass);
		ds1wm_ग_लिखो_रेजिस्टर(ds1wm_data, DS1WM_CMD, DS1WM_CMD_SRA);
		dev_dbg(&ds1wm_data->pdev->dev,
			"pass: %d beginning nibble loop\n", pass);

		r_prime = 0;
		d = 0;
		/* we work one nibble at a समय */
		/* each nibble is पूर्णांकerleaved to क्रमm a byte */
		क्रम (i = 0; i < 16; i++) अणु

			अचिन्हित अक्षर resp, _r, _r_prime, _d;

			_r = (r >> (4*i)) & 0xf;
			_r = ((_r & 0x1) << 1) |
			((_r & 0x2) << 2) |
			((_r & 0x4) << 3) |
			((_r & 0x8) << 4);

			/* ग_लिखोs _r, then पढ़ोs back: */
			resp = ds1wm_पढ़ो(ds1wm_data, _r);

			अगर (ds1wm_data->पढ़ो_error) अणु
				dev_err(&ds1wm_data->pdev->dev,
				"pass: %d nibble: %d read error\n", pass, i);
				अवरोध;
			पूर्ण

			_r_prime = ((resp & 0x02) >> 1) |
			((resp & 0x08) >> 2) |
			((resp & 0x20) >> 3) |
			((resp & 0x80) >> 4);

			_d = ((resp & 0x01) >> 0) |
			((resp & 0x04) >> 1) |
			((resp & 0x10) >> 2) |
			((resp & 0x40) >> 3);

			r_prime |= (अचिन्हित दीर्घ दीर्घ) _r_prime << (i * 4);
			d |= (अचिन्हित दीर्घ दीर्घ) _d << (i * 4);

		पूर्ण
		अगर (ds1wm_data->पढ़ो_error) अणु
			mutex_unlock(&master_dev->bus_mutex);
			dev_err(&ds1wm_data->pdev->dev,
				"pass: %d read error, retrying\n", pass);
			अवरोध;
		पूर्ण
		dev_dbg(&ds1wm_data->pdev->dev,
			"pass: %d r\': %0#18llx d:%0#18llx\n",
			pass, r_prime, d);
		dev_dbg(&ds1wm_data->pdev->dev,
			"pass: %d nibble loop complete, exiting ASM\n", pass);
		ds1wm_ग_लिखो_रेजिस्टर(ds1wm_data, DS1WM_CMD, ~DS1WM_CMD_SRA);
		dev_dbg(&ds1wm_data->pdev->dev,
			"pass: %d resetting bus\n", pass);
		ds1wm_reset(ds1wm_data);
		mutex_unlock(&master_dev->bus_mutex);
		अगर ((r_prime & ((u64)1 << 63)) && (d & ((u64)1 << 63))) अणु
			dev_err(&ds1wm_data->pdev->dev,
				"pass: %d bus error, retrying\n", pass);
			जारी; /* start over */
		पूर्ण


		dev_dbg(&ds1wm_data->pdev->dev,
			"pass: %d found %0#18llx\n", pass, r_prime);
		slave_found(master_dev, r_prime);
		++slaves_found;
		dev_dbg(&ds1wm_data->pdev->dev,
			"pass: %d complete, preparing next pass\n", pass);

		/* any discrepency found which we alपढ़ोy choose the
		   '1' branch is now is now irrelevant we reveal the
		   next branch with this: */
		d &= ~r;
		/* find last bit set, i.e. the most signअगर. bit set */
		ms_discrep_bit = fls64(d) - 1;
		dev_dbg(&ds1wm_data->pdev->dev,
			"pass: %d new d:%0#18llx MS discrep bit:%d\n",
			pass, d, ms_discrep_bit);

		/* prev_ms_discrep_bit = ms_discrep_bit;
		   prepare क्रम next ROM search:		    */
		अगर (ms_discrep_bit == -1)
			अवरोध;

		r = (r &  ~(~0ull << (ms_discrep_bit))) | 1 << ms_discrep_bit;
	पूर्ण /* end जबतक true */
	dev_dbg(&ds1wm_data->pdev->dev,
		"pass: %d total: %d search done ms d bit pos: %d\n", pass,
		slaves_found, ms_discrep_bit);
पूर्ण

/* --------------------------------------------------------------------- */

अटल काष्ठा w1_bus_master ds1wm_master = अणु
	.पढ़ो_byte  = ds1wm_पढ़ो_byte,
	.ग_लिखो_byte = ds1wm_ग_लिखो_byte,
	.reset_bus  = ds1wm_reset_bus,
	.search	    = ds1wm_search,
पूर्ण;

अटल पूर्णांक ds1wm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ds1wm_data *ds1wm_data;
	काष्ठा ds1wm_driver_data *plat;
	काष्ठा resource *res;
	पूर्णांक ret;
	u8 पूर्णांकen;

	अगर (!pdev)
		वापस -ENODEV;

	ds1wm_data = devm_kzalloc(&pdev->dev, माप(*ds1wm_data), GFP_KERNEL);
	अगर (!ds1wm_data)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(pdev, ds1wm_data);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENXIO;
	ds1wm_data->map = devm_ioremap(&pdev->dev, res->start,
				       resource_size(res));
	अगर (!ds1wm_data->map)
		वापस -ENOMEM;

	ds1wm_data->pdev = pdev;
	ds1wm_data->cell = mfd_get_cell(pdev);
	अगर (!ds1wm_data->cell)
		वापस -ENODEV;
	plat = dev_get_platdata(&pdev->dev);
	अगर (!plat)
		वापस -ENODEV;

	/* how many bits to shअगरt रेजिस्टर number to get रेजिस्टर offset */
	अगर (plat->bus_shअगरt > 2) अणु
		dev_err(&ds1wm_data->pdev->dev,
			"illegal bus shift %d, not written",
			ds1wm_data->bus_shअगरt);
		वापस -EINVAL;
	पूर्ण

	ds1wm_data->bus_shअगरt = plat->bus_shअगरt;
	/* make sure resource has space क्रम 8 रेजिस्टरs */
	अगर ((8 << ds1wm_data->bus_shअगरt) > resource_size(res)) अणु
		dev_err(&ds1wm_data->pdev->dev,
			"memory resource size %d to small, should be %d\n",
			(पूर्णांक)resource_size(res),
			8 << ds1wm_data->bus_shअगरt);
		वापस -EINVAL;
	पूर्ण

	ds1wm_data->is_hw_big_endian = plat->is_hw_big_endian;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);
	अगर (!res)
		वापस -ENXIO;
	ds1wm_data->irq = res->start;
	ds1wm_data->पूर्णांक_en_reg_none = (plat->active_high ? DS1WM_INTEN_IAS : 0);
	ds1wm_data->reset_recover_delay = plat->reset_recover_delay;

	/* Mask पूर्णांकerrupts, set IAS beक्रमe claiming पूर्णांकerrupt */
	पूर्णांकen = ds1wm_पढ़ो_रेजिस्टर(ds1wm_data, DS1WM_INT_EN);
	ds1wm_ग_लिखो_रेजिस्टर(ds1wm_data,
		DS1WM_INT_EN, ds1wm_data->पूर्णांक_en_reg_none);

	अगर (res->flags & IORESOURCE_IRQ_HIGHEDGE)
		irq_set_irq_type(ds1wm_data->irq, IRQ_TYPE_EDGE_RISING);
	अगर (res->flags & IORESOURCE_IRQ_LOWEDGE)
		irq_set_irq_type(ds1wm_data->irq, IRQ_TYPE_EDGE_FALLING);
	अगर (res->flags & IORESOURCE_IRQ_HIGHLEVEL)
		irq_set_irq_type(ds1wm_data->irq, IRQ_TYPE_LEVEL_HIGH);
	अगर (res->flags & IORESOURCE_IRQ_LOWLEVEL)
		irq_set_irq_type(ds1wm_data->irq, IRQ_TYPE_LEVEL_LOW);

	ret = devm_request_irq(&pdev->dev, ds1wm_data->irq, ds1wm_isr,
			IRQF_SHARED, "ds1wm", ds1wm_data);
	अगर (ret) अणु
		dev_err(&ds1wm_data->pdev->dev,
			"devm_request_irq %d failed with errno %d\n",
			ds1wm_data->irq,
			ret);

		वापस ret;
	पूर्ण

	ds1wm_up(ds1wm_data);

	ds1wm_master.data = (व्योम *)ds1wm_data;

	ret = w1_add_master_device(&ds1wm_master);
	अगर (ret)
		जाओ err;

	dev_dbg(&ds1wm_data->pdev->dev,
		"ds1wm: probe successful, IAS: %d, rec.delay: %d, clockrate: %d, bus-shift: %d, is Hw Big Endian: %d\n",
		plat->active_high,
		plat->reset_recover_delay,
		plat->घड़ी_rate,
		ds1wm_data->bus_shअगरt,
		ds1wm_data->is_hw_big_endian);
	वापस 0;

err:
	ds1wm_करोwn(ds1wm_data);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ds1wm_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state)
अणु
	काष्ठा ds1wm_data *ds1wm_data = platक्रमm_get_drvdata(pdev);

	ds1wm_करोwn(ds1wm_data);

	वापस 0;
पूर्ण

अटल पूर्णांक ds1wm_resume(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ds1wm_data *ds1wm_data = platक्रमm_get_drvdata(pdev);

	ds1wm_up(ds1wm_data);

	वापस 0;
पूर्ण
#अन्यथा
#घोषणा ds1wm_suspend शून्य
#घोषणा ds1wm_resume शून्य
#पूर्ण_अगर

अटल पूर्णांक ds1wm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ds1wm_data *ds1wm_data = platक्रमm_get_drvdata(pdev);

	w1_हटाओ_master_device(&ds1wm_master);
	ds1wm_करोwn(ds1wm_data);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ds1wm_driver = अणु
	.driver   = अणु
		.name = "ds1wm",
	पूर्ण,
	.probe    = ds1wm_probe,
	.हटाओ   = ds1wm_हटाओ,
	.suspend  = ds1wm_suspend,
	.resume   = ds1wm_resume
पूर्ण;

अटल पूर्णांक __init ds1wm_init(व्योम)
अणु
	pr_info("DS1WM w1 busmaster driver - (c) 2004 Szabolcs Gyurko\n");
	वापस platक्रमm_driver_रेजिस्टर(&ds1wm_driver);
पूर्ण

अटल व्योम __निकास ds1wm_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ds1wm_driver);
पूर्ण

module_init(ds1wm_init);
module_निकास(ds1wm_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Szabolcs Gyurko <szabolcs.gyurko@tlt.hu>, "
	"Matt Reimer <mreimer@vpop.net>,"
	"Jean-Francois Dagenais <dagenaisj@sonatest.com>");
MODULE_DESCRIPTION("DS1WM w1 busmaster driver");
