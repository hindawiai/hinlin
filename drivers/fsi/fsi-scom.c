<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * SCOM FSI Client device driver
 *
 * Copyright (C) IBM Corporation 2016
 */

#समावेश <linux/fsi.h>
#समावेश <linux/module.h>
#समावेश <linux/cdev.h>
#समावेश <linux/delay.h>
#समावेश <linux/fs.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>

#समावेश <uapi/linux/fsi.h>

#घोषणा FSI_ENGID_SCOM		0x5

/* SCOM engine रेजिस्टर set */
#घोषणा SCOM_DATA0_REG		0x00
#घोषणा SCOM_DATA1_REG		0x04
#घोषणा SCOM_CMD_REG		0x08
#घोषणा SCOM_FSI2PIB_RESET_REG	0x18
#घोषणा SCOM_STATUS_REG		0x1C /* Read */
#घोषणा SCOM_PIB_RESET_REG	0x1C /* Write */

/* Command रेजिस्टर */
#घोषणा SCOM_WRITE_CMD		0x80000000
#घोषणा SCOM_READ_CMD		0x00000000

/* Status रेजिस्टर bits */
#घोषणा SCOM_STATUS_ERR_SUMMARY		0x80000000
#घोषणा SCOM_STATUS_PROTECTION		0x01000000
#घोषणा SCOM_STATUS_PARITY		0x04000000
#घोषणा SCOM_STATUS_PIB_ABORT		0x00100000
#घोषणा SCOM_STATUS_PIB_RESP_MASK	0x00007000
#घोषणा SCOM_STATUS_PIB_RESP_SHIFT	12

#घोषणा SCOM_STATUS_ANY_ERR		(SCOM_STATUS_PROTECTION | \
					 SCOM_STATUS_PARITY |	  \
					 SCOM_STATUS_PIB_ABORT | \
					 SCOM_STATUS_PIB_RESP_MASK)
/* SCOM address encodings */
#घोषणा XSCOM_ADDR_IND_FLAG		BIT_ULL(63)
#घोषणा XSCOM_ADDR_INF_FORM1		BIT_ULL(60)

/* SCOM indirect stuff */
#घोषणा XSCOM_ADDR_सूचीECT_PART		0x7fffffffull
#घोषणा XSCOM_ADDR_INसूचीECT_PART	0x000fffff00000000ull
#घोषणा XSCOM_DATA_IND_READ		BIT_ULL(63)
#घोषणा XSCOM_DATA_IND_COMPLETE		BIT_ULL(31)
#घोषणा XSCOM_DATA_IND_ERR_MASK		0x70000000ull
#घोषणा XSCOM_DATA_IND_ERR_SHIFT	28
#घोषणा XSCOM_DATA_IND_DATA		0x0000ffffull
#घोषणा XSCOM_DATA_IND_FORM1_DATA	0x000fffffffffffffull
#घोषणा XSCOM_ADDR_FORM1_LOW		0x000ffffffffull
#घोषणा XSCOM_ADDR_FORM1_HI		0xfff00000000ull
#घोषणा XSCOM_ADDR_FORM1_HI_SHIFT	20

/* Retries */
#घोषणा SCOM_MAX_RETRIES		100	/* Retries on busy */
#घोषणा SCOM_MAX_IND_RETRIES		10	/* Retries indirect not पढ़ोy */

काष्ठा scom_device अणु
	काष्ठा list_head link;
	काष्ठा fsi_device *fsi_dev;
	काष्ठा device dev;
	काष्ठा cdev cdev;
	काष्ठा mutex lock;
	bool dead;
पूर्ण;

अटल पूर्णांक __put_scom(काष्ठा scom_device *scom_dev, uपूर्णांक64_t value,
		      uपूर्णांक32_t addr, uपूर्णांक32_t *status)
अणु
	__be32 data, raw_status;
	पूर्णांक rc;

	data = cpu_to_be32((value >> 32) & 0xffffffff);
	rc = fsi_device_ग_लिखो(scom_dev->fsi_dev, SCOM_DATA0_REG, &data,
				माप(uपूर्णांक32_t));
	अगर (rc)
		वापस rc;

	data = cpu_to_be32(value & 0xffffffff);
	rc = fsi_device_ग_लिखो(scom_dev->fsi_dev, SCOM_DATA1_REG, &data,
				माप(uपूर्णांक32_t));
	अगर (rc)
		वापस rc;

	data = cpu_to_be32(SCOM_WRITE_CMD | addr);
	rc = fsi_device_ग_लिखो(scom_dev->fsi_dev, SCOM_CMD_REG, &data,
				माप(uपूर्णांक32_t));
	अगर (rc)
		वापस rc;
	rc = fsi_device_पढ़ो(scom_dev->fsi_dev, SCOM_STATUS_REG, &raw_status,
			     माप(uपूर्णांक32_t));
	अगर (rc)
		वापस rc;
	*status = be32_to_cpu(raw_status);

	वापस 0;
पूर्ण

अटल पूर्णांक __get_scom(काष्ठा scom_device *scom_dev, uपूर्णांक64_t *value,
		      uपूर्णांक32_t addr, uपूर्णांक32_t *status)
अणु
	__be32 data, raw_status;
	पूर्णांक rc;


	*value = 0ULL;
	data = cpu_to_be32(SCOM_READ_CMD | addr);
	rc = fsi_device_ग_लिखो(scom_dev->fsi_dev, SCOM_CMD_REG, &data,
				माप(uपूर्णांक32_t));
	अगर (rc)
		वापस rc;
	rc = fsi_device_पढ़ो(scom_dev->fsi_dev, SCOM_STATUS_REG, &raw_status,
			     माप(uपूर्णांक32_t));
	अगर (rc)
		वापस rc;

	/*
	 * Read the data रेजिस्टरs even on error, so we करोn't have
	 * to पूर्णांकerpret the status रेजिस्टर here.
	 */
	rc = fsi_device_पढ़ो(scom_dev->fsi_dev, SCOM_DATA0_REG, &data,
				माप(uपूर्णांक32_t));
	अगर (rc)
		वापस rc;
	*value |= (uपूर्णांक64_t)be32_to_cpu(data) << 32;
	rc = fsi_device_पढ़ो(scom_dev->fsi_dev, SCOM_DATA1_REG, &data,
				माप(uपूर्णांक32_t));
	अगर (rc)
		वापस rc;
	*value |= be32_to_cpu(data);
	*status = be32_to_cpu(raw_status);

	वापस rc;
पूर्ण

अटल पूर्णांक put_indirect_scom_क्रमm0(काष्ठा scom_device *scom, uपूर्णांक64_t value,
				   uपूर्णांक64_t addr, uपूर्णांक32_t *status)
अणु
	uपूर्णांक64_t ind_data, ind_addr;
	पूर्णांक rc, retries, err = 0;

	अगर (value & ~XSCOM_DATA_IND_DATA)
		वापस -EINVAL;

	ind_addr = addr & XSCOM_ADDR_सूचीECT_PART;
	ind_data = (addr & XSCOM_ADDR_INसूचीECT_PART) | value;
	rc = __put_scom(scom, ind_data, ind_addr, status);
	अगर (rc || (*status & SCOM_STATUS_ANY_ERR))
		वापस rc;

	क्रम (retries = 0; retries < SCOM_MAX_IND_RETRIES; retries++) अणु
		rc = __get_scom(scom, &ind_data, addr, status);
		अगर (rc || (*status & SCOM_STATUS_ANY_ERR))
			वापस rc;

		err = (ind_data & XSCOM_DATA_IND_ERR_MASK) >> XSCOM_DATA_IND_ERR_SHIFT;
		*status = err << SCOM_STATUS_PIB_RESP_SHIFT;
		अगर ((ind_data & XSCOM_DATA_IND_COMPLETE) || (err != SCOM_PIB_BLOCKED))
			वापस 0;

		msleep(1);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक put_indirect_scom_क्रमm1(काष्ठा scom_device *scom, uपूर्णांक64_t value,
				   uपूर्णांक64_t addr, uपूर्णांक32_t *status)
अणु
	uपूर्णांक64_t ind_data, ind_addr;

	अगर (value & ~XSCOM_DATA_IND_FORM1_DATA)
		वापस -EINVAL;

	ind_addr = addr & XSCOM_ADDR_FORM1_LOW;
	ind_data = value | (addr & XSCOM_ADDR_FORM1_HI) << XSCOM_ADDR_FORM1_HI_SHIFT;
	वापस __put_scom(scom, ind_data, ind_addr, status);
पूर्ण

अटल पूर्णांक get_indirect_scom_क्रमm0(काष्ठा scom_device *scom, uपूर्णांक64_t *value,
				   uपूर्णांक64_t addr, uपूर्णांक32_t *status)
अणु
	uपूर्णांक64_t ind_data, ind_addr;
	पूर्णांक rc, retries, err = 0;

	ind_addr = addr & XSCOM_ADDR_सूचीECT_PART;
	ind_data = (addr & XSCOM_ADDR_INसूचीECT_PART) | XSCOM_DATA_IND_READ;
	rc = __put_scom(scom, ind_data, ind_addr, status);
	अगर (rc || (*status & SCOM_STATUS_ANY_ERR))
		वापस rc;

	क्रम (retries = 0; retries < SCOM_MAX_IND_RETRIES; retries++) अणु
		rc = __get_scom(scom, &ind_data, addr, status);
		अगर (rc || (*status & SCOM_STATUS_ANY_ERR))
			वापस rc;

		err = (ind_data & XSCOM_DATA_IND_ERR_MASK) >> XSCOM_DATA_IND_ERR_SHIFT;
		*status = err << SCOM_STATUS_PIB_RESP_SHIFT;
		*value = ind_data & XSCOM_DATA_IND_DATA;

		अगर ((ind_data & XSCOM_DATA_IND_COMPLETE) || (err != SCOM_PIB_BLOCKED))
			वापस 0;

		msleep(1);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक raw_put_scom(काष्ठा scom_device *scom, uपूर्णांक64_t value,
			uपूर्णांक64_t addr, uपूर्णांक32_t *status)
अणु
	अगर (addr & XSCOM_ADDR_IND_FLAG) अणु
		अगर (addr & XSCOM_ADDR_INF_FORM1)
			वापस put_indirect_scom_क्रमm1(scom, value, addr, status);
		अन्यथा
			वापस put_indirect_scom_क्रमm0(scom, value, addr, status);
	पूर्ण अन्यथा
		वापस __put_scom(scom, value, addr, status);
पूर्ण

अटल पूर्णांक raw_get_scom(काष्ठा scom_device *scom, uपूर्णांक64_t *value,
			uपूर्णांक64_t addr, uपूर्णांक32_t *status)
अणु
	अगर (addr & XSCOM_ADDR_IND_FLAG) अणु
		अगर (addr & XSCOM_ADDR_INF_FORM1)
			वापस -ENXIO;
		वापस get_indirect_scom_क्रमm0(scom, value, addr, status);
	पूर्ण अन्यथा
		वापस __get_scom(scom, value, addr, status);
पूर्ण

अटल पूर्णांक handle_fsi2pib_status(काष्ठा scom_device *scom, uपूर्णांक32_t status)
अणु
	uपूर्णांक32_t dummy = -1;

	अगर (status & SCOM_STATUS_PROTECTION)
		वापस -EPERM;
	अगर (status & SCOM_STATUS_PARITY) अणु
		fsi_device_ग_लिखो(scom->fsi_dev, SCOM_FSI2PIB_RESET_REG, &dummy,
				 माप(uपूर्णांक32_t));
		वापस -EIO;
	पूर्ण
	/* Return -EBUSY on PIB पात to क्रमce a retry */
	अगर (status & SCOM_STATUS_PIB_ABORT)
		वापस -EBUSY;
	वापस 0;
पूर्ण

अटल पूर्णांक handle_pib_status(काष्ठा scom_device *scom, uपूर्णांक8_t status)
अणु
	uपूर्णांक32_t dummy = -1;

	अगर (status == SCOM_PIB_SUCCESS)
		वापस 0;
	अगर (status == SCOM_PIB_BLOCKED)
		वापस -EBUSY;

	/* Reset the bridge */
	fsi_device_ग_लिखो(scom->fsi_dev, SCOM_FSI2PIB_RESET_REG, &dummy,
			 माप(uपूर्णांक32_t));

	चयन(status) अणु
	हाल SCOM_PIB_OFFLINE:
		वापस -ENODEV;
	हाल SCOM_PIB_BAD_ADDR:
		वापस -ENXIO;
	हाल SCOM_PIB_TIMEOUT:
		वापस -ETIMEDOUT;
	हाल SCOM_PIB_PARTIAL:
	हाल SCOM_PIB_CLK_ERR:
	हाल SCOM_PIB_PARITY_ERR:
	शेष:
		वापस -EIO;
	पूर्ण
पूर्ण

अटल पूर्णांक put_scom(काष्ठा scom_device *scom, uपूर्णांक64_t value,
		    uपूर्णांक64_t addr)
अणु
	uपूर्णांक32_t status, dummy = -1;
	पूर्णांक rc, retries;

	क्रम (retries = 0; retries < SCOM_MAX_RETRIES; retries++) अणु
		rc = raw_put_scom(scom, value, addr, &status);
		अगर (rc) अणु
			/* Try resetting the bridge अगर FSI fails */
			अगर (rc != -ENODEV && retries == 0) अणु
				fsi_device_ग_लिखो(scom->fsi_dev, SCOM_FSI2PIB_RESET_REG,
						 &dummy, माप(uपूर्णांक32_t));
				rc = -EBUSY;
			पूर्ण अन्यथा
				वापस rc;
		पूर्ण अन्यथा
			rc = handle_fsi2pib_status(scom, status);
		अगर (rc && rc != -EBUSY)
			अवरोध;
		अगर (rc == 0) अणु
			rc = handle_pib_status(scom,
					       (status & SCOM_STATUS_PIB_RESP_MASK)
					       >> SCOM_STATUS_PIB_RESP_SHIFT);
			अगर (rc && rc != -EBUSY)
				अवरोध;
		पूर्ण
		अगर (rc == 0)
			अवरोध;
		msleep(1);
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक get_scom(काष्ठा scom_device *scom, uपूर्णांक64_t *value,
		    uपूर्णांक64_t addr)
अणु
	uपूर्णांक32_t status, dummy = -1;
	पूर्णांक rc, retries;

	क्रम (retries = 0; retries < SCOM_MAX_RETRIES; retries++) अणु
		rc = raw_get_scom(scom, value, addr, &status);
		अगर (rc) अणु
			/* Try resetting the bridge अगर FSI fails */
			अगर (rc != -ENODEV && retries == 0) अणु
				fsi_device_ग_लिखो(scom->fsi_dev, SCOM_FSI2PIB_RESET_REG,
						 &dummy, माप(uपूर्णांक32_t));
				rc = -EBUSY;
			पूर्ण अन्यथा
				वापस rc;
		पूर्ण अन्यथा
			rc = handle_fsi2pib_status(scom, status);
		अगर (rc && rc != -EBUSY)
			अवरोध;
		अगर (rc == 0) अणु
			rc = handle_pib_status(scom,
					       (status & SCOM_STATUS_PIB_RESP_MASK)
					       >> SCOM_STATUS_PIB_RESP_SHIFT);
			अगर (rc && rc != -EBUSY)
				अवरोध;
		पूर्ण
		अगर (rc == 0)
			अवरोध;
		msleep(1);
	पूर्ण
	वापस rc;
पूर्ण

अटल sमाप_प्रकार scom_पढ़ो(काष्ठा file *filep, अक्षर __user *buf, माप_प्रकार len,
			 loff_t *offset)
अणु
	काष्ठा scom_device *scom = filep->निजी_data;
	काष्ठा device *dev = &scom->fsi_dev->dev;
	uपूर्णांक64_t val;
	पूर्णांक rc;

	अगर (len != माप(uपूर्णांक64_t))
		वापस -EINVAL;

	mutex_lock(&scom->lock);
	अगर (scom->dead)
		rc = -ENODEV;
	अन्यथा
		rc = get_scom(scom, &val, *offset);
	mutex_unlock(&scom->lock);
	अगर (rc) अणु
		dev_dbg(dev, "get_scom fail:%d\n", rc);
		वापस rc;
	पूर्ण

	rc = copy_to_user(buf, &val, len);
	अगर (rc)
		dev_dbg(dev, "copy to user failed:%d\n", rc);

	वापस rc ? rc : len;
पूर्ण

अटल sमाप_प्रकार scom_ग_लिखो(काष्ठा file *filep, स्थिर अक्षर __user *buf,
			  माप_प्रकार len, loff_t *offset)
अणु
	पूर्णांक rc;
	काष्ठा scom_device *scom = filep->निजी_data;
	काष्ठा device *dev = &scom->fsi_dev->dev;
	uपूर्णांक64_t val;

	अगर (len != माप(uपूर्णांक64_t))
		वापस -EINVAL;

	rc = copy_from_user(&val, buf, len);
	अगर (rc) अणु
		dev_dbg(dev, "copy from user failed:%d\n", rc);
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&scom->lock);
	अगर (scom->dead)
		rc = -ENODEV;
	अन्यथा
		rc = put_scom(scom, val, *offset);
	mutex_unlock(&scom->lock);
	अगर (rc) अणु
		dev_dbg(dev, "put_scom failed with:%d\n", rc);
		वापस rc;
	पूर्ण

	वापस len;
पूर्ण

अटल loff_t scom_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	चयन (whence) अणु
	हाल प्रस्तुत_से:
		अवरोध;
	हाल शुरू_से:
		file->f_pos = offset;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस offset;
पूर्ण

अटल व्योम raw_convert_status(काष्ठा scom_access *acc, uपूर्णांक32_t status)
अणु
	acc->pib_status = (status & SCOM_STATUS_PIB_RESP_MASK) >>
		SCOM_STATUS_PIB_RESP_SHIFT;
	acc->पूर्णांकf_errors = 0;

	अगर (status & SCOM_STATUS_PROTECTION)
		acc->पूर्णांकf_errors |= SCOM_INTF_ERR_PROTECTION;
	अन्यथा अगर (status & SCOM_STATUS_PARITY)
		acc->पूर्णांकf_errors |= SCOM_INTF_ERR_PARITY;
	अन्यथा अगर (status & SCOM_STATUS_PIB_ABORT)
		acc->पूर्णांकf_errors |= SCOM_INTF_ERR_ABORT;
	अन्यथा अगर (status & SCOM_STATUS_ERR_SUMMARY)
		acc->पूर्णांकf_errors |= SCOM_INTF_ERR_UNKNOWN;
पूर्ण

अटल पूर्णांक scom_raw_पढ़ो(काष्ठा scom_device *scom, व्योम __user *argp)
अणु
	काष्ठा scom_access acc;
	uपूर्णांक32_t status;
	पूर्णांक rc;

	अगर (copy_from_user(&acc, argp, माप(काष्ठा scom_access)))
		वापस -EFAULT;

	rc = raw_get_scom(scom, &acc.data, acc.addr, &status);
	अगर (rc)
		वापस rc;
	raw_convert_status(&acc, status);
	अगर (copy_to_user(argp, &acc, माप(काष्ठा scom_access)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक scom_raw_ग_लिखो(काष्ठा scom_device *scom, व्योम __user *argp)
अणु
	u64 prev_data, mask, data;
	काष्ठा scom_access acc;
	uपूर्णांक32_t status;
	पूर्णांक rc;

	अगर (copy_from_user(&acc, argp, माप(काष्ठा scom_access)))
		वापस -EFAULT;

	अगर (acc.mask) अणु
		rc = raw_get_scom(scom, &prev_data, acc.addr, &status);
		अगर (rc)
			वापस rc;
		अगर (status & SCOM_STATUS_ANY_ERR)
			जाओ fail;
		mask = acc.mask;
	पूर्ण अन्यथा अणु
		prev_data = mask = -1ull;
	पूर्ण
	data = (prev_data & ~mask) | (acc.data & mask);
	rc = raw_put_scom(scom, data, acc.addr, &status);
	अगर (rc)
		वापस rc;
 fail:
	raw_convert_status(&acc, status);
	अगर (copy_to_user(argp, &acc, माप(काष्ठा scom_access)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक scom_reset(काष्ठा scom_device *scom, व्योम __user *argp)
अणु
	uपूर्णांक32_t flags, dummy = -1;
	पूर्णांक rc = 0;

	अगर (get_user(flags, (__u32 __user *)argp))
		वापस -EFAULT;
	अगर (flags & SCOM_RESET_PIB)
		rc = fsi_device_ग_लिखो(scom->fsi_dev, SCOM_PIB_RESET_REG, &dummy,
				      माप(uपूर्णांक32_t));
	अगर (!rc && (flags & (SCOM_RESET_PIB | SCOM_RESET_INTF)))
		rc = fsi_device_ग_लिखो(scom->fsi_dev, SCOM_FSI2PIB_RESET_REG, &dummy,
				      माप(uपूर्णांक32_t));
	वापस rc;
पूर्ण

अटल पूर्णांक scom_check(काष्ठा scom_device *scom, व्योम __user *argp)
अणु
	/* Still need to find out how to get "protected" */
	वापस put_user(SCOM_CHECK_SUPPORTED, (__u32 __user *)argp);
पूर्ण

अटल दीर्घ scom_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा scom_device *scom = file->निजी_data;
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक rc = -ENOTTY;

	mutex_lock(&scom->lock);
	अगर (scom->dead) अणु
		mutex_unlock(&scom->lock);
		वापस -ENODEV;
	पूर्ण
	चयन(cmd) अणु
	हाल FSI_SCOM_CHECK:
		rc = scom_check(scom, argp);
		अवरोध;
	हाल FSI_SCOM_READ:
		rc = scom_raw_पढ़ो(scom, argp);
		अवरोध;
	हाल FSI_SCOM_WRITE:
		rc = scom_raw_ग_लिखो(scom, argp);
		अवरोध;
	हाल FSI_SCOM_RESET:
		rc = scom_reset(scom, argp);
		अवरोध;
	पूर्ण
	mutex_unlock(&scom->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक scom_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा scom_device *scom = container_of(inode->i_cdev, काष्ठा scom_device, cdev);

	file->निजी_data = scom;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations scom_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= scom_खोलो,
	.llseek		= scom_llseek,
	.पढ़ो		= scom_पढ़ो,
	.ग_लिखो		= scom_ग_लिखो,
	.unlocked_ioctl	= scom_ioctl,
पूर्ण;

अटल व्योम scom_मुक्त(काष्ठा device *dev)
अणु
	काष्ठा scom_device *scom = container_of(dev, काष्ठा scom_device, dev);

	put_device(&scom->fsi_dev->dev);
	kमुक्त(scom);
पूर्ण

अटल पूर्णांक scom_probe(काष्ठा device *dev)
अणु
	काष्ठा fsi_device *fsi_dev = to_fsi_dev(dev);
	काष्ठा scom_device *scom;
	पूर्णांक rc, didx;

	scom = kzalloc(माप(*scom), GFP_KERNEL);
	अगर (!scom)
		वापस -ENOMEM;
	dev_set_drvdata(dev, scom);
	mutex_init(&scom->lock);

	/* Grab a reference to the device (parent of our cdev), we'll drop it later */
	अगर (!get_device(dev)) अणु
		kमुक्त(scom);
		वापस -ENODEV;
	पूर्ण
	scom->fsi_dev = fsi_dev;

	/* Create अक्षरdev क्रम userspace access */
	scom->dev.type = &fsi_cdev_type;
	scom->dev.parent = dev;
	scom->dev.release = scom_मुक्त;
	device_initialize(&scom->dev);

	/* Allocate a minor in the FSI space */
	rc = fsi_get_new_minor(fsi_dev, fsi_dev_scom, &scom->dev.devt, &didx);
	अगर (rc)
		जाओ err;

	dev_set_name(&scom->dev, "scom%d", didx);
	cdev_init(&scom->cdev, &scom_fops);
	rc = cdev_device_add(&scom->cdev, &scom->dev);
	अगर (rc) अणु
		dev_err(dev, "Error %d creating char device %s\n",
			rc, dev_name(&scom->dev));
		जाओ err_मुक्त_minor;
	पूर्ण

	वापस 0;
 err_मुक्त_minor:
	fsi_मुक्त_minor(scom->dev.devt);
 err:
	put_device(&scom->dev);
	वापस rc;
पूर्ण

अटल पूर्णांक scom_हटाओ(काष्ठा device *dev)
अणु
	काष्ठा scom_device *scom = dev_get_drvdata(dev);

	mutex_lock(&scom->lock);
	scom->dead = true;
	mutex_unlock(&scom->lock);
	cdev_device_del(&scom->cdev, &scom->dev);
	fsi_मुक्त_minor(scom->dev.devt);
	put_device(&scom->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा fsi_device_id scom_ids[] = अणु
	अणु
		.engine_type = FSI_ENGID_SCOM,
		.version = FSI_VERSION_ANY,
	पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल काष्ठा fsi_driver scom_drv = अणु
	.id_table = scom_ids,
	.drv = अणु
		.name = "scom",
		.bus = &fsi_bus_type,
		.probe = scom_probe,
		.हटाओ = scom_हटाओ,
	पूर्ण
पूर्ण;

अटल पूर्णांक scom_init(व्योम)
अणु
	वापस fsi_driver_रेजिस्टर(&scom_drv);
पूर्ण

अटल व्योम scom_निकास(व्योम)
अणु
	fsi_driver_unरेजिस्टर(&scom_drv);
पूर्ण

module_init(scom_init);
module_निकास(scom_निकास);
MODULE_LICENSE("GPL");
