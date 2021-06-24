<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * debugfs attributes क्रम Wilco EC
 *
 * Copyright 2019 Google LLC
 *
 * See Documentation/ABI/testing/debugfs-wilco-ec क्रम usage.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/debugfs.h>
#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_data/wilco-ec.h>
#समावेश <linux/platक्रमm_device.h>

#घोषणा DRV_NAME "wilco-ec-debugfs"

/* The raw bytes will take up more space when represented as a hex string */
#घोषणा FORMATTED_BUFFER_SIZE (EC_MAILBOX_DATA_SIZE * 4)

काष्ठा wilco_ec_debugfs अणु
	काष्ठा wilco_ec_device *ec;
	काष्ठा dentry *dir;
	माप_प्रकार response_size;
	u8 raw_data[EC_MAILBOX_DATA_SIZE];
	u8 क्रमmatted_data[FORMATTED_BUFFER_SIZE];
पूर्ण;
अटल काष्ठा wilco_ec_debugfs *debug_info;

/**
 * parse_hex_sentence() - Convert a ascii hex representation पूर्णांकo byte array.
 * @in: Input buffer of ascii.
 * @isize: Length of input buffer.
 * @out: Output buffer.
 * @osize: Length of output buffer, e.g. max number of bytes to parse.
 *
 * An valid input is a series of ascii hexadecimal numbers, separated by spaces.
 * An example valid input is
 * "   00 f2 0    000076 6 0  ff"
 *
 * If an inभागidual "word" within the hex sentence is दीर्घer than MAX_WORD_SIZE,
 * then the sentence is illegal, and parsing will fail.
 *
 * Return: Number of bytes parsed, or negative error code on failure.
 */
अटल पूर्णांक parse_hex_sentence(स्थिर अक्षर *in, पूर्णांक isize, u8 *out, पूर्णांक osize)
अणु
	पूर्णांक n_parsed = 0;
	पूर्णांक word_start = 0;
	पूर्णांक word_end;
	पूर्णांक word_len;
	/* Temp buffer क्रम holding a "word" of अक्षरs that represents one byte */
	#घोषणा MAX_WORD_SIZE 16
	अक्षर पंचांगp[MAX_WORD_SIZE + 1];
	u8 byte;

	जबतक (word_start < isize && n_parsed < osize) अणु
		/* Find the start of the next word */
		जबतक (word_start < isize && है_खाली(in[word_start]))
			word_start++;
		 /* reached the end of the input beक्रमe next word? */
		अगर (word_start >= isize)
			अवरोध;

		/* Find the end of this word */
		word_end = word_start;
		जबतक (word_end < isize && !है_खाली(in[word_end]))
			word_end++;

		/* Copy to a पंचांगp शून्य terminated string */
		word_len = word_end - word_start;
		अगर (word_len > MAX_WORD_SIZE)
			वापस -EINVAL;
		स_नकल(पंचांगp, in + word_start, word_len);
		पंचांगp[word_len] = '\0';

		/*
		 * Convert from hex string, place in output. If fails to parse,
		 * just वापस -EINVAL because specअगरic error code is only
		 * relevant क्रम this one word, वापसing it would be confusing.
		 */
		अगर (kstrtou8(पंचांगp, 16, &byte))
			वापस -EINVAL;
		out[n_parsed++] = byte;

		word_start = word_end;
	पूर्ण
	वापस n_parsed;
पूर्ण

/* The message type takes up two bytes*/
#घोषणा TYPE_AND_DATA_SIZE ((EC_MAILBOX_DATA_SIZE) + 2)

अटल sमाप_प्रकार raw_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर *buf = debug_info->क्रमmatted_data;
	काष्ठा wilco_ec_message msg;
	u8 request_data[TYPE_AND_DATA_SIZE];
	sमाप_प्रकार kcount;
	पूर्णांक ret;

	अगर (count > FORMATTED_BUFFER_SIZE)
		वापस -EINVAL;

	kcount = simple_ग_लिखो_to_buffer(buf, FORMATTED_BUFFER_SIZE, ppos,
					user_buf, count);
	अगर (kcount < 0)
		वापस kcount;

	ret = parse_hex_sentence(buf, kcount, request_data, TYPE_AND_DATA_SIZE);
	अगर (ret < 0)
		वापस ret;
	/* Need at least two bytes क्रम message type and one byte of data */
	अगर (ret < 3)
		वापस -EINVAL;

	msg.type = request_data[0] << 8 | request_data[1];
	msg.flags = 0;
	msg.request_data = request_data + 2;
	msg.request_size = ret - 2;
	स_रखो(debug_info->raw_data, 0, माप(debug_info->raw_data));
	msg.response_data = debug_info->raw_data;
	msg.response_size = EC_MAILBOX_DATA_SIZE;

	ret = wilco_ec_mailbox(debug_info->ec, &msg);
	अगर (ret < 0)
		वापस ret;
	debug_info->response_size = ret;

	वापस count;
पूर्ण

अटल sमाप_प्रकार raw_पढ़ो(काष्ठा file *file, अक्षर __user *user_buf, माप_प्रकार count,
			loff_t *ppos)
अणु
	पूर्णांक fmt_len = 0;

	अगर (debug_info->response_size) अणु
		fmt_len = hex_dump_to_buffer(debug_info->raw_data,
					     debug_info->response_size,
					     16, 1, debug_info->क्रमmatted_data,
					     माप(debug_info->क्रमmatted_data),
					     true);
		/* Only वापस response the first समय it is पढ़ो */
		debug_info->response_size = 0;
	पूर्ण

	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos,
				       debug_info->क्रमmatted_data, fmt_len);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_raw = अणु
	.owner = THIS_MODULE,
	.पढ़ो = raw_पढ़ो,
	.ग_लिखो = raw_ग_लिखो,
	.llseek = no_llseek,
पूर्ण;

#घोषणा CMD_KB_CHROME		0x88
#घोषणा SUB_CMD_H1_GPIO		0x0A
#घोषणा SUB_CMD_TEST_EVENT	0x0B

काष्ठा ec_request अणु
	u8 cmd;		/* Always CMD_KB_CHROME */
	u8 reserved;
	u8 sub_cmd;
पूर्ण __packed;

काष्ठा ec_response अणु
	u8 status;	/* 0 अगर allowed */
	u8 val;
पूर्ण __packed;

अटल पूर्णांक send_ec_cmd(काष्ठा wilco_ec_device *ec, u8 sub_cmd, u8 *out_val)
अणु
	काष्ठा ec_request rq;
	काष्ठा ec_response rs;
	काष्ठा wilco_ec_message msg;
	पूर्णांक ret;

	स_रखो(&rq, 0, माप(rq));
	rq.cmd = CMD_KB_CHROME;
	rq.sub_cmd = sub_cmd;

	स_रखो(&msg, 0, माप(msg));
	msg.type = WILCO_EC_MSG_LEGACY;
	msg.request_data = &rq;
	msg.request_size = माप(rq);
	msg.response_data = &rs;
	msg.response_size = माप(rs);
	ret = wilco_ec_mailbox(ec, &msg);
	अगर (ret < 0)
		वापस ret;
	अगर (rs.status)
		वापस -EIO;

	*out_val = rs.val;

	वापस 0;
पूर्ण

/**
 * h1_gpio_get() - Gets h1 gpio status.
 * @arg: The wilco EC device.
 * @val: BIT(0)=ENTRY_TO_FACT_MODE, BIT(1)=SPI_CHROME_SEL
 */
अटल पूर्णांक h1_gpio_get(व्योम *arg, u64 *val)
अणु
	पूर्णांक ret;

	ret = send_ec_cmd(arg, SUB_CMD_H1_GPIO, (u8 *)val);
	अगर (ret == 0)
		*val &= 0xFF;
	वापस ret;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(fops_h1_gpio, h1_gpio_get, शून्य, "0x%02llx\n");

/**
 * test_event_set() - Sends command to EC to cause an EC test event.
 * @arg: The wilco EC device.
 * @val: unused.
 */
अटल पूर्णांक test_event_set(व्योम *arg, u64 val)
अणु
	u8 ret;

	वापस send_ec_cmd(arg, SUB_CMD_TEST_EVENT, &ret);
पूर्ण

/* Format is unused since it is only required क्रम get method which is शून्य */
DEFINE_DEBUGFS_ATTRIBUTE(fops_test_event, शून्य, test_event_set, "%llu\n");

/**
 * wilco_ec_debugfs_probe() - Create the debugfs node
 * @pdev: The platक्रमm device, probably created in core.c
 *
 * Try to create a debugfs node. If it fails, then we करोn't want to change
 * behavior at all, this is क्रम debugging after all. Just fail silently.
 *
 * Return: 0 always.
 */
अटल पूर्णांक wilco_ec_debugfs_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wilco_ec_device *ec = dev_get_drvdata(pdev->dev.parent);

	debug_info = devm_kzalloc(&pdev->dev, माप(*debug_info), GFP_KERNEL);
	अगर (!debug_info)
		वापस 0;
	debug_info->ec = ec;
	debug_info->dir = debugfs_create_dir("wilco_ec", शून्य);
	अगर (!debug_info->dir)
		वापस 0;
	debugfs_create_file("raw", 0644, debug_info->dir, शून्य, &fops_raw);
	debugfs_create_file("h1_gpio", 0444, debug_info->dir, ec,
			    &fops_h1_gpio);
	debugfs_create_file("test_event", 0200, debug_info->dir, ec,
			    &fops_test_event);

	वापस 0;
पूर्ण

अटल पूर्णांक wilco_ec_debugfs_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	debugfs_हटाओ_recursive(debug_info->dir);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver wilco_ec_debugfs_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
	पूर्ण,
	.probe = wilco_ec_debugfs_probe,
	.हटाओ = wilco_ec_debugfs_हटाओ,
पूर्ण;

module_platक्रमm_driver(wilco_ec_debugfs_driver);

MODULE_ALIAS("platform:" DRV_NAME);
MODULE_AUTHOR("Nick Crews <ncrews@chromium.org>");
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Wilco EC debugfs driver");
