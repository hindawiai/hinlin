<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43 wireless driver

  SYSFS support routines

  Copyright (c) 2006 Michael Buesch <m@bues.ch>


*/

#समावेश <linux/capability.h>
#समावेश <linux/पन.स>

#समावेश "b43.h"
#समावेश "sysfs.h"
#समावेश "main.h"
#समावेश "phy_common.h"

#घोषणा GENERIC_खाताSIZE	64

अटल पूर्णांक get_पूर्णांकeger(स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अक्षर पंचांगp[10 + 1] = अणु 0 पूर्ण;
	पूर्णांक ret = -EINVAL;

	अगर (count == 0)
		जाओ out;
	count = min_t(माप_प्रकार, count, 10);
	स_नकल(पंचांगp, buf, count);
	ret = simple_म_से_दीर्घ(पंचांगp, शून्य, 10);
      out:
	वापस ret;
पूर्ण

अटल sमाप_प्रकार b43_attr_पूर्णांकerभ_शेषe_show(काष्ठा device *dev,
					काष्ठा device_attribute *attr,
					अक्षर *buf)
अणु
	काष्ठा b43_wldev *wldev = dev_to_b43_wldev(dev);
	sमाप_प्रकार count = 0;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	mutex_lock(&wldev->wl->mutex);

	अगर (wldev->phy.type != B43_PHYTYPE_G) अणु
		mutex_unlock(&wldev->wl->mutex);
		वापस -ENOSYS;
	पूर्ण

	चयन (wldev->phy.g->पूर्णांकerभ_शेषe) अणु
	हाल B43_INTERFMODE_NONE:
		count =
		    snम_लिखो(buf, PAGE_SIZE,
			     "0 (No Interference Mitigation)\n");
		अवरोध;
	हाल B43_INTERFMODE_NONWLAN:
		count =
		    snम_लिखो(buf, PAGE_SIZE,
			     "1 (Non-WLAN Interference Mitigation)\n");
		अवरोध;
	हाल B43_INTERFMODE_MANUALWLAN:
		count =
		    snम_लिखो(buf, PAGE_SIZE,
			     "2 (WLAN Interference Mitigation)\n");
		अवरोध;
	शेष:
		B43_WARN_ON(1);
	पूर्ण

	mutex_unlock(&wldev->wl->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार b43_attr_पूर्णांकerभ_शेषe_store(काष्ठा device *dev,
					 काष्ठा device_attribute *attr,
					 स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा b43_wldev *wldev = dev_to_b43_wldev(dev);
	पूर्णांक err;
	पूर्णांक mode;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	mode = get_पूर्णांकeger(buf, count);
	चयन (mode) अणु
	हाल 0:
		mode = B43_INTERFMODE_NONE;
		अवरोध;
	हाल 1:
		mode = B43_INTERFMODE_NONWLAN;
		अवरोध;
	हाल 2:
		mode = B43_INTERFMODE_MANUALWLAN;
		अवरोध;
	हाल 3:
		mode = B43_INTERFMODE_AUTOWLAN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&wldev->wl->mutex);

	अगर (wldev->phy.ops->पूर्णांकerf_mitigation) अणु
		err = wldev->phy.ops->पूर्णांकerf_mitigation(wldev, mode);
		अगर (err) अणु
			b43err(wldev->wl, "Interference Mitigation not "
			       "supported by device\n");
		पूर्ण
	पूर्ण अन्यथा
		err = -ENOSYS;

	mutex_unlock(&wldev->wl->mutex);

	वापस err ? err : count;
पूर्ण

अटल DEVICE_ATTR(पूर्णांकerference, 0644,
		   b43_attr_पूर्णांकerभ_शेषe_show, b43_attr_पूर्णांकerभ_शेषe_store);

पूर्णांक b43_sysfs_रेजिस्टर(काष्ठा b43_wldev *wldev)
अणु
	काष्ठा device *dev = wldev->dev->dev;

	B43_WARN_ON(b43_status(wldev) != B43_STAT_INITIALIZED);

	वापस device_create_file(dev, &dev_attr_पूर्णांकerference);
पूर्ण

व्योम b43_sysfs_unरेजिस्टर(काष्ठा b43_wldev *wldev)
अणु
	काष्ठा device *dev = wldev->dev->dev;

	device_हटाओ_file(dev, &dev_attr_पूर्णांकerference);
पूर्ण
