<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Copyright (c) 2001,2002 Christer Weinigel <wingel@nano-प्रणाली.com>

    National Semiconductor SCx200 ACCESS.bus support
    Also supports the AMD CS5535 and AMD CS5536

    Based on i2c-keywest.c which is:
        Copyright (c) 2001 Benjamin Herrenschmidt <benh@kernel.crashing.org>
        Copyright (c) 2000 Philip Edelbrock <phil@stimpy.netroedge.com>

*/

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/i2c.h>
#समावेश <linux/pci.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>
#समावेश <linux/पन.स>

#समावेश <linux/scx200.h>

MODULE_AUTHOR("Christer Weinigel <wingel@nano-system.com>");
MODULE_DESCRIPTION("NatSemi SCx200 ACCESS.bus Driver");
MODULE_ALIAS("platform:cs5535-smb");
MODULE_LICENSE("GPL");

#घोषणा MAX_DEVICES 4
अटल पूर्णांक base[MAX_DEVICES] = अणु 0x820, 0x840 पूर्ण;
module_param_hw_array(base, पूर्णांक, ioport, शून्य, 0);
MODULE_PARM_DESC(base, "Base addresses for the ACCESS.bus controllers");

#घोषणा POLL_TIMEOUT	(HZ/5)

क्रमागत scx200_acb_state अणु
	state_idle,
	state_address,
	state_command,
	state_repeat_start,
	state_quick,
	state_पढ़ो,
	state_ग_लिखो,
पूर्ण;

अटल स्थिर अक्षर *scx200_acb_state_name[] = अणु
	"idle",
	"address",
	"command",
	"repeat_start",
	"quick",
	"read",
	"write",
पूर्ण;

/* Physical पूर्णांकerface */
काष्ठा scx200_acb_अगरace अणु
	काष्ठा scx200_acb_अगरace *next;
	काष्ठा i2c_adapter adapter;
	अचिन्हित base;
	काष्ठा mutex mutex;

	/* State machine data */
	क्रमागत scx200_acb_state state;
	पूर्णांक result;
	u8 address_byte;
	u8 command;
	u8 *ptr;
	अक्षर needs_reset;
	अचिन्हित len;
पूर्ण;

/* Register Definitions */
#घोषणा ACBSDA		(अगरace->base + 0)
#घोषणा ACBST		(अगरace->base + 1)
#घोषणा    ACBST_SDAST		0x40 /* SDA Status */
#घोषणा    ACBST_BER		0x20
#घोषणा    ACBST_NEGACK		0x10 /* Negative Acknowledge */
#घोषणा    ACBST_STASTR		0x08 /* Stall After Start */
#घोषणा    ACBST_MASTER		0x02
#घोषणा ACBCST		(अगरace->base + 2)
#घोषणा    ACBCST_BB		0x02
#घोषणा ACBCTL1		(अगरace->base + 3)
#घोषणा    ACBCTL1_STASTRE	0x80
#घोषणा    ACBCTL1_NMINTE	0x40
#घोषणा    ACBCTL1_ACK		0x10
#घोषणा    ACBCTL1_STOP		0x02
#घोषणा    ACBCTL1_START	0x01
#घोषणा ACBADDR		(अगरace->base + 4)
#घोषणा ACBCTL2		(अगरace->base + 5)
#घोषणा    ACBCTL2_ENABLE	0x01

/************************************************************************/

अटल व्योम scx200_acb_machine(काष्ठा scx200_acb_अगरace *अगरace, u8 status)
अणु
	स्थिर अक्षर *errmsg;

	dev_dbg(&अगरace->adapter.dev, "state %s, status = 0x%02x\n",
		scx200_acb_state_name[अगरace->state], status);

	अगर (status & ACBST_BER) अणु
		errmsg = "bus error";
		जाओ error;
	पूर्ण
	अगर (!(status & ACBST_MASTER)) अणु
		errmsg = "not master";
		जाओ error;
	पूर्ण
	अगर (status & ACBST_NEGACK) अणु
		dev_dbg(&अगरace->adapter.dev, "negative ack in state %s\n",
			scx200_acb_state_name[अगरace->state]);

		अगरace->state = state_idle;
		अगरace->result = -ENXIO;

		outb(inb(ACBCTL1) | ACBCTL1_STOP, ACBCTL1);
		outb(ACBST_STASTR | ACBST_NEGACK, ACBST);

		/* Reset the status रेजिस्टर */
		outb(0, ACBST);
		वापस;
	पूर्ण

	चयन (अगरace->state) अणु
	हाल state_idle:
		dev_warn(&अगरace->adapter.dev, "interrupt in idle state\n");
		अवरोध;

	हाल state_address:
		/* Do a poपूर्णांकer ग_लिखो first */
		outb(अगरace->address_byte & ~1, ACBSDA);

		अगरace->state = state_command;
		अवरोध;

	हाल state_command:
		outb(अगरace->command, ACBSDA);

		अगर (अगरace->address_byte & 1)
			अगरace->state = state_repeat_start;
		अन्यथा
			अगरace->state = state_ग_लिखो;
		अवरोध;

	हाल state_repeat_start:
		outb(inb(ACBCTL1) | ACBCTL1_START, ACBCTL1);
		fallthrough;

	हाल state_quick:
		अगर (अगरace->address_byte & 1) अणु
			अगर (अगरace->len == 1)
				outb(inb(ACBCTL1) | ACBCTL1_ACK, ACBCTL1);
			अन्यथा
				outb(inb(ACBCTL1) & ~ACBCTL1_ACK, ACBCTL1);
			outb(अगरace->address_byte, ACBSDA);

			अगरace->state = state_पढ़ो;
		पूर्ण अन्यथा अणु
			outb(अगरace->address_byte, ACBSDA);

			अगरace->state = state_ग_लिखो;
		पूर्ण
		अवरोध;

	हाल state_पढ़ो:
		/* Set ACK अगर _next_ byte will be the last one */
		अगर (अगरace->len == 2)
			outb(inb(ACBCTL1) | ACBCTL1_ACK, ACBCTL1);
		अन्यथा
			outb(inb(ACBCTL1) & ~ACBCTL1_ACK, ACBCTL1);

		अगर (अगरace->len == 1) अणु
			अगरace->result = 0;
			अगरace->state = state_idle;
			outb(inb(ACBCTL1) | ACBCTL1_STOP, ACBCTL1);
		पूर्ण

		*अगरace->ptr++ = inb(ACBSDA);
		--अगरace->len;

		अवरोध;

	हाल state_ग_लिखो:
		अगर (अगरace->len == 0) अणु
			अगरace->result = 0;
			अगरace->state = state_idle;
			outb(inb(ACBCTL1) | ACBCTL1_STOP, ACBCTL1);
			अवरोध;
		पूर्ण

		outb(*अगरace->ptr++, ACBSDA);
		--अगरace->len;

		अवरोध;
	पूर्ण

	वापस;

 error:
	dev_err(&अगरace->adapter.dev,
		"%s in state %s (addr=0x%02x, len=%d, status=0x%02x)\n", errmsg,
		scx200_acb_state_name[अगरace->state], अगरace->address_byte,
		अगरace->len, status);

	अगरace->state = state_idle;
	अगरace->result = -EIO;
	अगरace->needs_reset = 1;
पूर्ण

अटल व्योम scx200_acb_poll(काष्ठा scx200_acb_अगरace *अगरace)
अणु
	u8 status;
	अचिन्हित दीर्घ समयout;

	समयout = jअगरfies + POLL_TIMEOUT;
	जबतक (1) अणु
		status = inb(ACBST);

		/* Reset the status रेजिस्टर to aव्योम the hang */
		outb(0, ACBST);

		अगर ((status & (ACBST_SDAST|ACBST_BER|ACBST_NEGACK)) != 0) अणु
			scx200_acb_machine(अगरace, status);
			वापस;
		पूर्ण
		अगर (समय_after(jअगरfies, समयout))
			अवरोध;
		cpu_relax();
		cond_resched();
	पूर्ण

	dev_err(&अगरace->adapter.dev, "timeout in state %s\n",
		scx200_acb_state_name[अगरace->state]);

	अगरace->state = state_idle;
	अगरace->result = -EIO;
	अगरace->needs_reset = 1;
पूर्ण

अटल व्योम scx200_acb_reset(काष्ठा scx200_acb_अगरace *अगरace)
अणु
	/* Disable the ACCESS.bus device and Configure the SCL
	   frequency: 16 घड़ी cycles */
	outb(0x70, ACBCTL2);
	/* Polling mode */
	outb(0, ACBCTL1);
	/* Disable slave address */
	outb(0, ACBADDR);
	/* Enable the ACCESS.bus device */
	outb(inb(ACBCTL2) | ACBCTL2_ENABLE, ACBCTL2);
	/* Free STALL after START */
	outb(inb(ACBCTL1) & ~(ACBCTL1_STASTRE | ACBCTL1_NMINTE), ACBCTL1);
	/* Send a STOP */
	outb(inb(ACBCTL1) | ACBCTL1_STOP, ACBCTL1);
	/* Clear BER, NEGACK and STASTR bits */
	outb(ACBST_BER | ACBST_NEGACK | ACBST_STASTR, ACBST);
	/* Clear BB bit */
	outb(inb(ACBCST) | ACBCST_BB, ACBCST);
पूर्ण

अटल s32 scx200_acb_smbus_xfer(काष्ठा i2c_adapter *adapter,
				 u16 address, अचिन्हित लघु flags,
				 अक्षर rw, u8 command, पूर्णांक size,
				 जोड़ i2c_smbus_data *data)
अणु
	काष्ठा scx200_acb_अगरace *अगरace = i2c_get_adapdata(adapter);
	पूर्णांक len;
	u8 *buffer;
	u16 cur_word;
	पूर्णांक rc;

	चयन (size) अणु
	हाल I2C_SMBUS_QUICK:
		len = 0;
		buffer = शून्य;
		अवरोध;

	हाल I2C_SMBUS_BYTE:
		len = 1;
		buffer = rw ? &data->byte : &command;
		अवरोध;

	हाल I2C_SMBUS_BYTE_DATA:
		len = 1;
		buffer = &data->byte;
		अवरोध;

	हाल I2C_SMBUS_WORD_DATA:
		len = 2;
		cur_word = cpu_to_le16(data->word);
		buffer = (u8 *)&cur_word;
		अवरोध;

	हाल I2C_SMBUS_I2C_BLOCK_DATA:
		len = data->block[0];
		अगर (len == 0 || len > I2C_SMBUS_BLOCK_MAX)
			वापस -EINVAL;
		buffer = &data->block[1];
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&adapter->dev,
		"size=%d, address=0x%x, command=0x%x, len=%d, read=%d\n",
		size, address, command, len, rw);

	अगर (!len && rw == I2C_SMBUS_READ) अणु
		dev_dbg(&adapter->dev, "zero length read\n");
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&अगरace->mutex);

	अगरace->address_byte = (address << 1) | rw;
	अगरace->command = command;
	अगरace->ptr = buffer;
	अगरace->len = len;
	अगरace->result = -EINVAL;
	अगरace->needs_reset = 0;

	outb(inb(ACBCTL1) | ACBCTL1_START, ACBCTL1);

	अगर (size == I2C_SMBUS_QUICK || size == I2C_SMBUS_BYTE)
		अगरace->state = state_quick;
	अन्यथा
		अगरace->state = state_address;

	जबतक (अगरace->state != state_idle)
		scx200_acb_poll(अगरace);

	अगर (अगरace->needs_reset)
		scx200_acb_reset(अगरace);

	rc = अगरace->result;

	mutex_unlock(&अगरace->mutex);

	अगर (rc == 0 && size == I2C_SMBUS_WORD_DATA && rw == I2C_SMBUS_READ)
		data->word = le16_to_cpu(cur_word);

#अगर_घोषित DEBUG
	dev_dbg(&adapter->dev, "transfer done, result: %d", rc);
	अगर (buffer) अणु
		पूर्णांक i;
		prपूर्णांकk(" data:");
		क्रम (i = 0; i < len; ++i)
			prपूर्णांकk(" %02x", buffer[i]);
	पूर्ण
	prपूर्णांकk("\n");
#पूर्ण_अगर

	वापस rc;
पूर्ण

अटल u32 scx200_acb_func(काष्ठा i2c_adapter *adapter)
अणु
	वापस I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	       I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WORD_DATA |
	       I2C_FUNC_SMBUS_I2C_BLOCK;
पूर्ण

/* For now, we only handle combined mode (smbus) */
अटल स्थिर काष्ठा i2c_algorithm scx200_acb_algorithm = अणु
	.smbus_xfer	= scx200_acb_smbus_xfer,
	.functionality	= scx200_acb_func,
पूर्ण;

अटल काष्ठा scx200_acb_अगरace *scx200_acb_list;
अटल DEFINE_MUTEX(scx200_acb_list_mutex);

अटल पूर्णांक scx200_acb_probe(काष्ठा scx200_acb_अगरace *अगरace)
अणु
	u8 val;

	/* Disable the ACCESS.bus device and Configure the SCL
	   frequency: 16 घड़ी cycles */
	outb(0x70, ACBCTL2);

	अगर (inb(ACBCTL2) != 0x70) अणु
		pr_debug("ACBCTL2 readback failed\n");
		वापस -ENXIO;
	पूर्ण

	outb(inb(ACBCTL1) | ACBCTL1_NMINTE, ACBCTL1);

	val = inb(ACBCTL1);
	अगर (val) अणु
		pr_debug("disabled, but ACBCTL1=0x%02x\n", val);
		वापस -ENXIO;
	पूर्ण

	outb(inb(ACBCTL2) | ACBCTL2_ENABLE, ACBCTL2);

	outb(inb(ACBCTL1) | ACBCTL1_NMINTE, ACBCTL1);

	val = inb(ACBCTL1);
	अगर ((val & ACBCTL1_NMINTE) != ACBCTL1_NMINTE) अणु
		pr_debug("enabled, but NMINTE won't be set, ACBCTL1=0x%02x\n",
			 val);
		वापस -ENXIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा scx200_acb_अगरace *scx200_create_अगरace(स्थिर अक्षर *text,
		काष्ठा device *dev, पूर्णांक index)
अणु
	काष्ठा scx200_acb_अगरace *अगरace;
	काष्ठा i2c_adapter *adapter;

	अगरace = kzalloc(माप(*अगरace), GFP_KERNEL);
	अगर (!अगरace)
		वापस शून्य;

	adapter = &अगरace->adapter;
	i2c_set_adapdata(adapter, अगरace);
	snम_लिखो(adapter->name, माप(adapter->name), "%s ACB%d", text, index);
	adapter->owner = THIS_MODULE;
	adapter->algo = &scx200_acb_algorithm;
	adapter->class = I2C_CLASS_HWMON | I2C_CLASS_SPD;
	adapter->dev.parent = dev;

	mutex_init(&अगरace->mutex);

	वापस अगरace;
पूर्ण

अटल पूर्णांक scx200_acb_create(काष्ठा scx200_acb_अगरace *अगरace)
अणु
	काष्ठा i2c_adapter *adapter;
	पूर्णांक rc;

	adapter = &अगरace->adapter;

	rc = scx200_acb_probe(अगरace);
	अगर (rc) अणु
		pr_warn("probe failed\n");
		वापस rc;
	पूर्ण

	scx200_acb_reset(अगरace);

	अगर (i2c_add_adapter(adapter) < 0) अणु
		pr_err("failed to register\n");
		वापस -ENODEV;
	पूर्ण

	अगर (!adapter->dev.parent) अणु
		/* If there's no dev, we're tracking (ISA) अगरaces manually */
		mutex_lock(&scx200_acb_list_mutex);
		अगरace->next = scx200_acb_list;
		scx200_acb_list = अगरace;
		mutex_unlock(&scx200_acb_list_mutex);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा scx200_acb_अगरace *scx200_create_dev(स्थिर अक्षर *text,
		अचिन्हित दीर्घ base, पूर्णांक index, काष्ठा device *dev)
अणु
	काष्ठा scx200_acb_अगरace *अगरace;
	पूर्णांक rc;

	अगरace = scx200_create_अगरace(text, dev, index);

	अगर (अगरace == शून्य)
		वापस शून्य;

	अगर (!request_region(base, 8, अगरace->adapter.name)) अणु
		pr_err("can't allocate io 0x%lx-0x%lx\n", base, base + 8 - 1);
		जाओ errout_मुक्त;
	पूर्ण

	अगरace->base = base;
	rc = scx200_acb_create(अगरace);

	अगर (rc == 0)
		वापस अगरace;

	release_region(base, 8);
 errout_मुक्त:
	kमुक्त(अगरace);
	वापस शून्य;
पूर्ण

अटल पूर्णांक scx200_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा scx200_acb_अगरace *अगरace;
	काष्ठा resource *res;

	res = platक्रमm_get_resource(pdev, IORESOURCE_IO, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "can't fetch device resource info\n");
		वापस -ENODEV;
	पूर्ण

	अगरace = scx200_create_dev("CS5535", res->start, 0, &pdev->dev);
	अगर (!अगरace)
		वापस -EIO;

	dev_info(&pdev->dev, "SCx200 device '%s' registered\n",
			अगरace->adapter.name);
	platक्रमm_set_drvdata(pdev, अगरace);

	वापस 0;
पूर्ण

अटल व्योम scx200_cleanup_अगरace(काष्ठा scx200_acb_अगरace *अगरace)
अणु
	i2c_del_adapter(&अगरace->adapter);
	release_region(अगरace->base, 8);
	kमुक्त(अगरace);
पूर्ण

अटल पूर्णांक scx200_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा scx200_acb_अगरace *अगरace;

	अगरace = platक्रमm_get_drvdata(pdev);
	scx200_cleanup_अगरace(अगरace);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver scx200_pci_driver = अणु
	.driver = अणु
		.name = "cs5535-smb",
	पूर्ण,
	.probe = scx200_probe,
	.हटाओ = scx200_हटाओ,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id scx200_isa[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_SCx200_BRIDGE) पूर्ण,
	अणु PCI_DEVICE(PCI_VENDOR_ID_NS, PCI_DEVICE_ID_NS_SC1100_BRIDGE) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

अटल __init व्योम scx200_scan_isa(व्योम)
अणु
	पूर्णांक i;

	अगर (!pci_dev_present(scx200_isa))
		वापस;

	क्रम (i = 0; i < MAX_DEVICES; ++i) अणु
		अगर (base[i] == 0)
			जारी;

		/* XXX: should we care about failures? */
		scx200_create_dev("SCx200", base[i], i, शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक __init scx200_acb_init(व्योम)
अणु
	pr_debug("NatSemi SCx200 ACCESS.bus Driver\n");

	/* First scan क्रम ISA-based devices */
	scx200_scan_isa();	/* XXX: should we care about errors? */

	/* If at least one bus was created, init must succeed */
	अगर (scx200_acb_list)
		वापस 0;

	/* No ISA devices; रेजिस्टर the platक्रमm driver क्रम PCI-based devices */
	वापस platक्रमm_driver_रेजिस्टर(&scx200_pci_driver);
पूर्ण

अटल व्योम __निकास scx200_acb_cleanup(व्योम)
अणु
	काष्ठा scx200_acb_अगरace *अगरace;

	platक्रमm_driver_unरेजिस्टर(&scx200_pci_driver);

	mutex_lock(&scx200_acb_list_mutex);
	जबतक ((अगरace = scx200_acb_list) != शून्य) अणु
		scx200_acb_list = अगरace->next;
		mutex_unlock(&scx200_acb_list_mutex);

		scx200_cleanup_अगरace(अगरace);

		mutex_lock(&scx200_acb_list_mutex);
	पूर्ण
	mutex_unlock(&scx200_acb_list_mutex);
पूर्ण

module_init(scx200_acb_init);
module_निकास(scx200_acb_cleanup);
