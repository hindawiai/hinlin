<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *    SCLP control program identअगरication sysfs पूर्णांकerface
 *
 *    Copyright IBM Corp. 2001, 2007
 *    Author(s): Martin Peschke <mpeschke@de.ibm.com>
 *		 Michael Ernst <mernst@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "sclp_cpi"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/device.h>
#समावेश <linux/माला.स>
#समावेश <linux/प्रकार.स>
#समावेश <linux/kmod.h>
#समावेश <linux/समयr.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/completion.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/ebcdic.h>
#समावेश <यंत्र/sclp.h>

#समावेश "sclp.h"
#समावेश "sclp_rw.h"
#समावेश "sclp_cpi_sys.h"

#घोषणा CPI_LENGTH_NAME 8
#घोषणा CPI_LENGTH_LEVEL 16

अटल DEFINE_MUTEX(sclp_cpi_mutex);

काष्ठा cpi_evbuf अणु
	काष्ठा evbuf_header header;
	u8	id_क्रमmat;
	u8	reserved0;
	u8	प्रणाली_type[CPI_LENGTH_NAME];
	u64	reserved1;
	u8	प्रणाली_name[CPI_LENGTH_NAME];
	u64	reserved2;
	u64	प्रणाली_level;
	u64	reserved3;
	u8	sysplex_name[CPI_LENGTH_NAME];
	u8	reserved4[16];
पूर्ण __attribute__((packed));

काष्ठा cpi_sccb अणु
	काष्ठा sccb_header header;
	काष्ठा cpi_evbuf cpi_evbuf;
पूर्ण __attribute__((packed));

अटल काष्ठा sclp_रेजिस्टर sclp_cpi_event = अणु
	.send_mask = EVTYP_CTLPROGIDENT_MASK,
पूर्ण;

अटल अक्षर प्रणाली_name[CPI_LENGTH_NAME + 1];
अटल अक्षर sysplex_name[CPI_LENGTH_NAME + 1];
अटल अक्षर प्रणाली_type[CPI_LENGTH_NAME + 1];
अटल u64 प्रणाली_level;

अटल व्योम set_data(अक्षर *field, अक्षर *data)
अणु
	स_रखो(field, ' ', CPI_LENGTH_NAME);
	स_नकल(field, data, म_माप(data));
	sclp_ascebc_str(field, CPI_LENGTH_NAME);
पूर्ण

अटल व्योम cpi_callback(काष्ठा sclp_req *req, व्योम *data)
अणु
	काष्ठा completion *completion = data;

	complete(completion);
पूर्ण

अटल काष्ठा sclp_req *cpi_prepare_req(व्योम)
अणु
	काष्ठा sclp_req *req;
	काष्ठा cpi_sccb *sccb;
	काष्ठा cpi_evbuf *evb;

	req = kzalloc(माप(काष्ठा sclp_req), GFP_KERNEL);
	अगर (!req)
		वापस ERR_PTR(-ENOMEM);
	sccb = (काष्ठा cpi_sccb *) get_zeroed_page(GFP_KERNEL | GFP_DMA);
	अगर (!sccb) अणु
		kमुक्त(req);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	/* setup SCCB क्रम Control-Program Identअगरication */
	sccb->header.length = माप(काष्ठा cpi_sccb);
	sccb->cpi_evbuf.header.length = माप(काष्ठा cpi_evbuf);
	sccb->cpi_evbuf.header.type = EVTYP_CTLPROGIDENT;
	evb = &sccb->cpi_evbuf;

	/* set प्रणाली type */
	set_data(evb->प्रणाली_type, प्रणाली_type);

	/* set प्रणाली name */
	set_data(evb->प्रणाली_name, प्रणाली_name);

	/* set प्रणाली level */
	evb->प्रणाली_level = प्रणाली_level;

	/* set sysplex name */
	set_data(evb->sysplex_name, sysplex_name);

	/* prepare request data काष्ठाure presented to SCLP driver */
	req->command = SCLP_CMDW_WRITE_EVENT_DATA;
	req->sccb = sccb;
	req->status = SCLP_REQ_FILLED;
	req->callback = cpi_callback;
	वापस req;
पूर्ण

अटल व्योम cpi_मुक्त_req(काष्ठा sclp_req *req)
अणु
	मुक्त_page((अचिन्हित दीर्घ) req->sccb);
	kमुक्त(req);
पूर्ण

अटल पूर्णांक cpi_req(व्योम)
अणु
	काष्ठा completion completion;
	काष्ठा sclp_req *req;
	पूर्णांक rc;
	पूर्णांक response;

	rc = sclp_रेजिस्टर(&sclp_cpi_event);
	अगर (rc)
		जाओ out;
	अगर (!(sclp_cpi_event.sclp_receive_mask & EVTYP_CTLPROGIDENT_MASK)) अणु
		rc = -EOPNOTSUPP;
		जाओ out_unरेजिस्टर;
	पूर्ण

	req = cpi_prepare_req();
	अगर (IS_ERR(req)) अणु
		rc = PTR_ERR(req);
		जाओ out_unरेजिस्टर;
	पूर्ण

	init_completion(&completion);
	req->callback_data = &completion;

	/* Add request to sclp queue */
	rc = sclp_add_request(req);
	अगर (rc)
		जाओ out_मुक्त_req;

	रुको_क्रम_completion(&completion);

	अगर (req->status != SCLP_REQ_DONE) अणु
		pr_warn("request failed (status=0x%02x)\n", req->status);
		rc = -EIO;
		जाओ out_मुक्त_req;
	पूर्ण

	response = ((काष्ठा cpi_sccb *) req->sccb)->header.response_code;
	अगर (response != 0x0020) अणु
		pr_warn("request failed with response code 0x%x\n", response);
		rc = -EIO;
	पूर्ण

out_मुक्त_req:
	cpi_मुक्त_req(req);

out_unरेजिस्टर:
	sclp_unरेजिस्टर(&sclp_cpi_event);

out:
	वापस rc;
पूर्ण

अटल पूर्णांक check_string(स्थिर अक्षर *attr, स्थिर अक्षर *str)
अणु
	माप_प्रकार len;
	माप_प्रकार i;

	len = म_माप(str);

	अगर ((len > 0) && (str[len - 1] == '\n'))
		len--;

	अगर (len > CPI_LENGTH_NAME)
		वापस -EINVAL;

	क्रम (i = 0; i < len ; i++) अणु
		अगर (है_अक्षर(str[i]) || है_अंक(str[i]) ||
		    म_अक्षर("$@# ", str[i]))
			जारी;
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम set_string(अक्षर *attr, स्थिर अक्षर *value)
अणु
	माप_प्रकार len;
	माप_प्रकार i;

	len = म_माप(value);

	अगर ((len > 0) && (value[len - 1] == '\n'))
		len--;

	क्रम (i = 0; i < CPI_LENGTH_NAME; i++) अणु
		अगर (i < len)
			attr[i] = बड़े(value[i]);
		अन्यथा
			attr[i] = ' ';
	पूर्ण
पूर्ण

अटल sमाप_प्रकार प्रणाली_name_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	पूर्णांक rc;

	mutex_lock(&sclp_cpi_mutex);
	rc = snम_लिखो(page, PAGE_SIZE, "%s\n", प्रणाली_name);
	mutex_unlock(&sclp_cpi_mutex);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार प्रणाली_name_store(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr,
				 स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	पूर्णांक rc;

	rc = check_string("system_name", buf);
	अगर (rc)
		वापस rc;

	mutex_lock(&sclp_cpi_mutex);
	set_string(प्रणाली_name, buf);
	mutex_unlock(&sclp_cpi_mutex);

	वापस len;
पूर्ण

अटल काष्ठा kobj_attribute प्रणाली_name_attr =
	__ATTR(प्रणाली_name, 0644, प्रणाली_name_show, प्रणाली_name_store);

अटल sमाप_प्रकार sysplex_name_show(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	पूर्णांक rc;

	mutex_lock(&sclp_cpi_mutex);
	rc = snम_लिखो(page, PAGE_SIZE, "%s\n", sysplex_name);
	mutex_unlock(&sclp_cpi_mutex);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार sysplex_name_store(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr,
				  स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	पूर्णांक rc;

	rc = check_string("sysplex_name", buf);
	अगर (rc)
		वापस rc;

	mutex_lock(&sclp_cpi_mutex);
	set_string(sysplex_name, buf);
	mutex_unlock(&sclp_cpi_mutex);

	वापस len;
पूर्ण

अटल काष्ठा kobj_attribute sysplex_name_attr =
	__ATTR(sysplex_name, 0644, sysplex_name_show, sysplex_name_store);

अटल sमाप_प्रकार प्रणाली_type_show(काष्ठा kobject *kobj,
				काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	पूर्णांक rc;

	mutex_lock(&sclp_cpi_mutex);
	rc = snम_लिखो(page, PAGE_SIZE, "%s\n", प्रणाली_type);
	mutex_unlock(&sclp_cpi_mutex);
	वापस rc;
पूर्ण

अटल sमाप_प्रकार प्रणाली_type_store(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr,
				 स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	पूर्णांक rc;

	rc = check_string("system_type", buf);
	अगर (rc)
		वापस rc;

	mutex_lock(&sclp_cpi_mutex);
	set_string(प्रणाली_type, buf);
	mutex_unlock(&sclp_cpi_mutex);

	वापस len;
पूर्ण

अटल काष्ठा kobj_attribute प्रणाली_type_attr =
	__ATTR(प्रणाली_type, 0644, प्रणाली_type_show, प्रणाली_type_store);

अटल sमाप_प्रकार प्रणाली_level_show(काष्ठा kobject *kobj,
				 काष्ठा kobj_attribute *attr, अक्षर *page)
अणु
	अचिन्हित दीर्घ दीर्घ level;

	mutex_lock(&sclp_cpi_mutex);
	level = प्रणाली_level;
	mutex_unlock(&sclp_cpi_mutex);
	वापस snम_लिखो(page, PAGE_SIZE, "%#018llx\n", level);
पूर्ण

अटल sमाप_प्रकार प्रणाली_level_store(काष्ठा kobject *kobj,
				  काष्ठा kobj_attribute *attr,
				  स्थिर अक्षर *buf,
	माप_प्रकार len)
अणु
	अचिन्हित दीर्घ दीर्घ level;
	अक्षर *endp;

	level = simple_म_से_अदीर्घl(buf, &endp, 16);

	अगर (endp == buf)
		वापस -EINVAL;
	अगर (*endp == '\n')
		endp++;
	अगर (*endp)
		वापस -EINVAL;

	mutex_lock(&sclp_cpi_mutex);
	प्रणाली_level = level;
	mutex_unlock(&sclp_cpi_mutex);
	वापस len;
पूर्ण

अटल काष्ठा kobj_attribute प्रणाली_level_attr =
	__ATTR(प्रणाली_level, 0644, प्रणाली_level_show, प्रणाली_level_store);

अटल sमाप_प्रकार set_store(काष्ठा kobject *kobj,
			 काष्ठा kobj_attribute *attr,
			 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	पूर्णांक rc;

	mutex_lock(&sclp_cpi_mutex);
	rc = cpi_req();
	mutex_unlock(&sclp_cpi_mutex);
	अगर (rc)
		वापस rc;

	वापस len;
पूर्ण

अटल काष्ठा kobj_attribute set_attr = __ATTR(set, 0200, शून्य, set_store);

अटल काष्ठा attribute *cpi_attrs[] = अणु
	&प्रणाली_name_attr.attr,
	&sysplex_name_attr.attr,
	&प्रणाली_type_attr.attr,
	&प्रणाली_level_attr.attr,
	&set_attr.attr,
	शून्य,
पूर्ण;

अटल काष्ठा attribute_group cpi_attr_group = अणु
	.attrs = cpi_attrs,
पूर्ण;

अटल काष्ठा kset *cpi_kset;

पूर्णांक sclp_cpi_set_data(स्थिर अक्षर *प्रणाली, स्थिर अक्षर *sysplex, स्थिर अक्षर *type,
		      स्थिर u64 level)
अणु
	पूर्णांक rc;

	rc = check_string("system_name", प्रणाली);
	अगर (rc)
		वापस rc;
	rc = check_string("sysplex_name", sysplex);
	अगर (rc)
		वापस rc;
	rc = check_string("system_type", type);
	अगर (rc)
		वापस rc;

	mutex_lock(&sclp_cpi_mutex);
	set_string(प्रणाली_name, प्रणाली);
	set_string(sysplex_name, sysplex);
	set_string(प्रणाली_type, type);
	प्रणाली_level = level;

	rc = cpi_req();
	mutex_unlock(&sclp_cpi_mutex);

	वापस rc;
पूर्ण
EXPORT_SYMBOL(sclp_cpi_set_data);

अटल पूर्णांक __init cpi_init(व्योम)
अणु
	पूर्णांक rc;

	cpi_kset = kset_create_and_add("cpi", शून्य, firmware_kobj);
	अगर (!cpi_kset)
		वापस -ENOMEM;

	rc = sysfs_create_group(&cpi_kset->kobj, &cpi_attr_group);
	अगर (rc)
		kset_unरेजिस्टर(cpi_kset);

	वापस rc;
पूर्ण

__initcall(cpi_init);
