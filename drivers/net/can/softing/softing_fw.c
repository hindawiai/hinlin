<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008-2010
 *
 * - Kurt Van Dijck, EIA Electronics
 */

#समावेश <linux/firmware.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <यंत्र/भाग64.h>
#समावेश <यंत्र/पन.स>

#समावेश "softing.h"

/*
 * low level DPRAM command.
 * Make sure that card->dpram[DPRAM_FCT_HOST] is preset
 */
अटल पूर्णांक _softing_fct_cmd(काष्ठा softing *card, पूर्णांक16_t cmd, uपूर्णांक16_t vector,
		स्थिर अक्षर *msg)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ stamp;

	ioग_लिखो16(cmd, &card->dpram[DPRAM_FCT_PARAM]);
	ioग_लिखो8(vector >> 8, &card->dpram[DPRAM_FCT_HOST + 1]);
	ioग_लिखो8(vector, &card->dpram[DPRAM_FCT_HOST]);
	/* be sure to flush this to the card */
	wmb();
	stamp = jअगरfies + 1 * HZ;
	/* रुको क्रम card */
	करो अणु
		/* DPRAM_FCT_HOST is _not_ aligned */
		ret = ioपढ़ो8(&card->dpram[DPRAM_FCT_HOST]) +
			(ioपढ़ो8(&card->dpram[DPRAM_FCT_HOST + 1]) << 8);
		/* करोn't have any cached variables */
		rmb();
		अगर (ret == RES_OK)
			/* पढ़ो वापस-value now */
			वापस ioपढ़ो16(&card->dpram[DPRAM_FCT_RESULT]);

		अगर ((ret != vector) || समय_after(jअगरfies, stamp))
			अवरोध;
		/* process context => relax */
		usleep_range(500, 10000);
	पूर्ण जबतक (1);

	ret = (ret == RES_NONE) ? -ETIMEDOUT : -ECANCELED;
	dev_alert(&card->pdev->dev, "firmware %s failed (%i)\n", msg, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक softing_fct_cmd(काष्ठा softing *card, पूर्णांक16_t cmd, स्थिर अक्षर *msg)
अणु
	पूर्णांक ret;

	ret = _softing_fct_cmd(card, cmd, 0, msg);
	अगर (ret > 0) अणु
		dev_alert(&card->pdev->dev, "%s returned %u\n", msg, ret);
		ret = -EIO;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक softing_bootloader_command(काष्ठा softing *card, पूर्णांक16_t cmd,
		स्थिर अक्षर *msg)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ stamp;

	ioग_लिखो16(RES_NONE, &card->dpram[DPRAM_RECEIPT]);
	ioग_लिखो16(cmd, &card->dpram[DPRAM_COMMAND]);
	/* be sure to flush this to the card */
	wmb();
	stamp = jअगरfies + 3 * HZ;
	/* रुको क्रम card */
	करो अणु
		ret = ioपढ़ो16(&card->dpram[DPRAM_RECEIPT]);
		/* करोn't have any cached variables */
		rmb();
		अगर (ret == RES_OK)
			वापस 0;
		अगर (समय_after(jअगरfies, stamp))
			अवरोध;
		/* process context => relax */
		usleep_range(500, 10000);
	पूर्ण जबतक (!संकेत_pending(current));

	ret = (ret == RES_NONE) ? -ETIMEDOUT : -ECANCELED;
	dev_alert(&card->pdev->dev, "bootloader %s failed (%i)\n", msg, ret);
	वापस ret;
पूर्ण

अटल पूर्णांक fw_parse(स्थिर uपूर्णांक8_t **pmem, uपूर्णांक16_t *ptype, uपूर्णांक32_t *paddr,
		uपूर्णांक16_t *plen, स्थिर uपूर्णांक8_t **pdat)
अणु
	uपूर्णांक16_t checksum[2];
	स्थिर uपूर्णांक8_t *mem;
	स्थिर uपूर्णांक8_t *end;

	/*
	 * firmware records are a binary, unaligned stream composed of:
	 * uपूर्णांक16_t type;
	 * uपूर्णांक32_t addr;
	 * uपूर्णांक16_t len;
	 * uपूर्णांक8_t dat[len];
	 * uपूर्णांक16_t checksum;
	 * all values in little endian.
	 * We could define a काष्ठा क्रम this, with __attribute__((packed)),
	 * but would that solve the alignment in _all_ हालs (cfr. the
	 * काष्ठा itself may be an odd address)?
	 *
	 * I chose to use leXX_to_cpup() since this solves both
	 * endianness & alignment.
	 */
	mem = *pmem;
	*ptype = le16_to_cpup((व्योम *)&mem[0]);
	*paddr = le32_to_cpup((व्योम *)&mem[2]);
	*plen = le16_to_cpup((व्योम *)&mem[6]);
	*pdat = &mem[8];
	/* verअगरy checksum */
	end = &mem[8 + *plen];
	checksum[0] = le16_to_cpup((व्योम *)end);
	क्रम (checksum[1] = 0; mem < end; ++mem)
		checksum[1] += *mem;
	अगर (checksum[0] != checksum[1])
		वापस -EINVAL;
	/* increment */
	*pmem += 10 + *plen;
	वापस 0;
पूर्ण

पूर्णांक softing_load_fw(स्थिर अक्षर *file, काष्ठा softing *card,
		__iomem uपूर्णांक8_t *dpram, अचिन्हित पूर्णांक size, पूर्णांक offset)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;
	स्थिर uपूर्णांक8_t *mem, *end, *dat;
	uपूर्णांक16_t type, len;
	uपूर्णांक32_t addr;
	uपूर्णांक8_t *buf = शून्य, *new_buf;
	पूर्णांक buflen = 0;
	पूर्णांक8_t type_end = 0;

	ret = request_firmware(&fw, file, &card->pdev->dev);
	अगर (ret < 0)
		वापस ret;
	dev_dbg(&card->pdev->dev, "%s, firmware(%s) got %u bytes"
		", offset %c0x%04x\n",
		card->pdat->name, file, (अचिन्हित पूर्णांक)fw->size,
		(offset >= 0) ? '+' : '-', (अचिन्हित पूर्णांक)असल(offset));
	/* parse the firmware */
	mem = fw->data;
	end = &mem[fw->size];
	/* look क्रम header record */
	ret = fw_parse(&mem, &type, &addr, &len, &dat);
	अगर (ret < 0)
		जाओ failed;
	अगर (type != 0xffff)
		जाओ failed;
	अगर (म_भेदन("Structured Binary Format, Softing GmbH" , dat, len)) अणु
		ret = -EINVAL;
		जाओ failed;
	पूर्ण
	/* ok, we had a header */
	जबतक (mem < end) अणु
		ret = fw_parse(&mem, &type, &addr, &len, &dat);
		अगर (ret < 0)
			जाओ failed;
		अगर (type == 3) अणु
			/* start address, not used here */
			जारी;
		पूर्ण अन्यथा अगर (type == 1) अणु
			/* eof */
			type_end = 1;
			अवरोध;
		पूर्ण अन्यथा अगर (type != 0) अणु
			ret = -EINVAL;
			जाओ failed;
		पूर्ण

		अगर ((addr + len + offset) > size)
			जाओ failed;
		स_नकल_toio(&dpram[addr + offset], dat, len);
		/* be sure to flush caches from IO space */
		mb();
		अगर (len > buflen) अणु
			/* align buflen */
			buflen = (len + (1024-1)) & ~(1024-1);
			new_buf = kपुनः_स्मृति(buf, buflen, GFP_KERNEL);
			अगर (!new_buf) अणु
				ret = -ENOMEM;
				जाओ failed;
			पूर्ण
			buf = new_buf;
		पूर्ण
		/* verअगरy record data */
		स_नकल_fromio(buf, &dpram[addr + offset], len);
		अगर (स_भेद(buf, dat, len)) अणु
			/* is not ok */
			dev_alert(&card->pdev->dev, "DPRAM readback failed\n");
			ret = -EIO;
			जाओ failed;
		पूर्ण
	पूर्ण
	अगर (!type_end)
		/* no end record seen */
		जाओ failed;
	ret = 0;
failed:
	kमुक्त(buf);
	release_firmware(fw);
	अगर (ret < 0)
		dev_info(&card->pdev->dev, "firmware %s failed\n", file);
	वापस ret;
पूर्ण

पूर्णांक softing_load_app_fw(स्थिर अक्षर *file, काष्ठा softing *card)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर uपूर्णांक8_t *mem, *end, *dat;
	पूर्णांक ret, j;
	uपूर्णांक16_t type, len;
	uपूर्णांक32_t addr, start_addr = 0;
	अचिन्हित पूर्णांक sum, rx_sum;
	पूर्णांक8_t type_end = 0, type_entrypoपूर्णांक = 0;

	ret = request_firmware(&fw, file, &card->pdev->dev);
	अगर (ret) अणु
		dev_alert(&card->pdev->dev, "request_firmware(%s) got %i\n",
			file, ret);
		वापस ret;
	पूर्ण
	dev_dbg(&card->pdev->dev, "firmware(%s) got %lu bytes\n",
		file, (अचिन्हित दीर्घ)fw->size);
	/* parse the firmware */
	mem = fw->data;
	end = &mem[fw->size];
	/* look क्रम header record */
	ret = fw_parse(&mem, &type, &addr, &len, &dat);
	अगर (ret)
		जाओ failed;
	ret = -EINVAL;
	अगर (type != 0xffff) अणु
		dev_alert(&card->pdev->dev, "firmware starts with type 0x%x\n",
			type);
		जाओ failed;
	पूर्ण
	अगर (म_भेदन("Structured Binary Format, Softing GmbH", dat, len)) अणु
		dev_alert(&card->pdev->dev, "firmware string '%.*s' fault\n",
				len, dat);
		जाओ failed;
	पूर्ण
	/* ok, we had a header */
	जबतक (mem < end) अणु
		ret = fw_parse(&mem, &type, &addr, &len, &dat);
		अगर (ret)
			जाओ failed;

		अगर (type == 3) अणु
			/* start address */
			start_addr = addr;
			type_entrypoपूर्णांक = 1;
			जारी;
		पूर्ण अन्यथा अगर (type == 1) अणु
			/* eof */
			type_end = 1;
			अवरोध;
		पूर्ण अन्यथा अगर (type != 0) अणु
			dev_alert(&card->pdev->dev,
					"unknown record type 0x%04x\n", type);
			ret = -EINVAL;
			जाओ failed;
		पूर्ण

		/* regular data */
		क्रम (sum = 0, j = 0; j < len; ++j)
			sum += dat[j];
		/* work in 16bit (target) */
		sum &= 0xffff;

		स_नकल_toio(&card->dpram[card->pdat->app.offs], dat, len);
		ioग_लिखो32(card->pdat->app.offs + card->pdat->app.addr,
				&card->dpram[DPRAM_COMMAND + 2]);
		ioग_लिखो32(addr, &card->dpram[DPRAM_COMMAND + 6]);
		ioग_लिखो16(len, &card->dpram[DPRAM_COMMAND + 10]);
		ioग_लिखो8(1, &card->dpram[DPRAM_COMMAND + 12]);
		ret = softing_bootloader_command(card, 1, "loading app.");
		अगर (ret < 0)
			जाओ failed;
		/* verअगरy checksum */
		rx_sum = ioपढ़ो16(&card->dpram[DPRAM_RECEIPT + 2]);
		अगर (rx_sum != sum) अणु
			dev_alert(&card->pdev->dev, "SRAM seems to be damaged"
				", wanted 0x%04x, got 0x%04x\n", sum, rx_sum);
			ret = -EIO;
			जाओ failed;
		पूर्ण
	पूर्ण
	अगर (!type_end || !type_entrypoपूर्णांक)
		जाओ failed;
	/* start application in card */
	ioग_लिखो32(start_addr, &card->dpram[DPRAM_COMMAND + 2]);
	ioग_लिखो8(1, &card->dpram[DPRAM_COMMAND + 6]);
	ret = softing_bootloader_command(card, 3, "start app.");
	अगर (ret < 0)
		जाओ failed;
	ret = 0;
failed:
	release_firmware(fw);
	अगर (ret < 0)
		dev_info(&card->pdev->dev, "firmware %s failed\n", file);
	वापस ret;
पूर्ण

अटल पूर्णांक softing_reset_chip(काष्ठा softing *card)
अणु
	पूर्णांक ret;

	करो अणु
		/* reset chip */
		ioग_लिखो8(0, &card->dpram[DPRAM_RESET_RX_FIFO]);
		ioग_लिखो8(0, &card->dpram[DPRAM_RESET_RX_FIFO+1]);
		ioग_लिखो8(1, &card->dpram[DPRAM_RESET]);
		ioग_लिखो8(0, &card->dpram[DPRAM_RESET+1]);

		ret = softing_fct_cmd(card, 0, "reset_can");
		अगर (!ret)
			अवरोध;
		अगर (संकेत_pending(current))
			/* करोn't रुको any दीर्घer */
			अवरोध;
	पूर्ण जबतक (1);
	card->tx.pending = 0;
	वापस ret;
पूर्ण

पूर्णांक softing_chip_घातeron(काष्ठा softing *card)
अणु
	पूर्णांक ret;
	/* sync */
	ret = _softing_fct_cmd(card, 99, 0x55, "sync-a");
	अगर (ret < 0)
		जाओ failed;

	ret = _softing_fct_cmd(card, 99, 0xaa, "sync-b");
	अगर (ret < 0)
		जाओ failed;

	ret = softing_reset_chip(card);
	अगर (ret < 0)
		जाओ failed;
	/* get_serial */
	ret = softing_fct_cmd(card, 43, "get_serial_number");
	अगर (ret < 0)
		जाओ failed;
	card->id.serial = ioपढ़ो32(&card->dpram[DPRAM_FCT_PARAM]);
	/* get_version */
	ret = softing_fct_cmd(card, 12, "get_version");
	अगर (ret < 0)
		जाओ failed;
	card->id.fw_version = ioपढ़ो16(&card->dpram[DPRAM_FCT_PARAM + 2]);
	card->id.hw_version = ioपढ़ो16(&card->dpram[DPRAM_FCT_PARAM + 4]);
	card->id.license = ioपढ़ो16(&card->dpram[DPRAM_FCT_PARAM + 6]);
	card->id.chip[0] = ioपढ़ो16(&card->dpram[DPRAM_FCT_PARAM + 8]);
	card->id.chip[1] = ioपढ़ो16(&card->dpram[DPRAM_FCT_PARAM + 10]);
	वापस 0;
failed:
	वापस ret;
पूर्ण

अटल व्योम softing_initialize_बारtamp(काष्ठा softing *card)
अणु
	uपूर्णांक64_t ovf;

	card->ts_ref = kसमय_get();

	/* 16MHz is the reference */
	ovf = 0x100000000ULL * 16;
	करो_भाग(ovf, card->pdat->freq ?: 16);

	card->ts_overflow = kसमय_add_us(0, ovf);
पूर्ण

kसमय_प्रकार softing_raw2kसमय(काष्ठा softing *card, u32 raw)
अणु
	uपूर्णांक64_t rawl;
	kसमय_प्रकार now, real_offset;
	kसमय_प्रकार target;
	kसमय_प्रकार पंचांगp;

	now = kसमय_get();
	real_offset = kसमय_sub(kसमय_get_real(), now);

	/* find nsec from card */
	rawl = raw * 16;
	करो_भाग(rawl, card->pdat->freq ?: 16);
	target = kसमय_add_us(card->ts_ref, rawl);
	/* test क्रम overflows */
	पंचांगp = kसमय_add(target, card->ts_overflow);
	जबतक (unlikely(kसमय_प्रकारo_ns(पंचांगp) > kसमय_प्रकारo_ns(now))) अणु
		card->ts_ref = kसमय_add(card->ts_ref, card->ts_overflow);
		target = पंचांगp;
		पंचांगp = kसमय_add(target, card->ts_overflow);
	पूर्ण
	वापस kसमय_add(target, real_offset);
पूर्ण

अटल अंतरभूत पूर्णांक softing_error_reporting(काष्ठा net_device *netdev)
अणु
	काष्ठा softing_priv *priv = netdev_priv(netdev);

	वापस (priv->can.ctrlmode & CAN_CTRLMODE_BERR_REPORTING)
		? 1 : 0;
पूर्ण

पूर्णांक softing_startstop(काष्ठा net_device *dev, पूर्णांक up)
अणु
	पूर्णांक ret;
	काष्ठा softing *card;
	काष्ठा softing_priv *priv;
	काष्ठा net_device *netdev;
	पूर्णांक bus_biपंचांगask_start;
	पूर्णांक j, error_reporting;
	काष्ठा can_frame msg;
	स्थिर काष्ठा can_bittiming *bt;

	priv = netdev_priv(dev);
	card = priv->card;

	अगर (!card->fw.up)
		वापस -EIO;

	ret = mutex_lock_पूर्णांकerruptible(&card->fw.lock);
	अगर (ret)
		वापस ret;

	bus_biपंचांगask_start = 0;
	अगर (dev && up)
		/* prepare to start this bus as well */
		bus_biपंचांगask_start |= (1 << priv->index);
	/* bring netdevs करोwn */
	क्रम (j = 0; j < ARRAY_SIZE(card->net); ++j) अणु
		netdev = card->net[j];
		अगर (!netdev)
			जारी;
		priv = netdev_priv(netdev);

		अगर (dev != netdev)
			netअगर_stop_queue(netdev);

		अगर (netअगर_running(netdev)) अणु
			अगर (dev != netdev)
				bus_biपंचांगask_start |= (1 << j);
			priv->tx.pending = 0;
			priv->tx.echo_put = 0;
			priv->tx.echo_get = 0;
			/*
			 * this bus' may just have called खोलो_candev()
			 * which is rather stupid to call बंद_candev()
			 * alपढ़ोy
			 * but we may come here from busoff recovery too
			 * in which हाल the echo_skb _needs_ flushing too.
			 * just be sure to call खोलो_candev() again
			 */
			बंद_candev(netdev);
		पूर्ण
		priv->can.state = CAN_STATE_STOPPED;
	पूर्ण
	card->tx.pending = 0;

	softing_enable_irq(card, 0);
	ret = softing_reset_chip(card);
	अगर (ret)
		जाओ failed;
	अगर (!bus_biपंचांगask_start)
		/* no buses to be brought up */
		जाओ card_करोne;

	अगर ((bus_biपंचांगask_start & 1) && (bus_biपंचांगask_start & 2)
			&& (softing_error_reporting(card->net[0])
				!= softing_error_reporting(card->net[1]))) अणु
		dev_alert(&card->pdev->dev,
				"err_reporting flag differs for buses\n");
		जाओ invalid;
	पूर्ण
	error_reporting = 0;
	अगर (bus_biपंचांगask_start & 1) अणु
		netdev = card->net[0];
		priv = netdev_priv(netdev);
		error_reporting += softing_error_reporting(netdev);
		/* init chip 1 */
		bt = &priv->can.bittiming;
		ioग_लिखो16(bt->brp, &card->dpram[DPRAM_FCT_PARAM + 2]);
		ioग_लिखो16(bt->sjw, &card->dpram[DPRAM_FCT_PARAM + 4]);
		ioग_लिखो16(bt->phase_seg1 + bt->prop_seg,
				&card->dpram[DPRAM_FCT_PARAM + 6]);
		ioग_लिखो16(bt->phase_seg2, &card->dpram[DPRAM_FCT_PARAM + 8]);
		ioग_लिखो16((priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES) ? 1 : 0,
				&card->dpram[DPRAM_FCT_PARAM + 10]);
		ret = softing_fct_cmd(card, 1, "initialize_chip[0]");
		अगर (ret < 0)
			जाओ failed;
		/* set mode */
		ioग_लिखो16(0, &card->dpram[DPRAM_FCT_PARAM + 2]);
		ioग_लिखो16(0, &card->dpram[DPRAM_FCT_PARAM + 4]);
		ret = softing_fct_cmd(card, 3, "set_mode[0]");
		अगर (ret < 0)
			जाओ failed;
		/* set filter */
		/* 11bit id & mask */
		ioग_लिखो16(0x0000, &card->dpram[DPRAM_FCT_PARAM + 2]);
		ioग_लिखो16(0x07ff, &card->dpram[DPRAM_FCT_PARAM + 4]);
		/* 29bit id.lo & mask.lo & id.hi & mask.hi */
		ioग_लिखो16(0x0000, &card->dpram[DPRAM_FCT_PARAM + 6]);
		ioग_लिखो16(0xffff, &card->dpram[DPRAM_FCT_PARAM + 8]);
		ioग_लिखो16(0x0000, &card->dpram[DPRAM_FCT_PARAM + 10]);
		ioग_लिखो16(0x1fff, &card->dpram[DPRAM_FCT_PARAM + 12]);
		ret = softing_fct_cmd(card, 7, "set_filter[0]");
		अगर (ret < 0)
			जाओ failed;
		/* set output control */
		ioग_लिखो16(priv->output, &card->dpram[DPRAM_FCT_PARAM + 2]);
		ret = softing_fct_cmd(card, 5, "set_output[0]");
		अगर (ret < 0)
			जाओ failed;
	पूर्ण
	अगर (bus_biपंचांगask_start & 2) अणु
		netdev = card->net[1];
		priv = netdev_priv(netdev);
		error_reporting += softing_error_reporting(netdev);
		/* init chip2 */
		bt = &priv->can.bittiming;
		ioग_लिखो16(bt->brp, &card->dpram[DPRAM_FCT_PARAM + 2]);
		ioग_लिखो16(bt->sjw, &card->dpram[DPRAM_FCT_PARAM + 4]);
		ioग_लिखो16(bt->phase_seg1 + bt->prop_seg,
				&card->dpram[DPRAM_FCT_PARAM + 6]);
		ioग_लिखो16(bt->phase_seg2, &card->dpram[DPRAM_FCT_PARAM + 8]);
		ioग_लिखो16((priv->can.ctrlmode & CAN_CTRLMODE_3_SAMPLES) ? 1 : 0,
				&card->dpram[DPRAM_FCT_PARAM + 10]);
		ret = softing_fct_cmd(card, 2, "initialize_chip[1]");
		अगर (ret < 0)
			जाओ failed;
		/* set mode2 */
		ioग_लिखो16(0, &card->dpram[DPRAM_FCT_PARAM + 2]);
		ioग_लिखो16(0, &card->dpram[DPRAM_FCT_PARAM + 4]);
		ret = softing_fct_cmd(card, 4, "set_mode[1]");
		अगर (ret < 0)
			जाओ failed;
		/* set filter2 */
		/* 11bit id & mask */
		ioग_लिखो16(0x0000, &card->dpram[DPRAM_FCT_PARAM + 2]);
		ioग_लिखो16(0x07ff, &card->dpram[DPRAM_FCT_PARAM + 4]);
		/* 29bit id.lo & mask.lo & id.hi & mask.hi */
		ioग_लिखो16(0x0000, &card->dpram[DPRAM_FCT_PARAM + 6]);
		ioग_लिखो16(0xffff, &card->dpram[DPRAM_FCT_PARAM + 8]);
		ioग_लिखो16(0x0000, &card->dpram[DPRAM_FCT_PARAM + 10]);
		ioग_लिखो16(0x1fff, &card->dpram[DPRAM_FCT_PARAM + 12]);
		ret = softing_fct_cmd(card, 8, "set_filter[1]");
		अगर (ret < 0)
			जाओ failed;
		/* set output control2 */
		ioग_लिखो16(priv->output, &card->dpram[DPRAM_FCT_PARAM + 2]);
		ret = softing_fct_cmd(card, 6, "set_output[1]");
		अगर (ret < 0)
			जाओ failed;
	पूर्ण
	/* enable_error_frame */
	/*
	 * Error reporting is चयनed off at the moment since
	 * the receiving of them is not yet 100% verअगरied
	 * This should be enabled sooner or later
	 *
	अगर (error_reporting) अणु
		ret = softing_fct_cmd(card, 51, "enable_error_frame");
		अगर (ret < 0)
			जाओ failed;
	पूर्ण
	*/
	/* initialize पूर्णांकerface */
	ioग_लिखो16(1, &card->dpram[DPRAM_FCT_PARAM + 2]);
	ioग_लिखो16(1, &card->dpram[DPRAM_FCT_PARAM + 4]);
	ioग_लिखो16(1, &card->dpram[DPRAM_FCT_PARAM + 6]);
	ioग_लिखो16(1, &card->dpram[DPRAM_FCT_PARAM + 8]);
	ioग_लिखो16(1, &card->dpram[DPRAM_FCT_PARAM + 10]);
	ioग_लिखो16(1, &card->dpram[DPRAM_FCT_PARAM + 12]);
	ioग_लिखो16(1, &card->dpram[DPRAM_FCT_PARAM + 14]);
	ioग_लिखो16(1, &card->dpram[DPRAM_FCT_PARAM + 16]);
	ioग_लिखो16(1, &card->dpram[DPRAM_FCT_PARAM + 18]);
	ioग_लिखो16(1, &card->dpram[DPRAM_FCT_PARAM + 20]);
	ret = softing_fct_cmd(card, 17, "initialize_interface");
	अगर (ret < 0)
		जाओ failed;
	/* enable_fअगरo */
	ret = softing_fct_cmd(card, 36, "enable_fifo");
	अगर (ret < 0)
		जाओ failed;
	/* enable fअगरo tx ack */
	ret = softing_fct_cmd(card, 13, "fifo_tx_ack[0]");
	अगर (ret < 0)
		जाओ failed;
	/* enable fअगरo tx ack2 */
	ret = softing_fct_cmd(card, 14, "fifo_tx_ack[1]");
	अगर (ret < 0)
		जाओ failed;
	/* start_chip */
	ret = softing_fct_cmd(card, 11, "start_chip");
	अगर (ret < 0)
		जाओ failed;
	ioग_लिखो8(0, &card->dpram[DPRAM_INFO_BUSSTATE]);
	ioग_लिखो8(0, &card->dpram[DPRAM_INFO_BUSSTATE2]);
	अगर (card->pdat->generation < 2) अणु
		ioग_लिखो8(0, &card->dpram[DPRAM_V2_IRQ_TOHOST]);
		/* flush the DPRAM caches */
		wmb();
	पूर्ण

	softing_initialize_बारtamp(card);

	/*
	 * करो socketcan notअगरications/status changes
	 * from here, no errors should occur, or the failed: part
	 * must be reviewed
	 */
	स_रखो(&msg, 0, माप(msg));
	msg.can_id = CAN_ERR_FLAG | CAN_ERR_RESTARTED;
	msg.len = CAN_ERR_DLC;
	क्रम (j = 0; j < ARRAY_SIZE(card->net); ++j) अणु
		अगर (!(bus_biपंचांगask_start & (1 << j)))
			जारी;
		netdev = card->net[j];
		अगर (!netdev)
			जारी;
		priv = netdev_priv(netdev);
		priv->can.state = CAN_STATE_ERROR_ACTIVE;
		खोलो_candev(netdev);
		अगर (dev != netdev) अणु
			/* notअगरy other buses on the restart */
			softing_netdev_rx(netdev, &msg, 0);
			++priv->can.can_stats.restarts;
		पूर्ण
		netअगर_wake_queue(netdev);
	पूर्ण

	/* enable पूर्णांकerrupts */
	ret = softing_enable_irq(card, 1);
	अगर (ret)
		जाओ failed;
card_करोne:
	mutex_unlock(&card->fw.lock);
	वापस 0;
invalid:
	ret = -EINVAL;
failed:
	softing_enable_irq(card, 0);
	softing_reset_chip(card);
	mutex_unlock(&card->fw.lock);
	/* bring all other पूर्णांकerfaces करोwn */
	क्रम (j = 0; j < ARRAY_SIZE(card->net); ++j) अणु
		netdev = card->net[j];
		अगर (!netdev)
			जारी;
		dev_बंद(netdev);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक softing_शेष_output(काष्ठा net_device *netdev)
अणु
	काष्ठा softing_priv *priv = netdev_priv(netdev);
	काष्ठा softing *card = priv->card;

	चयन (priv->chip) अणु
	हाल 1000:
		वापस (card->pdat->generation < 2) ? 0xfb : 0xfa;
	हाल 5:
		वापस 0x60;
	शेष:
		वापस 0x40;
	पूर्ण
पूर्ण
