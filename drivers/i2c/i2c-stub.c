<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    i2c-stub.c - I2C/SMBus chip emulator

    Copyright (c) 2004 Mark M. Hoffman <mhoffman@lightlink.com>
    Copyright (C) 2007-2014 Jean Delvare <jdelvare@suse.de>

*/

#घोषणा pr_fmt(fmt) "i2c-stub: " fmt

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/i2c.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#घोषणा MAX_CHIPS 10

/*
 * Support क्रम I2C_FUNC_SMBUS_BLOCK_DATA is disabled by शेष and must
 * be enabled explicitly by setting the I2C_FUNC_SMBUS_BLOCK_DATA bits
 * in the 'functionality' module parameter.
 */
#घोषणा STUB_FUNC_DEFAULT \
		(I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE | \
		 I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA | \
		 I2C_FUNC_SMBUS_I2C_BLOCK)

#घोषणा STUB_FUNC_ALL \
		(STUB_FUNC_DEFAULT | I2C_FUNC_SMBUS_BLOCK_DATA)

अटल अचिन्हित लघु chip_addr[MAX_CHIPS];
module_param_array(chip_addr, uलघु, शून्य, S_IRUGO);
MODULE_PARM_DESC(chip_addr,
		 "Chip addresses (up to 10, between 0x03 and 0x77)");

अटल अचिन्हित दीर्घ functionality = STUB_FUNC_DEFAULT;
module_param(functionality, uदीर्घ, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(functionality, "Override functionality bitfield");

/* Some chips have banked रेजिस्टर ranges */

अटल u8 bank_reg[MAX_CHIPS];
module_param_array(bank_reg, byte, शून्य, S_IRUGO);
MODULE_PARM_DESC(bank_reg, "Bank register");

अटल u8 bank_mask[MAX_CHIPS];
module_param_array(bank_mask, byte, शून्य, S_IRUGO);
MODULE_PARM_DESC(bank_mask, "Bank value mask");

अटल u8 bank_start[MAX_CHIPS];
module_param_array(bank_start, byte, शून्य, S_IRUGO);
MODULE_PARM_DESC(bank_start, "First banked register");

अटल u8 bank_end[MAX_CHIPS];
module_param_array(bank_end, byte, शून्य, S_IRUGO);
MODULE_PARM_DESC(bank_end, "Last banked register");

काष्ठा smbus_block_data अणु
	काष्ठा list_head node;
	u8 command;
	u8 len;
	u8 block[I2C_SMBUS_BLOCK_MAX];
पूर्ण;

काष्ठा stub_chip अणु
	u8 poपूर्णांकer;
	u16 words[256];		/* Byte operations use the LSB as per SMBus
				   specअगरication */
	काष्ठा list_head smbus_blocks;

	/* For chips with banks, extra रेजिस्टरs are allocated dynamically */
	u8 bank_reg;
	u8 bank_shअगरt;
	u8 bank_mask;
	u8 bank_sel;		/* Currently selected bank */
	u8 bank_start;
	u8 bank_end;
	u16 bank_size;
	u16 *bank_words;	/* Room क्रम bank_mask * bank_size रेजिस्टरs */
पूर्ण;

अटल काष्ठा stub_chip *stub_chips;
अटल पूर्णांक stub_chips_nr;

अटल काष्ठा smbus_block_data *stub_find_block(काष्ठा device *dev,
						काष्ठा stub_chip *chip,
						u8 command, bool create)
अणु
	काष्ठा smbus_block_data *b, *rb = शून्य;

	list_क्रम_each_entry(b, &chip->smbus_blocks, node) अणु
		अगर (b->command == command) अणु
			rb = b;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (rb == शून्य && create) अणु
		rb = devm_kzalloc(dev, माप(*rb), GFP_KERNEL);
		अगर (rb == शून्य)
			वापस rb;
		rb->command = command;
		list_add(&rb->node, &chip->smbus_blocks);
	पूर्ण
	वापस rb;
पूर्ण

अटल u16 *stub_get_wordp(काष्ठा stub_chip *chip, u8 offset)
अणु
	अगर (chip->bank_sel &&
	    offset >= chip->bank_start && offset <= chip->bank_end)
		वापस chip->bank_words +
		       (chip->bank_sel - 1) * chip->bank_size +
		       offset - chip->bank_start;
	अन्यथा
		वापस chip->words + offset;
पूर्ण

/* Return negative त्रुटि_सं on error. */
अटल s32 stub_xfer(काष्ठा i2c_adapter *adap, u16 addr, अचिन्हित लघु flags,
	अक्षर पढ़ो_ग_लिखो, u8 command, पूर्णांक size, जोड़ i2c_smbus_data *data)
अणु
	s32 ret;
	पूर्णांक i, len;
	काष्ठा stub_chip *chip = शून्य;
	काष्ठा smbus_block_data *b;
	u16 *wordp;

	/* Search क्रम the right chip */
	क्रम (i = 0; i < stub_chips_nr; i++) अणु
		अगर (addr == chip_addr[i]) अणु
			chip = stub_chips + i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!chip)
		वापस -ENODEV;

	चयन (size) अणु

	हाल I2C_SMBUS_QUICK:
		dev_dbg(&adap->dev, "smbus quick - addr 0x%02x\n", addr);
		ret = 0;
		अवरोध;

	हाल I2C_SMBUS_BYTE:
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			chip->poपूर्णांकer = command;
			dev_dbg(&adap->dev,
				"smbus byte - addr 0x%02x, wrote 0x%02x.\n",
				addr, command);
		पूर्ण अन्यथा अणु
			wordp = stub_get_wordp(chip, chip->poपूर्णांकer++);
			data->byte = *wordp & 0xff;
			dev_dbg(&adap->dev,
				"smbus byte - addr 0x%02x, read  0x%02x.\n",
				addr, data->byte);
		पूर्ण

		ret = 0;
		अवरोध;

	हाल I2C_SMBUS_BYTE_DATA:
		wordp = stub_get_wordp(chip, command);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			*wordp &= 0xff00;
			*wordp |= data->byte;
			dev_dbg(&adap->dev,
				"smbus byte data - addr 0x%02x, wrote 0x%02x at 0x%02x.\n",
				addr, data->byte, command);

			/* Set the bank as needed */
			अगर (chip->bank_words && command == chip->bank_reg) अणु
				chip->bank_sel =
					(data->byte >> chip->bank_shअगरt)
					& chip->bank_mask;
				dev_dbg(&adap->dev,
					"switching to bank %u.\n",
					chip->bank_sel);
			पूर्ण
		पूर्ण अन्यथा अणु
			data->byte = *wordp & 0xff;
			dev_dbg(&adap->dev,
				"smbus byte data - addr 0x%02x, read  0x%02x at 0x%02x.\n",
				addr, data->byte, command);
		पूर्ण
		chip->poपूर्णांकer = command + 1;

		ret = 0;
		अवरोध;

	हाल I2C_SMBUS_WORD_DATA:
		wordp = stub_get_wordp(chip, command);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			*wordp = data->word;
			dev_dbg(&adap->dev,
				"smbus word data - addr 0x%02x, wrote 0x%04x at 0x%02x.\n",
				addr, data->word, command);
		पूर्ण अन्यथा अणु
			data->word = *wordp;
			dev_dbg(&adap->dev,
				"smbus word data - addr 0x%02x, read  0x%04x at 0x%02x.\n",
				addr, data->word, command);
		पूर्ण

		ret = 0;
		अवरोध;

	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		/*
		 * We ignore banks here, because banked chips करोn't use I2C
		 * block transfers
		 */
		अगर (data->block[0] > 256 - command)	/* Aव्योम overrun */
			data->block[0] = 256 - command;
		len = data->block[0];
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			क्रम (i = 0; i < len; i++) अणु
				chip->words[command + i] &= 0xff00;
				chip->words[command + i] |= data->block[1 + i];
			पूर्ण
			dev_dbg(&adap->dev,
				"i2c block data - addr 0x%02x, wrote %d bytes at 0x%02x.\n",
				addr, len, command);
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < len; i++) अणु
				data->block[1 + i] =
					chip->words[command + i] & 0xff;
			पूर्ण
			dev_dbg(&adap->dev,
				"i2c block data - addr 0x%02x, read  %d bytes at 0x%02x.\n",
				addr, len, command);
		पूर्ण

		ret = 0;
		अवरोध;

	हाल I2C_SMBUS_BLOCK_DATA:
		/*
		 * We ignore banks here, because chips typically करोn't use both
		 * banks and SMBus block transfers
		 */
		b = stub_find_block(&adap->dev, chip, command, false);
		अगर (पढ़ो_ग_लिखो == I2C_SMBUS_WRITE) अणु
			len = data->block[0];
			अगर (len == 0 || len > I2C_SMBUS_BLOCK_MAX) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण
			अगर (b == शून्य) अणु
				b = stub_find_block(&adap->dev, chip, command,
						    true);
				अगर (b == शून्य) अणु
					ret = -ENOMEM;
					अवरोध;
				पूर्ण
			पूर्ण
			/* Largest ग_लिखो sets पढ़ो block length */
			अगर (len > b->len)
				b->len = len;
			क्रम (i = 0; i < len; i++)
				b->block[i] = data->block[i + 1];
			/* update क्रम byte and word commands */
			chip->words[command] = (b->block[0] << 8) | b->len;
			dev_dbg(&adap->dev,
				"smbus block data - addr 0x%02x, wrote %d bytes at 0x%02x.\n",
				addr, len, command);
		पूर्ण अन्यथा अणु
			अगर (b == शून्य) अणु
				dev_dbg(&adap->dev,
					"SMBus block read command without prior block write not supported\n");
				ret = -EOPNOTSUPP;
				अवरोध;
			पूर्ण
			len = b->len;
			data->block[0] = len;
			क्रम (i = 0; i < len; i++)
				data->block[i + 1] = b->block[i];
			dev_dbg(&adap->dev,
				"smbus block data - addr 0x%02x, read  %d bytes at 0x%02x.\n",
				addr, len, command);
		पूर्ण

		ret = 0;
		अवरोध;

	शेष:
		dev_dbg(&adap->dev, "Unsupported I2C/SMBus command\n");
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण /* चयन (size) */

	वापस ret;
पूर्ण

अटल u32 stub_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस STUB_FUNC_ALL & functionality;
पूर्ण

अटल स्थिर काष्ठा i2c_algorithm smbus_algorithm = अणु
	.functionality	= stub_func,
	.smbus_xfer	= stub_xfer,
पूर्ण;

अटल काष्ठा i2c_adapter stub_adapter = अणु
	.owner		= THIS_MODULE,
	.class		= I2C_CLASS_HWMON | I2C_CLASS_SPD,
	.algo		= &smbus_algorithm,
	.name		= "SMBus stub driver",
पूर्ण;

अटल पूर्णांक __init i2c_stub_allocate_banks(पूर्णांक i)
अणु
	काष्ठा stub_chip *chip = stub_chips + i;

	chip->bank_reg = bank_reg[i];
	chip->bank_start = bank_start[i];
	chip->bank_end = bank_end[i];
	chip->bank_size = bank_end[i] - bank_start[i] + 1;

	/* We assume that all bits in the mask are contiguous */
	chip->bank_mask = bank_mask[i];
	जबतक (!(chip->bank_mask & 1)) अणु
		chip->bank_shअगरt++;
		chip->bank_mask >>= 1;
	पूर्ण

	chip->bank_words = kसुस्मृति(chip->bank_mask * chip->bank_size,
				   माप(u16),
				   GFP_KERNEL);
	अगर (!chip->bank_words)
		वापस -ENOMEM;

	pr_debug("Allocated %u banks of %u words each (registers 0x%02x to 0x%02x)\n",
		 chip->bank_mask, chip->bank_size, chip->bank_start,
		 chip->bank_end);

	वापस 0;
पूर्ण

अटल व्योम i2c_stub_मुक्त(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < stub_chips_nr; i++)
		kमुक्त(stub_chips[i].bank_words);
	kमुक्त(stub_chips);
पूर्ण

अटल पूर्णांक __init i2c_stub_init(व्योम)
अणु
	पूर्णांक i, ret;

	अगर (!chip_addr[0]) अणु
		pr_err("Please specify a chip address\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < MAX_CHIPS && chip_addr[i]; i++) अणु
		अगर (chip_addr[i] < 0x03 || chip_addr[i] > 0x77) अणु
			pr_err("Invalid chip address 0x%02x\n",
			       chip_addr[i]);
			वापस -EINVAL;
		पूर्ण

		pr_info("Virtual chip at 0x%02x\n", chip_addr[i]);
	पूर्ण

	/* Allocate memory क्रम all chips at once */
	stub_chips_nr = i;
	stub_chips = kसुस्मृति(stub_chips_nr, माप(काष्ठा stub_chip),
			     GFP_KERNEL);
	अगर (!stub_chips)
		वापस -ENOMEM;

	क्रम (i = 0; i < stub_chips_nr; i++) अणु
		INIT_LIST_HEAD(&stub_chips[i].smbus_blocks);

		/* Allocate extra memory क्रम banked रेजिस्टर ranges */
		अगर (bank_mask[i]) अणु
			ret = i2c_stub_allocate_banks(i);
			अगर (ret)
				जाओ fail_मुक्त;
		पूर्ण
	पूर्ण

	ret = i2c_add_adapter(&stub_adapter);
	अगर (ret)
		जाओ fail_मुक्त;

	वापस 0;

 fail_मुक्त:
	i2c_stub_मुक्त();
	वापस ret;
पूर्ण

अटल व्योम __निकास i2c_stub_निकास(व्योम)
अणु
	i2c_del_adapter(&stub_adapter);
	i2c_stub_मुक्त();
पूर्ण

MODULE_AUTHOR("Mark M. Hoffman <mhoffman@lightlink.com>");
MODULE_DESCRIPTION("I2C stub driver");
MODULE_LICENSE("GPL");

module_init(i2c_stub_init);
module_निकास(i2c_stub_निकास);
