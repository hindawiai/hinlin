<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*

  Broadcom B43legacy wireless driver

  SYSFS support routines

  Copyright (c) 2006 Michael Buesch <m@bues.ch>


*/

#समावेश "sysfs.h"
#समावेश "b43legacy.h"
#समावेश "main.h"
#समावेश "phy.h"
#समावेश "radio.h"

#समावेश <linux/capability.h>


#घोषणा GENERIC_खाताSIZE	64


अटल पूर्णांक get_पूर्णांकeger(स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अक्षर पंचांगp[10 + 1] = अणु 0 पूर्ण;
	पूर्णांक ret = -EINVAL, res;

	अगर (count == 0)
		जाओ out;
	count = min_t(माप_प्रकार, count, 10);
	स_नकल(पंचांगp, buf, count);
	ret = kstrtoपूर्णांक(पंचांगp, 10, &res);
	अगर (!ret)
		वापस res;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक get_boolean(स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	अगर (count != 0) अणु
		अगर (buf[0] == '1')
			वापस 1;
		अगर (buf[0] == '0')
			वापस 0;
		अगर (count >= 4 && स_भेद(buf, "true", 4) == 0)
			वापस 1;
		अगर (count >= 5 && स_भेद(buf, "false", 5) == 0)
			वापस 0;
		अगर (count >= 3 && स_भेद(buf, "yes", 3) == 0)
			वापस 1;
		अगर (count >= 2 && स_भेद(buf, "no", 2) == 0)
			वापस 0;
		अगर (count >= 2 && स_भेद(buf, "on", 2) == 0)
			वापस 1;
		अगर (count >= 3 && स_भेद(buf, "off", 3) == 0)
			वापस 0;
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल sमाप_प्रकार b43legacy_attr_पूर्णांकerभ_शेषe_show(काष्ठा device *dev,
					      काष्ठा device_attribute *attr,
					      अक्षर *buf)
अणु
	काष्ठा b43legacy_wldev *wldev = dev_to_b43legacy_wldev(dev);
	sमाप_प्रकार count = 0;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	mutex_lock(&wldev->wl->mutex);

	चयन (wldev->phy.पूर्णांकerभ_शेषe) अणु
	हाल B43legacy_INTERFMODE_NONE:
		count = snम_लिखो(buf, PAGE_SIZE, "0 (No Interference"
				 " Mitigation)\n");
		अवरोध;
	हाल B43legacy_INTERFMODE_NONWLAN:
		count = snम_लिखो(buf, PAGE_SIZE, "1 (Non-WLAN Interference"
				 " Mitigation)\n");
		अवरोध;
	हाल B43legacy_INTERFMODE_MANUALWLAN:
		count = snम_लिखो(buf, PAGE_SIZE, "2 (WLAN Interference"
				 " Mitigation)\n");
		अवरोध;
	शेष:
		B43legacy_WARN_ON(1);
	पूर्ण

	mutex_unlock(&wldev->wl->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार b43legacy_attr_पूर्णांकerभ_शेषe_store(काष्ठा device *dev,
					       काष्ठा device_attribute *attr,
					       स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा b43legacy_wldev *wldev = dev_to_b43legacy_wldev(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक err;
	पूर्णांक mode;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	mode = get_पूर्णांकeger(buf, count);
	चयन (mode) अणु
	हाल 0:
		mode = B43legacy_INTERFMODE_NONE;
		अवरोध;
	हाल 1:
		mode = B43legacy_INTERFMODE_NONWLAN;
		अवरोध;
	हाल 2:
		mode = B43legacy_INTERFMODE_MANUALWLAN;
		अवरोध;
	हाल 3:
		mode = B43legacy_INTERFMODE_AUTOWLAN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	mutex_lock(&wldev->wl->mutex);
	spin_lock_irqsave(&wldev->wl->irq_lock, flags);

	err = b43legacy_radio_set_पूर्णांकerference_mitigation(wldev, mode);
	अगर (err)
		b43legacyerr(wldev->wl, "Interference Mitigation not "
		       "supported by device\n");
	spin_unlock_irqrestore(&wldev->wl->irq_lock, flags);
	mutex_unlock(&wldev->wl->mutex);

	वापस err ? err : count;
पूर्ण

अटल DEVICE_ATTR(पूर्णांकerference, 0644,
		   b43legacy_attr_पूर्णांकerभ_शेषe_show,
		   b43legacy_attr_पूर्णांकerभ_शेषe_store);

अटल sमाप_प्रकार b43legacy_attr_preamble_show(काष्ठा device *dev,
					    काष्ठा device_attribute *attr,
					    अक्षर *buf)
अणु
	काष्ठा b43legacy_wldev *wldev = dev_to_b43legacy_wldev(dev);
	sमाप_प्रकार count;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	mutex_lock(&wldev->wl->mutex);

	अगर (wldev->लघु_preamble)
		count = snम_लिखो(buf, PAGE_SIZE, "1 (Short Preamble"
				 " enabled)\n");
	अन्यथा
		count = snम_लिखो(buf, PAGE_SIZE, "0 (Short Preamble"
				 " disabled)\n");

	mutex_unlock(&wldev->wl->mutex);

	वापस count;
पूर्ण

अटल sमाप_प्रकार b43legacy_attr_preamble_store(काष्ठा device *dev,
					     काष्ठा device_attribute *attr,
					     स्थिर अक्षर *buf, माप_प्रकार count)
अणु
	काष्ठा b43legacy_wldev *wldev = dev_to_b43legacy_wldev(dev);
	अचिन्हित दीर्घ flags;
	पूर्णांक value;

	अगर (!capable(CAP_NET_ADMIN))
		वापस -EPERM;

	value = get_boolean(buf, count);
	अगर (value < 0)
		वापस value;
	mutex_lock(&wldev->wl->mutex);
	spin_lock_irqsave(&wldev->wl->irq_lock, flags);

	wldev->लघु_preamble = !!value;

	spin_unlock_irqrestore(&wldev->wl->irq_lock, flags);
	mutex_unlock(&wldev->wl->mutex);

	वापस count;
पूर्ण

अटल DEVICE_ATTR(लघुpreamble, 0644,
		   b43legacy_attr_preamble_show,
		   b43legacy_attr_preamble_store);

पूर्णांक b43legacy_sysfs_रेजिस्टर(काष्ठा b43legacy_wldev *wldev)
अणु
	काष्ठा device *dev = wldev->dev->dev;
	पूर्णांक err;

	B43legacy_WARN_ON(b43legacy_status(wldev) !=
			  B43legacy_STAT_INITIALIZED);

	err = device_create_file(dev, &dev_attr_पूर्णांकerference);
	अगर (err)
		जाओ out;
	err = device_create_file(dev, &dev_attr_लघुpreamble);
	अगर (err)
		जाओ err_हटाओ_पूर्णांकerभ_शेषe;

out:
	वापस err;
err_हटाओ_पूर्णांकerभ_शेषe:
	device_हटाओ_file(dev, &dev_attr_पूर्णांकerference);
	जाओ out;
पूर्ण

व्योम b43legacy_sysfs_unरेजिस्टर(काष्ठा b43legacy_wldev *wldev)
अणु
	काष्ठा device *dev = wldev->dev->dev;

	device_हटाओ_file(dev, &dev_attr_लघुpreamble);
	device_हटाओ_file(dev, &dev_attr_पूर्णांकerference);
पूर्ण
