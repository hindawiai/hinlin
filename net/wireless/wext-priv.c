<शैली गुरु>
/*
 * This file implement the Wireless Extensions priv API.
 *
 * Authors :	Jean Tourrilhes - HPL - <jt@hpl.hp.com>
 * Copyright (c) 1997-2007 Jean Tourrilhes, All Rights Reserved.
 * Copyright	2009 Johannes Berg <johannes@sipsolutions.net>
 *
 * (As all part of the Linux kernel, this file is GPL)
 */
#समावेश <linux/slab.h>
#समावेश <linux/wireless.h>
#समावेश <linux/netdevice.h>
#समावेश <net/iw_handler.h>
#समावेश <net/wext.h>

पूर्णांक iw_handler_get_निजी(काष्ठा net_device *		dev,
			   काष्ठा iw_request_info *	info,
			   जोड़ iwreq_data *		wrqu,
			   अक्षर *			extra)
अणु
	/* Check अगर the driver has something to export */
	अगर ((dev->wireless_handlers->num_निजी_args == 0) ||
	   (dev->wireless_handlers->निजी_args == शून्य))
		वापस -EOPNOTSUPP;

	/* Check अगर there is enough buffer up there */
	अगर (wrqu->data.length < dev->wireless_handlers->num_निजी_args) अणु
		/* User space can't know in advance how large the buffer
		 * needs to be. Give it a hपूर्णांक, so that we can support
		 * any size buffer we want somewhat efficiently... */
		wrqu->data.length = dev->wireless_handlers->num_निजी_args;
		वापस -E2BIG;
	पूर्ण

	/* Set the number of available ioctls. */
	wrqu->data.length = dev->wireless_handlers->num_निजी_args;

	/* Copy काष्ठाure to the user buffer. */
	स_नकल(extra, dev->wireless_handlers->निजी_args,
	       माप(काष्ठा iw_priv_args) * wrqu->data.length);

	वापस 0;
पूर्ण

/* Size (in bytes) of the various निजी data types */
अटल स्थिर अक्षर iw_priv_type_size[] = अणु
	0,				/* IW_PRIV_TYPE_NONE */
	1,				/* IW_PRIV_TYPE_BYTE */
	1,				/* IW_PRIV_TYPE_CHAR */
	0,				/* Not defined */
	माप(__u32),			/* IW_PRIV_TYPE_INT */
	माप(काष्ठा iw_freq),		/* IW_PRIV_TYPE_FLOAT */
	माप(काष्ठा sockaddr),	/* IW_PRIV_TYPE_ADDR */
	0,				/* Not defined */
पूर्ण;

अटल पूर्णांक get_priv_size(__u16 args)
अणु
	पूर्णांक	num = args & IW_PRIV_SIZE_MASK;
	पूर्णांक	type = (args & IW_PRIV_TYPE_MASK) >> 12;

	वापस num * iw_priv_type_size[type];
पूर्ण

अटल पूर्णांक adjust_priv_size(__u16 args, काष्ठा iw_poपूर्णांक *iwp)
अणु
	पूर्णांक	num = iwp->length;
	पूर्णांक	max = args & IW_PRIV_SIZE_MASK;
	पूर्णांक	type = (args & IW_PRIV_TYPE_MASK) >> 12;

	/* Make sure the driver करोesn't goof up */
	अगर (max < num)
		num = max;

	वापस num * iw_priv_type_size[type];
पूर्ण

/*
 * Wrapper to call a निजी Wireless Extension handler.
 * We करो various checks and also take care of moving data between
 * user space and kernel space.
 * It's not as nice and slimline as the standard wrapper. The cause
 * is काष्ठा iw_priv_args, which was not really deचिन्हित क्रम the
 * job we are going here.
 *
 * IMPORTANT : This function prevent to set and get data on the same
 * IOCTL and enक्रमce the SET/GET convention. Not करोing it would be
 * far too hairy...
 * If you need to set and get data at the same समय, please करोn't use
 * a iw_handler but process it in your ioctl handler (i.e. use the
 * old driver API).
 */
अटल पूर्णांक get_priv_descr_and_size(काष्ठा net_device *dev, अचिन्हित पूर्णांक cmd,
				   स्थिर काष्ठा iw_priv_args **descrp)
अणु
	स्थिर काष्ठा iw_priv_args *descr;
	पूर्णांक i, extra_size;

	descr = शून्य;
	क्रम (i = 0; i < dev->wireless_handlers->num_निजी_args; i++) अणु
		अगर (cmd == dev->wireless_handlers->निजी_args[i].cmd) अणु
			descr = &dev->wireless_handlers->निजी_args[i];
			अवरोध;
		पूर्ण
	पूर्ण

	extra_size = 0;
	अगर (descr) अणु
		अगर (IW_IS_SET(cmd)) अणु
			पूर्णांक	offset = 0;	/* For sub-ioctls */
			/* Check क्रम sub-ioctl handler */
			अगर (descr->name[0] == '\0')
				/* Reserve one पूर्णांक क्रम sub-ioctl index */
				offset = माप(__u32);

			/* Size of set arguments */
			extra_size = get_priv_size(descr->set_args);

			/* Does it fits in iwr ? */
			अगर ((descr->set_args & IW_PRIV_SIZE_FIXED) &&
			   ((extra_size + offset) <= IFNAMSIZ))
				extra_size = 0;
		पूर्ण अन्यथा अणु
			/* Size of get arguments */
			extra_size = get_priv_size(descr->get_args);

			/* Does it fits in iwr ? */
			अगर ((descr->get_args & IW_PRIV_SIZE_FIXED) &&
			   (extra_size <= IFNAMSIZ))
				extra_size = 0;
		पूर्ण
	पूर्ण
	*descrp = descr;
	वापस extra_size;
पूर्ण

अटल पूर्णांक ioctl_निजी_iw_poपूर्णांक(काष्ठा iw_poपूर्णांक *iwp, अचिन्हित पूर्णांक cmd,
				  स्थिर काष्ठा iw_priv_args *descr,
				  iw_handler handler, काष्ठा net_device *dev,
				  काष्ठा iw_request_info *info, पूर्णांक extra_size)
अणु
	अक्षर *extra;
	पूर्णांक err;

	/* Check what user space is giving us */
	अगर (IW_IS_SET(cmd)) अणु
		अगर (!iwp->poपूर्णांकer && iwp->length != 0)
			वापस -EFAULT;

		अगर (iwp->length > (descr->set_args & IW_PRIV_SIZE_MASK))
			वापस -E2BIG;
	पूर्ण अन्यथा अगर (!iwp->poपूर्णांकer)
		वापस -EFAULT;

	extra = kzalloc(extra_size, GFP_KERNEL);
	अगर (!extra)
		वापस -ENOMEM;

	/* If it is a SET, get all the extra data in here */
	अगर (IW_IS_SET(cmd) && (iwp->length != 0)) अणु
		अगर (copy_from_user(extra, iwp->poपूर्णांकer, extra_size)) अणु
			err = -EFAULT;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Call the handler */
	err = handler(dev, info, (जोड़ iwreq_data *) iwp, extra);

	/* If we have something to वापस to the user */
	अगर (!err && IW_IS_GET(cmd)) अणु
		/* Adjust क्रम the actual length अगर it's variable,
		 * aव्योम leaking kernel bits outside.
		 */
		अगर (!(descr->get_args & IW_PRIV_SIZE_FIXED))
			extra_size = adjust_priv_size(descr->get_args, iwp);

		अगर (copy_to_user(iwp->poपूर्णांकer, extra, extra_size))
			err =  -EFAULT;
	पूर्ण

out:
	kमुक्त(extra);
	वापस err;
पूर्ण

पूर्णांक ioctl_निजी_call(काष्ठा net_device *dev, काष्ठा iwreq *iwr,
		       अचिन्हित पूर्णांक cmd, काष्ठा iw_request_info *info,
		       iw_handler handler)
अणु
	पूर्णांक extra_size = 0, ret = -EINVAL;
	स्थिर काष्ठा iw_priv_args *descr;

	extra_size = get_priv_descr_and_size(dev, cmd, &descr);

	/* Check अगर we have a poपूर्णांकer to user space data or not. */
	अगर (extra_size == 0) अणु
		/* No extra arguments. Trivial to handle */
		ret = handler(dev, info, &(iwr->u), (अक्षर *) &(iwr->u));
	पूर्ण अन्यथा अणु
		ret = ioctl_निजी_iw_poपूर्णांक(&iwr->u.data, cmd, descr,
					     handler, dev, info, extra_size);
	पूर्ण

	/* Call commit handler अगर needed and defined */
	अगर (ret == -EIWCOMMIT)
		ret = call_commit_handler(dev);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
पूर्णांक compat_निजी_call(काष्ठा net_device *dev, काष्ठा iwreq *iwr,
			अचिन्हित पूर्णांक cmd, काष्ठा iw_request_info *info,
			iw_handler handler)
अणु
	स्थिर काष्ठा iw_priv_args *descr;
	पूर्णांक ret, extra_size;

	extra_size = get_priv_descr_and_size(dev, cmd, &descr);

	/* Check अगर we have a poपूर्णांकer to user space data or not. */
	अगर (extra_size == 0) अणु
		/* No extra arguments. Trivial to handle */
		ret = handler(dev, info, &(iwr->u), (अक्षर *) &(iwr->u));
	पूर्ण अन्यथा अणु
		काष्ठा compat_iw_poपूर्णांक *iwp_compat;
		काष्ठा iw_poपूर्णांक iwp;

		iwp_compat = (काष्ठा compat_iw_poपूर्णांक *) &iwr->u.data;
		iwp.poपूर्णांकer = compat_ptr(iwp_compat->poपूर्णांकer);
		iwp.length = iwp_compat->length;
		iwp.flags = iwp_compat->flags;

		ret = ioctl_निजी_iw_poपूर्णांक(&iwp, cmd, descr,
					     handler, dev, info, extra_size);

		iwp_compat->poपूर्णांकer = ptr_to_compat(iwp.poपूर्णांकer);
		iwp_compat->length = iwp.length;
		iwp_compat->flags = iwp.flags;
	पूर्ण

	/* Call commit handler अगर needed and defined */
	अगर (ret == -EIWCOMMIT)
		ret = call_commit_handler(dev);

	वापस ret;
पूर्ण
#पूर्ण_अगर
