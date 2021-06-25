<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Media device node
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 *
 * --
 *
 * Common functions क्रम media-related drivers to रेजिस्टर and unरेजिस्टर media
 * device nodes.
 */

#अगर_अघोषित _MEDIA_DEVNODE_H
#घोषणा _MEDIA_DEVNODE_H

#समावेश <linux/poll.h>
#समावेश <linux/fs.h>
#समावेश <linux/device.h>
#समावेश <linux/cdev.h>

काष्ठा media_device;

/*
 * Flag to mark the media_devnode काष्ठा as रेजिस्टरed. Drivers must not touch
 * this flag directly, it will be set and cleared by media_devnode_रेजिस्टर and
 * media_devnode_unरेजिस्टर.
 */
#घोषणा MEDIA_FLAG_REGISTERED	0

/**
 * काष्ठा media_file_operations - Media device file operations
 *
 * @owner: should be filled with %THIS_MODULE
 * @पढ़ो: poपूर्णांकer to the function that implements पढ़ो() syscall
 * @ग_लिखो: poपूर्णांकer to the function that implements ग_लिखो() syscall
 * @poll: poपूर्णांकer to the function that implements poll() syscall
 * @ioctl: poपूर्णांकer to the function that implements ioctl() syscall
 * @compat_ioctl: poपूर्णांकer to the function that will handle 32 bits userspace
 *	calls to the ioctl() syscall on a Kernel compiled with 64 bits.
 * @खोलो: poपूर्णांकer to the function that implements खोलो() syscall
 * @release: poपूर्णांकer to the function that will release the resources allocated
 *	by the @खोलो function.
 */
काष्ठा media_file_operations अणु
	काष्ठा module *owner;
	sमाप_प्रकार (*पढ़ो) (काष्ठा file *, अक्षर __user *, माप_प्रकार, loff_t *);
	sमाप_प्रकार (*ग_लिखो) (काष्ठा file *, स्थिर अक्षर __user *, माप_प्रकार, loff_t *);
	__poll_t (*poll) (काष्ठा file *, काष्ठा poll_table_काष्ठा *);
	दीर्घ (*ioctl) (काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
	दीर्घ (*compat_ioctl) (काष्ठा file *, अचिन्हित पूर्णांक, अचिन्हित दीर्घ);
	पूर्णांक (*खोलो) (काष्ठा file *);
	पूर्णांक (*release) (काष्ठा file *);
पूर्ण;

/**
 * काष्ठा media_devnode - Media device node
 * @media_dev:	poपूर्णांकer to काष्ठा &media_device
 * @fops:	poपूर्णांकer to काष्ठा &media_file_operations with media device ops
 * @dev:	poपूर्णांकer to काष्ठा &device containing the media controller device
 * @cdev:	काष्ठा cdev poपूर्णांकer अक्षरacter device
 * @parent:	parent device
 * @minor:	device node minor number
 * @flags:	flags, combination of the ``MEDIA_FLAG_*`` स्थिरants
 * @release:	release callback called at the end of ``media_devnode_release()``
 *		routine at media-device.c.
 *
 * This काष्ठाure represents a media-related device node.
 *
 * The @parent is a physical device. It must be set by core or device drivers
 * beक्रमe रेजिस्टरing the node.
 */
काष्ठा media_devnode अणु
	काष्ठा media_device *media_dev;

	/* device ops */
	स्थिर काष्ठा media_file_operations *fops;

	/* sysfs */
	काष्ठा device dev;		/* media device */
	काष्ठा cdev cdev;		/* अक्षरacter device */
	काष्ठा device *parent;		/* device parent */

	/* device info */
	पूर्णांक minor;
	अचिन्हित दीर्घ flags;		/* Use bitops to access flags */

	/* callbacks */
	व्योम (*release)(काष्ठा media_devnode *devnode);
पूर्ण;

/* dev to media_devnode */
#घोषणा to_media_devnode(cd) container_of(cd, काष्ठा media_devnode, dev)

/**
 * media_devnode_रेजिस्टर - रेजिस्टर a media device node
 *
 * @mdev: काष्ठा media_device we want to रेजिस्टर a device node
 * @devnode: media device node काष्ठाure we want to रेजिस्टर
 * @owner: should be filled with %THIS_MODULE
 *
 * The registration code assigns minor numbers and रेजिस्टरs the new device node
 * with the kernel. An error is वापसed अगर no मुक्त minor number can be found,
 * or अगर the registration of the device node fails.
 *
 * Zero is वापसed on success.
 *
 * Note that अगर the media_devnode_रेजिस्टर call fails, the release() callback of
 * the media_devnode काष्ठाure is *not* called, so the caller is responsible क्रम
 * मुक्तing any data.
 */
पूर्णांक __must_check media_devnode_रेजिस्टर(काष्ठा media_device *mdev,
					काष्ठा media_devnode *devnode,
					काष्ठा module *owner);

/**
 * media_devnode_unरेजिस्टर_prepare - clear the media device node रेजिस्टर bit
 * @devnode: the device node to prepare क्रम unरेजिस्टर
 *
 * This clears the passed device रेजिस्टर bit. Future खोलो calls will be met
 * with errors. Should be called beक्रमe media_devnode_unरेजिस्टर() to aव्योम
 * races with unरेजिस्टर and device file खोलो calls.
 *
 * This function can safely be called अगर the device node has never been
 * रेजिस्टरed or has alपढ़ोy been unरेजिस्टरed.
 */
व्योम media_devnode_unरेजिस्टर_prepare(काष्ठा media_devnode *devnode);

/**
 * media_devnode_unरेजिस्टर - unरेजिस्टर a media device node
 * @devnode: the device node to unरेजिस्टर
 *
 * This unरेजिस्टरs the passed device. Future खोलो calls will be met with
 * errors.
 *
 * Should be called after media_devnode_unरेजिस्टर_prepare()
 */
व्योम media_devnode_unरेजिस्टर(काष्ठा media_devnode *devnode);

/**
 * media_devnode_data - वापसs a poपूर्णांकer to the &media_devnode
 *
 * @filp: poपूर्णांकer to काष्ठा &file
 */
अटल अंतरभूत काष्ठा media_devnode *media_devnode_data(काष्ठा file *filp)
अणु
	वापस filp->निजी_data;
पूर्ण

/**
 * media_devnode_is_रेजिस्टरed - वापसs true अगर &media_devnode is रेजिस्टरed;
 *	false otherwise.
 *
 * @devnode: poपूर्णांकer to काष्ठा &media_devnode.
 *
 * Note: If mdev is शून्य, it also वापसs false.
 */
अटल अंतरभूत पूर्णांक media_devnode_is_रेजिस्टरed(काष्ठा media_devnode *devnode)
अणु
	अगर (!devnode)
		वापस false;

	वापस test_bit(MEDIA_FLAG_REGISTERED, &devnode->flags);
पूर्ण

#पूर्ण_अगर /* _MEDIA_DEVNODE_H */
