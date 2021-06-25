<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OPAL Operator Panel Display Driver
 *
 * Copyright 2016, Suraj Jitindar Singh, IBM Corporation.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/fs.h>
#समावेश <linux/device.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mutex.h>
#समावेश <linux/of.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/miscdevice.h>

#समावेश <यंत्र/opal.h>

/*
 * This driver creates a अक्षरacter device (/dev/op_panel) which exposes the
 * चालक panel (अक्षरacter LCD display) on IBM Power Systems machines
 * with FSPs.
 * A अक्षरacter buffer written to the device will be displayed on the
 * चालक panel.
 */

अटल DEFINE_MUTEX(oppanel_mutex);

अटल u32		num_lines, oppanel_size;
अटल oppanel_line_t	*oppanel_lines;
अटल अक्षर		*oppanel_data;

अटल loff_t oppanel_llseek(काष्ठा file *filp, loff_t offset, पूर्णांक whence)
अणु
	वापस fixed_size_llseek(filp, offset, whence, oppanel_size);
पूर्ण

अटल sमाप_प्रकार oppanel_पढ़ो(काष्ठा file *filp, अक्षर __user *userbuf, माप_प्रकार len,
			    loff_t *f_pos)
अणु
	वापस simple_पढ़ो_from_buffer(userbuf, len, f_pos, oppanel_data,
			oppanel_size);
पूर्ण

अटल पूर्णांक __op_panel_update_display(व्योम)
अणु
	काष्ठा opal_msg msg;
	पूर्णांक rc, token;

	token = opal_async_get_token_पूर्णांकerruptible();
	अगर (token < 0) अणु
		अगर (token != -ERESTARTSYS)
			pr_debug("Couldn't get OPAL async token [token=%d]\n",
				token);
		वापस token;
	पूर्ण

	rc = opal_ग_लिखो_oppanel_async(token, oppanel_lines, num_lines);
	चयन (rc) अणु
	हाल OPAL_ASYNC_COMPLETION:
		rc = opal_async_रुको_response(token, &msg);
		अगर (rc) अणु
			pr_debug("Failed to wait for async response [rc=%d]\n",
				rc);
			अवरोध;
		पूर्ण
		rc = opal_get_async_rc(msg);
		अगर (rc != OPAL_SUCCESS) अणु
			pr_debug("OPAL async call returned failed [rc=%d]\n",
				rc);
			अवरोध;
		पूर्ण
	हाल OPAL_SUCCESS:
		अवरोध;
	शेष:
		pr_debug("OPAL write op-panel call failed [rc=%d]\n", rc);
	पूर्ण

	opal_async_release_token(token);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार oppanel_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *userbuf,
			     माप_प्रकार len, loff_t *f_pos)
अणु
	loff_t f_pos_prev = *f_pos;
	sमाप_प्रकार ret;
	पूर्णांक rc;

	अगर (!*f_pos)
		स_रखो(oppanel_data, ' ', oppanel_size);
	अन्यथा अगर (*f_pos >= oppanel_size)
		वापस -EFBIG;

	ret = simple_ग_लिखो_to_buffer(oppanel_data, oppanel_size, f_pos, userbuf,
			len);
	अगर (ret > 0) अणु
		rc = __op_panel_update_display();
		अगर (rc != OPAL_SUCCESS) अणु
			pr_err_ratelimited("OPAL call failed to write to op panel display [rc=%d]\n",
				rc);
			*f_pos = f_pos_prev;
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक oppanel_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अगर (!mutex_trylock(&oppanel_mutex)) अणु
		pr_debug("Device Busy\n");
		वापस -EBUSY;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक oppanel_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	mutex_unlock(&oppanel_mutex);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations oppanel_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= oppanel_llseek,
	.पढ़ो		= oppanel_पढ़ो,
	.ग_लिखो		= oppanel_ग_लिखो,
	.खोलो		= oppanel_खोलो,
	.release	= oppanel_release
पूर्ण;

अटल काष्ठा miscdevice oppanel_dev = अणु
	.minor		= MISC_DYNAMIC_MINOR,
	.name		= "op_panel",
	.fops		= &oppanel_fops
पूर्ण;

अटल पूर्णांक oppanel_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	u32 line_len;
	पूर्णांक rc, i;

	rc = of_property_पढ़ो_u32(np, "#length", &line_len);
	अगर (rc) अणु
		pr_err_ratelimited("Operator panel length property not found\n");
		वापस rc;
	पूर्ण
	rc = of_property_पढ़ो_u32(np, "#lines", &num_lines);
	अगर (rc) अणु
		pr_err_ratelimited("Operator panel lines property not found\n");
		वापस rc;
	पूर्ण
	oppanel_size = line_len * num_lines;

	pr_devel("Operator panel of size %u found with %u lines of length %u\n",
			oppanel_size, num_lines, line_len);

	oppanel_data = kसुस्मृति(oppanel_size, माप(*oppanel_data), GFP_KERNEL);
	अगर (!oppanel_data)
		वापस -ENOMEM;

	oppanel_lines = kसुस्मृति(num_lines, माप(oppanel_line_t), GFP_KERNEL);
	अगर (!oppanel_lines) अणु
		rc = -ENOMEM;
		जाओ मुक्त_oppanel_data;
	पूर्ण

	स_रखो(oppanel_data, ' ', oppanel_size);
	क्रम (i = 0; i < num_lines; i++) अणु
		oppanel_lines[i].line_len = cpu_to_be64(line_len);
		oppanel_lines[i].line = cpu_to_be64(__pa(&oppanel_data[i *
						line_len]));
	पूर्ण

	rc = misc_रेजिस्टर(&oppanel_dev);
	अगर (rc) अणु
		pr_err_ratelimited("Failed to register as misc device\n");
		जाओ मुक्त_oppanel;
	पूर्ण

	वापस 0;

मुक्त_oppanel:
	kमुक्त(oppanel_lines);
मुक्त_oppanel_data:
	kमुक्त(oppanel_data);
	वापस rc;
पूर्ण

अटल पूर्णांक oppanel_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	misc_deरेजिस्टर(&oppanel_dev);
	kमुक्त(oppanel_lines);
	kमुक्त(oppanel_data);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id oppanel_match[] = अणु
	अणु .compatible = "ibm,opal-oppanel" पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver oppanel_driver = अणु
	.driver	= अणु
		.name		= "powernv-op-panel",
		.of_match_table	= oppanel_match,
	पूर्ण,
	.probe	= oppanel_probe,
	.हटाओ	= oppanel_हटाओ,
पूर्ण;

module_platक्रमm_driver(oppanel_driver);

MODULE_DEVICE_TABLE(of, oppanel_match);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("PowerNV Operator Panel LCD Display Driver");
MODULE_AUTHOR("Suraj Jitindar Singh <sjitindarsingh@gmail.com>");
