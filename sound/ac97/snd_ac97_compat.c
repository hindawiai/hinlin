<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Copyright (C) 2016 Robert Jarzmik <robert.jarzmik@मुक्त.fr>
 */

#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <sound/ac97/codec.h>
#समावेश <sound/ac97/compat.h>
#समावेश <sound/ac97/controller.h>
#समावेश <sound/soc.h>

#समावेश "ac97_core.h"

अटल व्योम compat_ac97_release(काष्ठा device *dev)
अणु
	kमुक्त(to_ac97_t(dev));
पूर्ण

अटल व्योम compat_ac97_reset(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा ac97_codec_device *adev = to_ac97_device(ac97->निजी_data);
	काष्ठा ac97_controller *actrl = adev->ac97_ctrl;

	अगर (actrl->ops->reset)
		actrl->ops->reset(actrl);
पूर्ण

अटल व्योम compat_ac97_warm_reset(काष्ठा snd_ac97 *ac97)
अणु
	काष्ठा ac97_codec_device *adev = to_ac97_device(ac97->निजी_data);
	काष्ठा ac97_controller *actrl = adev->ac97_ctrl;

	अगर (actrl->ops->warm_reset)
		actrl->ops->warm_reset(actrl);
पूर्ण

अटल व्योम compat_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg,
			      अचिन्हित लघु val)
अणु
	काष्ठा ac97_codec_device *adev = to_ac97_device(ac97->निजी_data);
	काष्ठा ac97_controller *actrl = adev->ac97_ctrl;

	actrl->ops->ग_लिखो(actrl, ac97->num, reg, val);
पूर्ण

अटल अचिन्हित लघु compat_ac97_पढ़ो(काष्ठा snd_ac97 *ac97,
				       अचिन्हित लघु reg)
अणु
	काष्ठा ac97_codec_device *adev = to_ac97_device(ac97->निजी_data);
	काष्ठा ac97_controller *actrl = adev->ac97_ctrl;

	वापस actrl->ops->पढ़ो(actrl, ac97->num, reg);
पूर्ण

अटल स्थिर काष्ठा snd_ac97_bus_ops compat_snd_ac97_bus_ops = अणु
	.reset = compat_ac97_reset,
	.warm_reset = compat_ac97_warm_reset,
	.ग_लिखो = compat_ac97_ग_लिखो,
	.पढ़ो = compat_ac97_पढ़ो,
पूर्ण;

अटल काष्ठा snd_ac97_bus compat_soc_ac97_bus = अणु
	.ops = &compat_snd_ac97_bus_ops,
पूर्ण;

काष्ठा snd_ac97 *snd_ac97_compat_alloc(काष्ठा ac97_codec_device *adev)
अणु
	काष्ठा snd_ac97 *ac97;
	पूर्णांक ret;

	ac97 = kzalloc(माप(काष्ठा snd_ac97), GFP_KERNEL);
	अगर (ac97 == शून्य)
		वापस ERR_PTR(-ENOMEM);

	ac97->निजी_data = adev;
	ac97->bus = &compat_soc_ac97_bus;

	ac97->dev.parent = &adev->dev;
	ac97->dev.release = compat_ac97_release;
	dev_set_name(&ac97->dev, "%s-compat", dev_name(&adev->dev));
	ret = device_रेजिस्टर(&ac97->dev);
	अगर (ret) अणु
		put_device(&ac97->dev);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस ac97;
पूर्ण
EXPORT_SYMBOL_GPL(snd_ac97_compat_alloc);

व्योम snd_ac97_compat_release(काष्ठा snd_ac97 *ac97)
अणु
	device_unरेजिस्टर(&ac97->dev);
पूर्ण
EXPORT_SYMBOL_GPL(snd_ac97_compat_release);

पूर्णांक snd_ac97_reset(काष्ठा snd_ac97 *ac97, bool try_warm, अचिन्हित पूर्णांक id,
	अचिन्हित पूर्णांक id_mask)
अणु
	काष्ठा ac97_codec_device *adev = to_ac97_device(ac97->निजी_data);
	काष्ठा ac97_controller *actrl = adev->ac97_ctrl;
	अचिन्हित पूर्णांक scanned;

	अगर (try_warm) अणु
		compat_ac97_warm_reset(ac97);
		scanned = snd_ac97_bus_scan_one(actrl, adev->num);
		अगर (ac97_ids_match(scanned, adev->venकरोr_id, id_mask))
			वापस 1;
	पूर्ण

	compat_ac97_reset(ac97);
	compat_ac97_warm_reset(ac97);
	scanned = snd_ac97_bus_scan_one(actrl, adev->num);
	अगर (ac97_ids_match(scanned, adev->venकरोr_id, id_mask))
		वापस 0;

	वापस -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(snd_ac97_reset);
