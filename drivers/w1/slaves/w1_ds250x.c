<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * w1_ds250x.c - w1 family 09/0b/89/91 (DS250x) driver
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>
#समावेश <linux/types.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/crc16.h>

#समावेश <linux/w1.h>
#समावेश <linux/nvmem-provider.h>

#घोषणा W1_DS2501_UNW_FAMILY    0x91
#घोषणा W1_DS2501_SIZE          64

#घोषणा W1_DS2502_FAMILY        0x09
#घोषणा W1_DS2502_UNW_FAMILY    0x89
#घोषणा W1_DS2502_SIZE          128

#घोषणा W1_DS2505_FAMILY	0x0b
#घोषणा W1_DS2505_SIZE		2048

#घोषणा W1_PAGE_SIZE		32

#घोषणा W1_EXT_READ_MEMORY	0xA5
#घोषणा W1_READ_DATA_CRC        0xC3

#घोषणा OFF2PG(off)	((off) / W1_PAGE_SIZE)

#घोषणा CRC16_INIT		0
#घोषणा CRC16_VALID		0xb001

काष्ठा w1_eprom_data अणु
	माप_प्रकार size;
	पूर्णांक (*पढ़ो)(काष्ठा w1_slave *sl, पूर्णांक pageno);
	u8 eprom[W1_DS2505_SIZE];
	DECLARE_BITMAP(page_present, W1_DS2505_SIZE / W1_PAGE_SIZE);
	अक्षर nvmem_name[64];
पूर्ण;

अटल पूर्णांक w1_ds2502_पढ़ो_page(काष्ठा w1_slave *sl, पूर्णांक pageno)
अणु
	काष्ठा w1_eprom_data *data = sl->family_data;
	पूर्णांक pgoff = pageno * W1_PAGE_SIZE;
	पूर्णांक ret = -EIO;
	u8 buf[3];
	u8 crc8;

	अगर (test_bit(pageno, data->page_present))
		वापस 0; /* page alपढ़ोy present */

	mutex_lock(&sl->master->bus_mutex);

	अगर (w1_reset_select_slave(sl))
		जाओ err;

	buf[0] = W1_READ_DATA_CRC;
	buf[1] = pgoff & 0xff;
	buf[2] = pgoff >> 8;
	w1_ग_लिखो_block(sl->master, buf, 3);

	crc8 = w1_पढ़ो_8(sl->master);
	अगर (w1_calc_crc8(buf, 3) != crc8)
		जाओ err;

	w1_पढ़ो_block(sl->master, &data->eprom[pgoff], W1_PAGE_SIZE);

	crc8 = w1_पढ़ो_8(sl->master);
	अगर (w1_calc_crc8(&data->eprom[pgoff], W1_PAGE_SIZE) != crc8)
		जाओ err;

	set_bit(pageno, data->page_present); /* mark page present */
	ret = 0;
err:
	mutex_unlock(&sl->master->bus_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक w1_ds2505_पढ़ो_page(काष्ठा w1_slave *sl, पूर्णांक pageno)
अणु
	काष्ठा w1_eprom_data *data = sl->family_data;
	पूर्णांक redir_retries = 16;
	पूर्णांक pgoff, epoff;
	पूर्णांक ret = -EIO;
	u8 buf[6];
	u8 redir;
	u16 crc;

	अगर (test_bit(pageno, data->page_present))
		वापस 0; /* page alपढ़ोy present */

	epoff = pgoff = pageno * W1_PAGE_SIZE;
	mutex_lock(&sl->master->bus_mutex);

retry:
	अगर (w1_reset_select_slave(sl))
		जाओ err;

	buf[0] = W1_EXT_READ_MEMORY;
	buf[1] = pgoff & 0xff;
	buf[2] = pgoff >> 8;
	w1_ग_लिखो_block(sl->master, buf, 3);
	w1_पढ़ो_block(sl->master, buf + 3, 3); /* redir, crc16 */
	redir = buf[3];
	crc = crc16(CRC16_INIT, buf, 6);

	अगर (crc != CRC16_VALID)
		जाओ err;


	अगर (redir != 0xff) अणु
		redir_retries--;
		अगर (redir_retries < 0)
			जाओ err;

		pgoff = (redir ^ 0xff) * W1_PAGE_SIZE;
		जाओ retry;
	पूर्ण

	w1_पढ़ो_block(sl->master, &data->eprom[epoff], W1_PAGE_SIZE);
	w1_पढ़ो_block(sl->master, buf, 2); /* crc16 */
	crc = crc16(CRC16_INIT, &data->eprom[epoff], W1_PAGE_SIZE);
	crc = crc16(crc, buf, 2);

	अगर (crc != CRC16_VALID)
		जाओ err;

	set_bit(pageno, data->page_present);
	ret = 0;
err:
	mutex_unlock(&sl->master->bus_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक w1_nvmem_पढ़ो(व्योम *priv, अचिन्हित पूर्णांक off, व्योम *buf, माप_प्रकार count)
अणु
	काष्ठा w1_slave *sl = priv;
	काष्ठा w1_eprom_data *data = sl->family_data;
	माप_प्रकार eprom_size = data->size;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (off > eprom_size)
		वापस -EINVAL;

	अगर ((off + count) > eprom_size)
		count = eprom_size - off;

	i = OFF2PG(off);
	करो अणु
		ret = data->पढ़ो(sl, i++);
		अगर (ret < 0)
			वापस ret;
	पूर्ण जबतक (i < OFF2PG(off + count));

	स_नकल(buf, &data->eprom[off], count);
	वापस 0;
पूर्ण

अटल पूर्णांक w1_eprom_add_slave(काष्ठा w1_slave *sl)
अणु
	काष्ठा w1_eprom_data *data;
	काष्ठा nvmem_device *nvmem;
	काष्ठा nvmem_config nvmem_cfg = अणु
		.dev = &sl->dev,
		.reg_पढ़ो = w1_nvmem_पढ़ो,
		.type = NVMEM_TYPE_OTP,
		.पढ़ो_only = true,
		.word_size = 1,
		.priv = sl,
		.id = -1
	पूर्ण;

	data = devm_kzalloc(&sl->dev, माप(काष्ठा w1_eprom_data), GFP_KERNEL);
	अगर (!data)
		वापस -ENOMEM;

	sl->family_data = data;
	चयन (sl->family->fid) अणु
	हाल W1_DS2501_UNW_FAMILY:
		data->size = W1_DS2501_SIZE;
		data->पढ़ो = w1_ds2502_पढ़ो_page;
		अवरोध;
	हाल W1_DS2502_FAMILY:
	हाल W1_DS2502_UNW_FAMILY:
		data->size = W1_DS2502_SIZE;
		data->पढ़ो = w1_ds2502_पढ़ो_page;
		अवरोध;
	हाल W1_DS2505_FAMILY:
		data->size = W1_DS2505_SIZE;
		data->पढ़ो = w1_ds2505_पढ़ो_page;
		अवरोध;
	पूर्ण

	अगर (sl->master->bus_master->dev_id)
		snम_लिखो(data->nvmem_name, माप(data->nvmem_name),
			 "%s-%02x-%012llx",
			 sl->master->bus_master->dev_id, sl->reg_num.family,
			 (अचिन्हित दीर्घ दीर्घ)sl->reg_num.id);
	अन्यथा
		snम_लिखो(data->nvmem_name, माप(data->nvmem_name),
			 "%02x-%012llx",
			 sl->reg_num.family,
			 (अचिन्हित दीर्घ दीर्घ)sl->reg_num.id);

	nvmem_cfg.name = data->nvmem_name;
	nvmem_cfg.size = data->size;

	nvmem = devm_nvmem_रेजिस्टर(&sl->dev, &nvmem_cfg);
	वापस PTR_ERR_OR_ZERO(nvmem);
पूर्ण

अटल स्थिर काष्ठा w1_family_ops w1_eprom_fops = अणु
	.add_slave	= w1_eprom_add_slave,
पूर्ण;

अटल काष्ठा w1_family w1_family_09 = अणु
	.fid = W1_DS2502_FAMILY,
	.fops = &w1_eprom_fops,
पूर्ण;

अटल काष्ठा w1_family w1_family_0b = अणु
	.fid = W1_DS2505_FAMILY,
	.fops = &w1_eprom_fops,
पूर्ण;

अटल काष्ठा w1_family w1_family_89 = अणु
	.fid = W1_DS2502_UNW_FAMILY,
	.fops = &w1_eprom_fops,
पूर्ण;

अटल काष्ठा w1_family w1_family_91 = अणु
	.fid = W1_DS2501_UNW_FAMILY,
	.fops = &w1_eprom_fops,
पूर्ण;

अटल पूर्णांक __init w1_ds250x_init(व्योम)
अणु
	पूर्णांक err;

	err = w1_रेजिस्टर_family(&w1_family_09);
	अगर (err)
		वापस err;

	err = w1_रेजिस्टर_family(&w1_family_0b);
	अगर (err)
		जाओ err_0b;

	err = w1_रेजिस्टर_family(&w1_family_89);
	अगर (err)
		जाओ err_89;

	err = w1_रेजिस्टर_family(&w1_family_91);
	अगर (err)
		जाओ err_91;

	वापस 0;

err_91:
	w1_unरेजिस्टर_family(&w1_family_89);
err_89:
	w1_unरेजिस्टर_family(&w1_family_0b);
err_0b:
	w1_unरेजिस्टर_family(&w1_family_09);
	वापस err;
पूर्ण

अटल व्योम __निकास w1_ds250x_निकास(व्योम)
अणु
	w1_unरेजिस्टर_family(&w1_family_09);
	w1_unरेजिस्टर_family(&w1_family_0b);
	w1_unरेजिस्टर_family(&w1_family_89);
	w1_unरेजिस्टर_family(&w1_family_91);
पूर्ण

module_init(w1_ds250x_init);
module_निकास(w1_ds250x_निकास);

MODULE_AUTHOR("Thomas Bogendoerfer <tbogendoerfe@suse.de>");
MODULE_DESCRIPTION("w1 family driver for DS250x Add Only Memory");
MODULE_LICENSE("GPL");
MODULE_ALIAS("w1-family-" __stringअगरy(W1_DS2502_FAMILY));
MODULE_ALIAS("w1-family-" __stringअगरy(W1_DS2505_FAMILY));
MODULE_ALIAS("w1-family-" __stringअगरy(W1_DS2501_UNW_FAMILY));
MODULE_ALIAS("w1-family-" __stringअगरy(W1_DS2502_UNW_FAMILY));
