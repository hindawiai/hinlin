<शैली गुरु>
/*
 * Copyright(c) 2015, 2016 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश <linux/delay.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "hfi.h"

/* क्रम the given bus number, वापस the CSR क्रम पढ़ोing an i2c line */
अटल अंतरभूत u32 i2c_in_csr(u32 bus_num)
अणु
	वापस bus_num ? ASIC_QSFP2_IN : ASIC_QSFP1_IN;
पूर्ण

/* क्रम the given bus number, वापस the CSR क्रम writing an i2c line */
अटल अंतरभूत u32 i2c_oe_csr(u32 bus_num)
अणु
	वापस bus_num ? ASIC_QSFP2_OE : ASIC_QSFP1_OE;
पूर्ण

अटल व्योम hfi1_setsda(व्योम *data, पूर्णांक state)
अणु
	काष्ठा hfi1_i2c_bus *bus = (काष्ठा hfi1_i2c_bus *)data;
	काष्ठा hfi1_devdata *dd = bus->controlling_dd;
	u64 reg;
	u32 target_oe;

	target_oe = i2c_oe_csr(bus->num);
	reg = पढ़ो_csr(dd, target_oe);
	/*
	 * The OE bit value is inverted and connected to the pin.  When
	 * OE is 0 the pin is left to be pulled up, when the OE is 1
	 * the pin is driven low.  This matches the "open drain" or "खोलो
	 * collector" convention.
	 */
	अगर (state)
		reg &= ~QSFP_HFI0_I2CDAT;
	अन्यथा
		reg |= QSFP_HFI0_I2CDAT;
	ग_लिखो_csr(dd, target_oe, reg);
	/* करो a पढ़ो to क्रमce the ग_लिखो पूर्णांकo the chip */
	(व्योम)पढ़ो_csr(dd, target_oe);
पूर्ण

अटल व्योम hfi1_setscl(व्योम *data, पूर्णांक state)
अणु
	काष्ठा hfi1_i2c_bus *bus = (काष्ठा hfi1_i2c_bus *)data;
	काष्ठा hfi1_devdata *dd = bus->controlling_dd;
	u64 reg;
	u32 target_oe;

	target_oe = i2c_oe_csr(bus->num);
	reg = पढ़ो_csr(dd, target_oe);
	/*
	 * The OE bit value is inverted and connected to the pin.  When
	 * OE is 0 the pin is left to be pulled up, when the OE is 1
	 * the pin is driven low.  This matches the "open drain" or "खोलो
	 * collector" convention.
	 */
	अगर (state)
		reg &= ~QSFP_HFI0_I2CCLK;
	अन्यथा
		reg |= QSFP_HFI0_I2CCLK;
	ग_लिखो_csr(dd, target_oe, reg);
	/* करो a पढ़ो to क्रमce the ग_लिखो पूर्णांकo the chip */
	(व्योम)पढ़ो_csr(dd, target_oe);
पूर्ण

अटल पूर्णांक hfi1_माला_लोda(व्योम *data)
अणु
	काष्ठा hfi1_i2c_bus *bus = (काष्ठा hfi1_i2c_bus *)data;
	u64 reg;
	u32 target_in;

	hfi1_setsda(data, 1);	/* clear OE so we करो not pull line करोwn */
	udelay(2);		/* 1us pull up + 250ns hold */

	target_in = i2c_in_csr(bus->num);
	reg = पढ़ो_csr(bus->controlling_dd, target_in);
	वापस !!(reg & QSFP_HFI0_I2CDAT);
पूर्ण

अटल पूर्णांक hfi1_माला_लोcl(व्योम *data)
अणु
	काष्ठा hfi1_i2c_bus *bus = (काष्ठा hfi1_i2c_bus *)data;
	u64 reg;
	u32 target_in;

	hfi1_setscl(data, 1);	/* clear OE so we करो not pull line करोwn */
	udelay(2);		/* 1us pull up + 250ns hold */

	target_in = i2c_in_csr(bus->num);
	reg = पढ़ो_csr(bus->controlling_dd, target_in);
	वापस !!(reg & QSFP_HFI0_I2CCLK);
पूर्ण

/*
 * Allocate and initialize the given i2c bus number.
 * Returns शून्य on failure.
 */
अटल काष्ठा hfi1_i2c_bus *init_i2c_bus(काष्ठा hfi1_devdata *dd,
					 काष्ठा hfi1_asic_data *ad, पूर्णांक num)
अणु
	काष्ठा hfi1_i2c_bus *bus;
	पूर्णांक ret;

	bus = kzalloc(माप(*bus), GFP_KERNEL);
	अगर (!bus)
		वापस शून्य;

	bus->controlling_dd = dd;
	bus->num = num;	/* our bus number */

	bus->algo.setsda = hfi1_setsda;
	bus->algo.setscl = hfi1_setscl;
	bus->algo.माला_लोda = hfi1_माला_लोda;
	bus->algo.माला_लोcl = hfi1_माला_लोcl;
	bus->algo.udelay = 5;
	bus->algo.समयout = usecs_to_jअगरfies(100000);
	bus->algo.data = bus;

	bus->adapter.owner = THIS_MODULE;
	bus->adapter.algo_data = &bus->algo;
	bus->adapter.dev.parent = &dd->pcidev->dev;
	snम_लिखो(bus->adapter.name, माप(bus->adapter.name),
		 "hfi1_i2c%d", num);

	ret = i2c_bit_add_bus(&bus->adapter);
	अगर (ret) अणु
		dd_dev_info(dd, "%s: unable to add i2c bus %d, err %d\n",
			    __func__, num, ret);
		kमुक्त(bus);
		वापस शून्य;
	पूर्ण

	वापस bus;
पूर्ण

/*
 * Initialize i2c buses.
 * Return 0 on success, -त्रुटि_सं on error.
 */
पूर्णांक set_up_i2c(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_asic_data *ad)
अणु
	ad->i2c_bus0 = init_i2c_bus(dd, ad, 0);
	ad->i2c_bus1 = init_i2c_bus(dd, ad, 1);
	अगर (!ad->i2c_bus0 || !ad->i2c_bus1)
		वापस -ENOMEM;
	वापस 0;
पूर्ण;

अटल व्योम clean_i2c_bus(काष्ठा hfi1_i2c_bus *bus)
अणु
	अगर (bus) अणु
		i2c_del_adapter(&bus->adapter);
		kमुक्त(bus);
	पूर्ण
पूर्ण

व्योम clean_up_i2c(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_asic_data *ad)
अणु
	अगर (!ad)
		वापस;
	clean_i2c_bus(ad->i2c_bus0);
	ad->i2c_bus0 = शून्य;
	clean_i2c_bus(ad->i2c_bus1);
	ad->i2c_bus1 = शून्य;
पूर्ण

अटल पूर्णांक i2c_bus_ग_लिखो(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_i2c_bus *i2c,
			 u8 slave_addr, पूर्णांक offset, पूर्णांक offset_size,
			 u8 *data, u16 len)
अणु
	पूर्णांक ret;
	पूर्णांक num_msgs;
	u8 offset_bytes[2];
	काष्ठा i2c_msg msgs[2];

	चयन (offset_size) अणु
	हाल 0:
		num_msgs = 1;
		msgs[0].addr = slave_addr;
		msgs[0].flags = 0;
		msgs[0].len = len;
		msgs[0].buf = data;
		अवरोध;
	हाल 2:
		offset_bytes[1] = (offset >> 8) & 0xff;
		fallthrough;
	हाल 1:
		num_msgs = 2;
		offset_bytes[0] = offset & 0xff;

		msgs[0].addr = slave_addr;
		msgs[0].flags = 0;
		msgs[0].len = offset_size;
		msgs[0].buf = offset_bytes;

		msgs[1].addr = slave_addr;
		msgs[1].flags = I2C_M_NOSTART;
		msgs[1].len = len;
		msgs[1].buf = data;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	i2c->controlling_dd = dd;
	ret = i2c_transfer(&i2c->adapter, msgs, num_msgs);
	अगर (ret != num_msgs) अणु
		dd_dev_err(dd, "%s: bus %d, i2c slave 0x%x, offset 0x%x, len 0x%x; write failed, ret %d\n",
			   __func__, i2c->num, slave_addr, offset, len, ret);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक i2c_bus_पढ़ो(काष्ठा hfi1_devdata *dd, काष्ठा hfi1_i2c_bus *bus,
			u8 slave_addr, पूर्णांक offset, पूर्णांक offset_size,
			u8 *data, u16 len)
अणु
	पूर्णांक ret;
	पूर्णांक num_msgs;
	u8 offset_bytes[2];
	काष्ठा i2c_msg msgs[2];

	चयन (offset_size) अणु
	हाल 0:
		num_msgs = 1;
		msgs[0].addr = slave_addr;
		msgs[0].flags = I2C_M_RD;
		msgs[0].len = len;
		msgs[0].buf = data;
		अवरोध;
	हाल 2:
		offset_bytes[1] = (offset >> 8) & 0xff;
		fallthrough;
	हाल 1:
		num_msgs = 2;
		offset_bytes[0] = offset & 0xff;

		msgs[0].addr = slave_addr;
		msgs[0].flags = 0;
		msgs[0].len = offset_size;
		msgs[0].buf = offset_bytes;

		msgs[1].addr = slave_addr;
		msgs[1].flags = I2C_M_RD;
		msgs[1].len = len;
		msgs[1].buf = data;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	bus->controlling_dd = dd;
	ret = i2c_transfer(&bus->adapter, msgs, num_msgs);
	अगर (ret != num_msgs) अणु
		dd_dev_err(dd, "%s: bus %d, i2c slave 0x%x, offset 0x%x, len 0x%x; read failed, ret %d\n",
			   __func__, bus->num, slave_addr, offset, len, ret);
		वापस ret < 0 ? ret : -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Raw i2c ग_लिखो.  No set-up or lock checking.
 *
 * Return 0 on success, -त्रुटि_सं on error.
 */
अटल पूर्णांक __i2c_ग_लिखो(काष्ठा hfi1_pportdata *ppd, u32 target, पूर्णांक i2c_addr,
		       पूर्णांक offset, व्योम *bp, पूर्णांक len)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	काष्ठा hfi1_i2c_bus *bus;
	u8 slave_addr;
	पूर्णांक offset_size;

	bus = target ? dd->asic_data->i2c_bus1 : dd->asic_data->i2c_bus0;
	slave_addr = (i2c_addr & 0xff) >> 1; /* convert to 7-bit addr */
	offset_size = (i2c_addr >> 8) & 0x3;
	वापस i2c_bus_ग_लिखो(dd, bus, slave_addr, offset, offset_size, bp, len);
पूर्ण

/*
 * Caller must hold the i2c chain resource.
 *
 * Return number of bytes written, or -त्रुटि_सं.
 */
पूर्णांक i2c_ग_लिखो(काष्ठा hfi1_pportdata *ppd, u32 target, पूर्णांक i2c_addr, पूर्णांक offset,
	      व्योम *bp, पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर (!check_chip_resource(ppd->dd, i2c_target(target), __func__))
		वापस -EACCES;

	ret = __i2c_ग_लिखो(ppd, target, i2c_addr, offset, bp, len);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

/*
 * Raw i2c पढ़ो.  No set-up or lock checking.
 *
 * Return 0 on success, -त्रुटि_सं on error.
 */
अटल पूर्णांक __i2c_पढ़ो(काष्ठा hfi1_pportdata *ppd, u32 target, पूर्णांक i2c_addr,
		      पूर्णांक offset, व्योम *bp, पूर्णांक len)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	काष्ठा hfi1_i2c_bus *bus;
	u8 slave_addr;
	पूर्णांक offset_size;

	bus = target ? dd->asic_data->i2c_bus1 : dd->asic_data->i2c_bus0;
	slave_addr = (i2c_addr & 0xff) >> 1; /* convert to 7-bit addr */
	offset_size = (i2c_addr >> 8) & 0x3;
	वापस i2c_bus_पढ़ो(dd, bus, slave_addr, offset, offset_size, bp, len);
पूर्ण

/*
 * Caller must hold the i2c chain resource.
 *
 * Return number of bytes पढ़ो, or -त्रुटि_सं.
 */
पूर्णांक i2c_पढ़ो(काष्ठा hfi1_pportdata *ppd, u32 target, पूर्णांक i2c_addr, पूर्णांक offset,
	     व्योम *bp, पूर्णांक len)
अणु
	पूर्णांक ret;

	अगर (!check_chip_resource(ppd->dd, i2c_target(target), __func__))
		वापस -EACCES;

	ret = __i2c_पढ़ो(ppd, target, i2c_addr, offset, bp, len);
	अगर (ret)
		वापस ret;

	वापस len;
पूर्ण

/*
 * Write page n, offset m of QSFP memory as defined by SFF 8636
 * by writing @addr = ((256 * n) + m)
 *
 * Caller must hold the i2c chain resource.
 *
 * Return number of bytes written or -त्रुटि_सं.
 */
पूर्णांक qsfp_ग_लिखो(काष्ठा hfi1_pportdata *ppd, u32 target, पूर्णांक addr, व्योम *bp,
	       पूर्णांक len)
अणु
	पूर्णांक count = 0;
	पूर्णांक offset;
	पूर्णांक nग_लिखो;
	पूर्णांक ret = 0;
	u8 page;

	अगर (!check_chip_resource(ppd->dd, i2c_target(target), __func__))
		वापस -EACCES;

	जबतक (count < len) अणु
		/*
		 * Set the qsfp page based on a zero-based address
		 * and a page size of QSFP_PAGESIZE bytes.
		 */
		page = (u8)(addr / QSFP_PAGESIZE);

		ret = __i2c_ग_लिखो(ppd, target, QSFP_DEV | QSFP_OFFSET_SIZE,
				  QSFP_PAGE_SELECT_BYTE_OFFS, &page, 1);
		/* QSFPs require a 5-10msec delay after ग_लिखो operations */
		mdelay(5);
		अगर (ret) अणु
			hfi1_dev_porterr(ppd->dd, ppd->port,
					 "QSFP chain %d can't write QSFP_PAGE_SELECT_BYTE: %d\n",
					 target, ret);
			अवरोध;
		पूर्ण

		offset = addr % QSFP_PAGESIZE;
		nग_लिखो = len - count;
		/* truncate ग_लिखो to boundary अगर crossing boundary */
		अगर (((addr % QSFP_RW_BOUNDARY) + nग_लिखो) > QSFP_RW_BOUNDARY)
			nग_लिखो = QSFP_RW_BOUNDARY - (addr % QSFP_RW_BOUNDARY);

		ret = __i2c_ग_लिखो(ppd, target, QSFP_DEV | QSFP_OFFSET_SIZE,
				  offset, bp + count, nग_लिखो);
		/* QSFPs require a 5-10msec delay after ग_लिखो operations */
		mdelay(5);
		अगर (ret)	/* stop on error */
			अवरोध;

		count += nग_लिखो;
		addr += nग_लिखो;
	पूर्ण

	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

/*
 * Perक्रमm a stand-alone single QSFP ग_लिखो.  Acquire the resource, करो the
 * ग_लिखो, then release the resource.
 */
पूर्णांक one_qsfp_ग_लिखो(काष्ठा hfi1_pportdata *ppd, u32 target, पूर्णांक addr, व्योम *bp,
		   पूर्णांक len)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u32 resource = qsfp_resource(dd);
	पूर्णांक ret;

	ret = acquire_chip_resource(dd, resource, QSFP_WAIT);
	अगर (ret)
		वापस ret;
	ret = qsfp_ग_लिखो(ppd, target, addr, bp, len);
	release_chip_resource(dd, resource);

	वापस ret;
पूर्ण

/*
 * Access page n, offset m of QSFP memory as defined by SFF 8636
 * by पढ़ोing @addr = ((256 * n) + m)
 *
 * Caller must hold the i2c chain resource.
 *
 * Return the number of bytes पढ़ो or -त्रुटि_सं.
 */
पूर्णांक qsfp_पढ़ो(काष्ठा hfi1_pportdata *ppd, u32 target, पूर्णांक addr, व्योम *bp,
	      पूर्णांक len)
अणु
	पूर्णांक count = 0;
	पूर्णांक offset;
	पूर्णांक nपढ़ो;
	पूर्णांक ret = 0;
	u8 page;

	अगर (!check_chip_resource(ppd->dd, i2c_target(target), __func__))
		वापस -EACCES;

	जबतक (count < len) अणु
		/*
		 * Set the qsfp page based on a zero-based address
		 * and a page size of QSFP_PAGESIZE bytes.
		 */
		page = (u8)(addr / QSFP_PAGESIZE);
		ret = __i2c_ग_लिखो(ppd, target, QSFP_DEV | QSFP_OFFSET_SIZE,
				  QSFP_PAGE_SELECT_BYTE_OFFS, &page, 1);
		/* QSFPs require a 5-10msec delay after ग_लिखो operations */
		mdelay(5);
		अगर (ret) अणु
			hfi1_dev_porterr(ppd->dd, ppd->port,
					 "QSFP chain %d can't write QSFP_PAGE_SELECT_BYTE: %d\n",
					 target, ret);
			अवरोध;
		पूर्ण

		offset = addr % QSFP_PAGESIZE;
		nपढ़ो = len - count;
		/* truncate पढ़ो to boundary अगर crossing boundary */
		अगर (((addr % QSFP_RW_BOUNDARY) + nपढ़ो) > QSFP_RW_BOUNDARY)
			nपढ़ो = QSFP_RW_BOUNDARY - (addr % QSFP_RW_BOUNDARY);

		ret = __i2c_पढ़ो(ppd, target, QSFP_DEV | QSFP_OFFSET_SIZE,
				 offset, bp + count, nपढ़ो);
		अगर (ret)	/* stop on error */
			अवरोध;

		count += nपढ़ो;
		addr += nपढ़ो;
	पूर्ण

	अगर (ret < 0)
		वापस ret;
	वापस count;
पूर्ण

/*
 * Perक्रमm a stand-alone single QSFP पढ़ो.  Acquire the resource, करो the
 * पढ़ो, then release the resource.
 */
पूर्णांक one_qsfp_पढ़ो(काष्ठा hfi1_pportdata *ppd, u32 target, पूर्णांक addr, व्योम *bp,
		  पूर्णांक len)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u32 resource = qsfp_resource(dd);
	पूर्णांक ret;

	ret = acquire_chip_resource(dd, resource, QSFP_WAIT);
	अगर (ret)
		वापस ret;
	ret = qsfp_पढ़ो(ppd, target, addr, bp, len);
	release_chip_resource(dd, resource);

	वापस ret;
पूर्ण

/*
 * This function caches the QSFP memory range in 128 byte chunks.
 * As an example, the next byte after address 255 is byte 128 from
 * upper page 01H (अगर existing) rather than byte 0 from lower page 00H.
 * Access page n, offset m of QSFP memory as defined by SFF 8636
 * in the cache by पढ़ोing byte ((128 * n) + m)
 * The calls to qsfp_अणुपढ़ो,ग_लिखोपूर्ण in this function correctly handle the
 * address map dअगरference between this mapping and the mapping implemented
 * by those functions
 *
 * The caller must be holding the QSFP i2c chain resource.
 */
पूर्णांक refresh_qsfp_cache(काष्ठा hfi1_pportdata *ppd, काष्ठा qsfp_data *cp)
अणु
	u32 target = ppd->dd->hfi1_id;
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;
	u8 *cache = &cp->cache[0];

	/* ensure sane contents on invalid पढ़ोs, क्रम cable swaps */
	स_रखो(cache, 0, (QSFP_MAX_NUM_PAGES * 128));
	spin_lock_irqsave(&ppd->qsfp_info.qsfp_lock, flags);
	ppd->qsfp_info.cache_valid = 0;
	spin_unlock_irqrestore(&ppd->qsfp_info.qsfp_lock, flags);

	अगर (!qsfp_mod_present(ppd)) अणु
		ret = -ENODEV;
		जाओ bail;
	पूर्ण

	ret = qsfp_पढ़ो(ppd, target, 0, cache, QSFP_PAGESIZE);
	अगर (ret != QSFP_PAGESIZE) अणु
		dd_dev_info(ppd->dd,
			    "%s: Page 0 read failed, expected %d, got %d\n",
			    __func__, QSFP_PAGESIZE, ret);
		जाओ bail;
	पूर्ण

	/* Is paging enabled? */
	अगर (!(cache[2] & 4)) अणु
		/* Paging enabled, page 03 required */
		अगर ((cache[195] & 0xC0) == 0xC0) अणु
			/* all */
			ret = qsfp_पढ़ो(ppd, target, 384, cache + 256, 128);
			अगर (ret <= 0 || ret != 128) अणु
				dd_dev_info(ppd->dd, "%s failed\n", __func__);
				जाओ bail;
			पूर्ण
			ret = qsfp_पढ़ो(ppd, target, 640, cache + 384, 128);
			अगर (ret <= 0 || ret != 128) अणु
				dd_dev_info(ppd->dd, "%s failed\n", __func__);
				जाओ bail;
			पूर्ण
			ret = qsfp_पढ़ो(ppd, target, 896, cache + 512, 128);
			अगर (ret <= 0 || ret != 128) अणु
				dd_dev_info(ppd->dd, "%s failed\n", __func__);
				जाओ bail;
			पूर्ण
		पूर्ण अन्यथा अगर ((cache[195] & 0x80) == 0x80) अणु
			/* only page 2 and 3 */
			ret = qsfp_पढ़ो(ppd, target, 640, cache + 384, 128);
			अगर (ret <= 0 || ret != 128) अणु
				dd_dev_info(ppd->dd, "%s failed\n", __func__);
				जाओ bail;
			पूर्ण
			ret = qsfp_पढ़ो(ppd, target, 896, cache + 512, 128);
			अगर (ret <= 0 || ret != 128) अणु
				dd_dev_info(ppd->dd, "%s failed\n", __func__);
				जाओ bail;
			पूर्ण
		पूर्ण अन्यथा अगर ((cache[195] & 0x40) == 0x40) अणु
			/* only page 1 and 3 */
			ret = qsfp_पढ़ो(ppd, target, 384, cache + 256, 128);
			अगर (ret <= 0 || ret != 128) अणु
				dd_dev_info(ppd->dd, "%s failed\n", __func__);
				जाओ bail;
			पूर्ण
			ret = qsfp_पढ़ो(ppd, target, 896, cache + 512, 128);
			अगर (ret <= 0 || ret != 128) अणु
				dd_dev_info(ppd->dd, "%s failed\n", __func__);
				जाओ bail;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* only page 3 */
			ret = qsfp_पढ़ो(ppd, target, 896, cache + 512, 128);
			अगर (ret <= 0 || ret != 128) अणु
				dd_dev_info(ppd->dd, "%s failed\n", __func__);
				जाओ bail;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&ppd->qsfp_info.qsfp_lock, flags);
	ppd->qsfp_info.cache_valid = 1;
	ppd->qsfp_info.cache_refresh_required = 0;
	spin_unlock_irqrestore(&ppd->qsfp_info.qsfp_lock, flags);

	वापस 0;

bail:
	स_रखो(cache, 0, (QSFP_MAX_NUM_PAGES * 128));
	वापस ret;
पूर्ण

स्थिर अक्षर * स्थिर hfi1_qsfp_devtech[16] = अणु
	"850nm VCSEL", "1310nm VCSEL", "1550nm VCSEL", "1310nm FP",
	"1310nm DFB", "1550nm DFB", "1310nm EML", "1550nm EML",
	"Cu Misc", "1490nm DFB", "Cu NoEq", "Cu Eq",
	"Undef", "Cu Active BothEq", "Cu FarEq", "Cu NearEq"
पूर्ण;

#घोषणा QSFP_DUMP_CHUNK 16 /* Holds दीर्घest string */
#घोषणा QSFP_DEFAULT_HDR_CNT 224

#घोषणा QSFP_PWR(pbyte) (((pbyte) >> 6) & 3)
#घोषणा QSFP_HIGH_PWR(pbyte) ((pbyte) & 3)
/* For use with QSFP_HIGH_PWR macro */
#घोषणा QSFP_HIGH_PWR_UNUSED	0 /* Bits [1:0] = 00 implies low घातer module */

/*
 * Takes घातer class byte [Page 00 Byte 129] in SFF 8636
 * Returns घातer class as पूर्णांकeger (1 through 7, per SFF 8636 rev 2.4)
 */
पूर्णांक get_qsfp_घातer_class(u8 घातer_byte)
अणु
	अगर (QSFP_HIGH_PWR(घातer_byte) == QSFP_HIGH_PWR_UNUSED)
		/* घातer classes count from 1, their bit encodings from 0 */
		वापस (QSFP_PWR(घातer_byte) + 1);
	/*
	 * 00 in the high घातer classes stands क्रम unused, bringing
	 * balance to the off-by-1 offset above, we add 4 here to
	 * account क्रम the dअगरference between the low and high घातer
	 * groups
	 */
	वापस (QSFP_HIGH_PWR(घातer_byte) + 4);
पूर्ण

पूर्णांक qsfp_mod_present(काष्ठा hfi1_pportdata *ppd)
अणु
	काष्ठा hfi1_devdata *dd = ppd->dd;
	u64 reg;

	reg = पढ़ो_csr(dd, dd->hfi1_id ? ASIC_QSFP2_IN : ASIC_QSFP1_IN);
	वापस !(reg & QSFP_HFI0_MODPRST_N);
पूर्ण

/*
 * This function maps QSFP memory addresses in 128 byte chunks in the following
 * fashion per the CableInfo SMA query definition in the IBA 1.3 spec/OPA Gen 1
 * spec
 * For addr 000-127, lower page 00h
 * For addr 128-255, upper page 00h
 * For addr 256-383, upper page 01h
 * For addr 384-511, upper page 02h
 * For addr 512-639, upper page 03h
 *
 * For addresses beyond this range, it वापसs the invalid range of data buffer
 * set to 0.
 * For upper pages that are optional, अगर they are not valid, वापसs the
 * particular range of bytes in the data buffer set to 0.
 */
पूर्णांक get_cable_info(काष्ठा hfi1_devdata *dd, u32 port_num, u32 addr, u32 len,
		   u8 *data)
अणु
	काष्ठा hfi1_pportdata *ppd;
	u32 excess_len = len;
	पूर्णांक ret = 0, offset = 0;

	अगर (port_num > dd->num_pports || port_num < 1) अणु
		dd_dev_info(dd, "%s: Invalid port number %d\n",
			    __func__, port_num);
		ret = -EINVAL;
		जाओ set_zeroes;
	पूर्ण

	ppd = dd->pport + (port_num - 1);
	अगर (!qsfp_mod_present(ppd)) अणु
		ret = -ENODEV;
		जाओ set_zeroes;
	पूर्ण

	अगर (!ppd->qsfp_info.cache_valid) अणु
		ret = -EINVAL;
		जाओ set_zeroes;
	पूर्ण

	अगर (addr >= (QSFP_MAX_NUM_PAGES * 128)) अणु
		ret = -दुस्फल;
		जाओ set_zeroes;
	पूर्ण

	अगर ((addr + len) > (QSFP_MAX_NUM_PAGES * 128)) अणु
		excess_len = (addr + len) - (QSFP_MAX_NUM_PAGES * 128);
		स_नकल(data, &ppd->qsfp_info.cache[addr], (len - excess_len));
		data += (len - excess_len);
		जाओ set_zeroes;
	पूर्ण

	स_नकल(data, &ppd->qsfp_info.cache[addr], len);

	अगर (addr <= QSFP_MONITOR_VAL_END &&
	    (addr + len) >= QSFP_MONITOR_VAL_START) अणु
		/* Overlap with the dynamic channel monitor range */
		अगर (addr < QSFP_MONITOR_VAL_START) अणु
			अगर (addr + len <= QSFP_MONITOR_VAL_END)
				len = addr + len - QSFP_MONITOR_VAL_START;
			अन्यथा
				len = QSFP_MONITOR_RANGE;
			offset = QSFP_MONITOR_VAL_START - addr;
			addr = QSFP_MONITOR_VAL_START;
		पूर्ण अन्यथा अगर (addr == QSFP_MONITOR_VAL_START) अणु
			offset = 0;
			अगर (addr + len > QSFP_MONITOR_VAL_END)
				len = QSFP_MONITOR_RANGE;
		पूर्ण अन्यथा अणु
			offset = 0;
			अगर (addr + len > QSFP_MONITOR_VAL_END)
				len = QSFP_MONITOR_VAL_END - addr + 1;
		पूर्ण
		/* Refresh the values of the dynamic monitors from the cable */
		ret = one_qsfp_पढ़ो(ppd, dd->hfi1_id, addr, data + offset, len);
		अगर (ret != len) अणु
			ret = -EAGAIN;
			जाओ set_zeroes;
		पूर्ण
	पूर्ण

	वापस 0;

set_zeroes:
	स_रखो(data, 0, excess_len);
	वापस ret;
पूर्ण

अटल स्थिर अक्षर *pwr_codes[8] = अणु"N/AW",
				  "1.5W",
				  "2.0W",
				  "2.5W",
				  "3.5W",
				  "4.0W",
				  "4.5W",
				  "5.0W"
				 पूर्ण;

पूर्णांक qsfp_dump(काष्ठा hfi1_pportdata *ppd, अक्षर *buf, पूर्णांक len)
अणु
	u8 *cache = &ppd->qsfp_info.cache[0];
	u8 bin_buff[QSFP_DUMP_CHUNK];
	अक्षर lenstr[6];
	पूर्णांक sofar;
	पूर्णांक bidx = 0;
	u8 *atten = &cache[QSFP_ATTEN_OFFS];
	u8 *venकरोr_oui = &cache[QSFP_VOUI_OFFS];
	u8 घातer_byte = 0;

	sofar = 0;
	lenstr[0] = ' ';
	lenstr[1] = '\0';

	अगर (ppd->qsfp_info.cache_valid) अणु
		अगर (QSFP_IS_CU(cache[QSFP_MOD_TECH_OFFS]))
			snम_लिखो(lenstr, माप(lenstr), "%dM ",
				 cache[QSFP_MOD_LEN_OFFS]);

		घातer_byte = cache[QSFP_MOD_PWR_OFFS];
		sofar += scnम_लिखो(buf + sofar, len - sofar, "PWR:%.3sW\n",
				pwr_codes[get_qsfp_घातer_class(घातer_byte)]);

		sofar += scnम_लिखो(buf + sofar, len - sofar, "TECH:%s%s\n",
				lenstr,
			hfi1_qsfp_devtech[(cache[QSFP_MOD_TECH_OFFS]) >> 4]);

		sofar += scnम_लिखो(buf + sofar, len - sofar, "Vendor:%.*s\n",
				   QSFP_VEND_LEN, &cache[QSFP_VEND_OFFS]);

		sofar += scnम_लिखो(buf + sofar, len - sofar, "OUI:%06X\n",
				   QSFP_OUI(venकरोr_oui));

		sofar += scnम_लिखो(buf + sofar, len - sofar, "Part#:%.*s\n",
				   QSFP_PN_LEN, &cache[QSFP_PN_OFFS]);

		sofar += scnम_लिखो(buf + sofar, len - sofar, "Rev:%.*s\n",
				   QSFP_REV_LEN, &cache[QSFP_REV_OFFS]);

		अगर (QSFP_IS_CU(cache[QSFP_MOD_TECH_OFFS]))
			sofar += scnम_लिखो(buf + sofar, len - sofar,
				"Atten:%d, %d\n",
				QSFP_ATTEN_SDR(atten),
				QSFP_ATTEN_DDR(atten));

		sofar += scnम_लिखो(buf + sofar, len - sofar, "Serial:%.*s\n",
				   QSFP_SN_LEN, &cache[QSFP_SN_OFFS]);

		sofar += scnम_लिखो(buf + sofar, len - sofar, "Date:%.*s\n",
				   QSFP_DATE_LEN, &cache[QSFP_DATE_OFFS]);

		sofar += scnम_लिखो(buf + sofar, len - sofar, "Lot:%.*s\n",
				   QSFP_LOT_LEN, &cache[QSFP_LOT_OFFS]);

		जबतक (bidx < QSFP_DEFAULT_HDR_CNT) अणु
			पूर्णांक iidx;

			स_नकल(bin_buff, &cache[bidx], QSFP_DUMP_CHUNK);
			क्रम (iidx = 0; iidx < QSFP_DUMP_CHUNK; ++iidx) अणु
				sofar += scnम_लिखो(buf + sofar, len - sofar,
					" %02X", bin_buff[iidx]);
			पूर्ण
			sofar += scnम_लिखो(buf + sofar, len - sofar, "\n");
			bidx += QSFP_DUMP_CHUNK;
		पूर्ण
	पूर्ण
	वापस sofar;
पूर्ण
