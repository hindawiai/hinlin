<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * posix-घड़ी.h - support क्रम dynamic घड़ी devices
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 */
#अगर_अघोषित _LINUX_POSIX_CLOCK_H_
#घोषणा _LINUX_POSIX_CLOCK_H_

#समावेश <linux/cdev.h>
#समावेश <linux/fs.h>
#समावेश <linux/poll.h>
#समावेश <linux/posix-समयrs.h>
#समावेश <linux/rwsem.h>

काष्ठा posix_घड़ी;

/**
 * काष्ठा posix_घड़ी_operations - functional पूर्णांकerface to the घड़ी
 *
 * Every posix घड़ी is represented by a अक्षरacter device. Drivers may
 * optionally offer extended capabilities by implementing the
 * अक्षरacter device methods. The अक्षरacter device file operations are
 * first handled by the घड़ी device layer, then passed on to the
 * driver by calling these functions.
 *
 * @owner:          The घड़ी driver should set to THIS_MODULE
 * @घड़ी_adjसमय:  Adjust the घड़ी
 * @घड़ी_समय_लो:  Read the current समय
 * @घड़ी_getres:   Get the घड़ी resolution
 * @घड़ी_समय_रखो:  Set the current समय value
 * @खोलो:           Optional अक्षरacter device खोलो method
 * @release:        Optional अक्षरacter device release method
 * @ioctl:          Optional अक्षरacter device ioctl method
 * @पढ़ो:           Optional अक्षरacter device पढ़ो method
 * @poll:           Optional अक्षरacter device poll method
 */
काष्ठा posix_घड़ी_operations अणु
	काष्ठा module *owner;

	पूर्णांक  (*घड़ी_adjसमय)(काष्ठा posix_घड़ी *pc, काष्ठा __kernel_समयx *tx);

	पूर्णांक  (*घड़ी_समय_लो)(काष्ठा posix_घड़ी *pc, काष्ठा बारpec64 *ts);

	पूर्णांक  (*घड़ी_getres) (काष्ठा posix_घड़ी *pc, काष्ठा बारpec64 *ts);

	पूर्णांक  (*घड़ी_समय_रखो)(काष्ठा posix_घड़ी *pc,
			      स्थिर काष्ठा बारpec64 *ts);

	/*
	 * Optional अक्षरacter device methods:
	 */
	दीर्घ    (*ioctl)   (काष्ठा posix_घड़ी *pc,
			    अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

	पूर्णांक     (*खोलो)    (काष्ठा posix_घड़ी *pc, भ_शेषe_t f_mode);

	__poll_t (*poll)   (काष्ठा posix_घड़ी *pc,
			    काष्ठा file *file, poll_table *रुको);

	पूर्णांक     (*release) (काष्ठा posix_घड़ी *pc);

	sमाप_प्रकार (*पढ़ो)    (काष्ठा posix_घड़ी *pc,
			    uपूर्णांक flags, अक्षर __user *buf, माप_प्रकार cnt);
पूर्ण;

/**
 * काष्ठा posix_घड़ी - represents a dynamic posix घड़ी
 *
 * @ops:     Functional पूर्णांकerface to the घड़ी
 * @cdev:    Character device instance क्रम this घड़ी
 * @dev:     Poपूर्णांकer to the घड़ी's device.
 * @rwsem:   Protects the 'zombie' field from concurrent access.
 * @zombie:  If 'zombie' is true, then the hardware has disappeared.
 *
 * Drivers should embed their काष्ठा posix_घड़ी within a निजी
 * काष्ठाure, obtaining a reference to it during callbacks using
 * container_of().
 *
 * Drivers should supply an initialized but not exposed काष्ठा device
 * to posix_घड़ी_रेजिस्टर(). It is used to manage lअगरeसमय of the
 * driver's private structure. It's 'release' field should be set to
 * a release function क्रम this निजी काष्ठाure.
 */
काष्ठा posix_घड़ी अणु
	काष्ठा posix_घड़ी_operations ops;
	काष्ठा cdev cdev;
	काष्ठा device *dev;
	काष्ठा rw_semaphore rwsem;
	bool zombie;
पूर्ण;

/**
 * posix_घड़ी_रेजिस्टर() - रेजिस्टर a new घड़ी
 * @clk:   Poपूर्णांकer to the घड़ी. Caller must provide 'ops' field
 * @dev:   Poपूर्णांकer to the initialized device. Caller must provide
 *         'release' field
 *
 * A घड़ी driver calls this function to रेजिस्टर itself with the
 * घड़ी device subप्रणाली. If 'clk' poपूर्णांकs to dynamically allocated
 * memory, then the caller must provide a 'release' function to मुक्त
 * that memory.
 *
 * Returns zero on success, non-zero otherwise.
 */
पूर्णांक posix_घड़ी_रेजिस्टर(काष्ठा posix_घड़ी *clk, काष्ठा device *dev);

/**
 * posix_घड़ी_unरेजिस्टर() - unरेजिस्टर a घड़ी
 * @clk: Clock instance previously रेजिस्टरed via posix_घड़ी_रेजिस्टर()
 *
 * A घड़ी driver calls this function to हटाओ itself from the घड़ी
 * device subप्रणाली. The posix_घड़ी itself will reमुख्य (in an
 * inactive state) until its reference count drops to zero, at which
 * poपूर्णांक it will be deallocated with its 'release' method.
 */
व्योम posix_घड़ी_unरेजिस्टर(काष्ठा posix_घड़ी *clk);

#पूर्ण_अगर
