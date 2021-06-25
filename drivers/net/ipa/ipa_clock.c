<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/* Copyright (c) 2012-2018, The Linux Foundation. All rights reserved.
 * Copyright (C) 2018-2021 Linaro Ltd.
 */

#समावेश <linux/refcount.h>
#समावेश <linux/mutex.h>
#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerconnect.h>

#समावेश "ipa.h"
#समावेश "ipa_clock.h"
#समावेश "ipa_modem.h"
#समावेश "ipa_data.h"

/**
 * DOC: IPA Clocking
 *
 * The "IPA Clock" manages both the IPA core घड़ी and the पूर्णांकerconnects
 * (buses) the IPA depends on as a single logical entity.  A reference count
 * is incremented by "get" operations and decremented by "put" operations.
 * Transitions of that count from 0 to 1 result in the घड़ी and पूर्णांकerconnects
 * being enabled, and transitions of the count from 1 to 0 cause them to be
 * disabled.  We currently operate the core घड़ी at a fixed घड़ी rate, and
 * all buses at a fixed average and peak bandwidth.  As more advanced IPA
 * features are enabled, we can make better use of घड़ी and bus scaling.
 *
 * An IPA घड़ी reference must be held क्रम any access to IPA hardware.
 */

/**
 * काष्ठा ipa_पूर्णांकerconnect - IPA पूर्णांकerconnect inक्रमmation
 * @path:		Interconnect path
 * @average_bandwidth:	Average पूर्णांकerconnect bandwidth (KB/second)
 * @peak_bandwidth:	Peak पूर्णांकerconnect bandwidth (KB/second)
 */
काष्ठा ipa_पूर्णांकerconnect अणु
	काष्ठा icc_path *path;
	u32 average_bandwidth;
	u32 peak_bandwidth;
पूर्ण;

/**
 * काष्ठा ipa_घड़ी - IPA घड़ीing inक्रमmation
 * @count:		Clocking reference count
 * @mutex:		Protects घड़ी enable/disable
 * @core:		IPA core घड़ी
 * @पूर्णांकerconnect_count:	Number of elements in पूर्णांकerconnect[]
 * @पूर्णांकerconnect:	Interconnect array
 */
काष्ठा ipa_घड़ी अणु
	refcount_t count;
	काष्ठा mutex mutex; /* protects घड़ी enable/disable */
	काष्ठा clk *core;
	u32 पूर्णांकerconnect_count;
	काष्ठा ipa_पूर्णांकerconnect *पूर्णांकerconnect;
पूर्ण;

अटल पूर्णांक ipa_पूर्णांकerconnect_init_one(काष्ठा device *dev,
				     काष्ठा ipa_पूर्णांकerconnect *पूर्णांकerconnect,
				     स्थिर काष्ठा ipa_पूर्णांकerconnect_data *data)
अणु
	काष्ठा icc_path *path;

	path = of_icc_get(dev, data->name);
	अगर (IS_ERR(path)) अणु
		पूर्णांक ret = PTR_ERR(path);

		dev_err_probe(dev, ret, "error getting %s interconnect\n",
			      data->name);

		वापस ret;
	पूर्ण

	पूर्णांकerconnect->path = path;
	पूर्णांकerconnect->average_bandwidth = data->average_bandwidth;
	पूर्णांकerconnect->peak_bandwidth = data->peak_bandwidth;

	वापस 0;
पूर्ण

अटल व्योम ipa_पूर्णांकerconnect_निकास_one(काष्ठा ipa_पूर्णांकerconnect *पूर्णांकerconnect)
अणु
	icc_put(पूर्णांकerconnect->path);
	स_रखो(पूर्णांकerconnect, 0, माप(*पूर्णांकerconnect));
पूर्ण

/* Initialize पूर्णांकerconnects required क्रम IPA operation */
अटल पूर्णांक ipa_पूर्णांकerconnect_init(काष्ठा ipa_घड़ी *घड़ी, काष्ठा device *dev,
				 स्थिर काष्ठा ipa_पूर्णांकerconnect_data *data)
अणु
	काष्ठा ipa_पूर्णांकerconnect *पूर्णांकerconnect;
	u32 count;
	पूर्णांक ret;

	count = घड़ी->पूर्णांकerconnect_count;
	पूर्णांकerconnect = kसुस्मृति(count, माप(*पूर्णांकerconnect), GFP_KERNEL);
	अगर (!पूर्णांकerconnect)
		वापस -ENOMEM;
	घड़ी->पूर्णांकerconnect = पूर्णांकerconnect;

	जबतक (count--) अणु
		ret = ipa_पूर्णांकerconnect_init_one(dev, पूर्णांकerconnect, data++);
		अगर (ret)
			जाओ out_unwind;
		पूर्णांकerconnect++;
	पूर्ण

	वापस 0;

out_unwind:
	जबतक (पूर्णांकerconnect-- > घड़ी->पूर्णांकerconnect)
		ipa_पूर्णांकerconnect_निकास_one(पूर्णांकerconnect);
	kमुक्त(घड़ी->पूर्णांकerconnect);
	घड़ी->पूर्णांकerconnect = शून्य;

	वापस ret;
पूर्ण

/* Inverse of ipa_पूर्णांकerconnect_init() */
अटल व्योम ipa_पूर्णांकerconnect_निकास(काष्ठा ipa_घड़ी *घड़ी)
अणु
	काष्ठा ipa_पूर्णांकerconnect *पूर्णांकerconnect;

	पूर्णांकerconnect = घड़ी->पूर्णांकerconnect + घड़ी->पूर्णांकerconnect_count;
	जबतक (पूर्णांकerconnect-- > घड़ी->पूर्णांकerconnect)
		ipa_पूर्णांकerconnect_निकास_one(पूर्णांकerconnect);
	kमुक्त(घड़ी->पूर्णांकerconnect);
	घड़ी->पूर्णांकerconnect = शून्य;
पूर्ण

/* Currently we only use one bandwidth level, so just "enable" पूर्णांकerconnects */
अटल पूर्णांक ipa_पूर्णांकerconnect_enable(काष्ठा ipa *ipa)
अणु
	काष्ठा ipa_पूर्णांकerconnect *पूर्णांकerconnect;
	काष्ठा ipa_घड़ी *घड़ी = ipa->घड़ी;
	पूर्णांक ret;
	u32 i;

	पूर्णांकerconnect = घड़ी->पूर्णांकerconnect;
	क्रम (i = 0; i < घड़ी->पूर्णांकerconnect_count; i++) अणु
		ret = icc_set_bw(पूर्णांकerconnect->path,
				 पूर्णांकerconnect->average_bandwidth,
				 पूर्णांकerconnect->peak_bandwidth);
		अगर (ret)
			जाओ out_unwind;
		पूर्णांकerconnect++;
	पूर्ण

	वापस 0;

out_unwind:
	जबतक (पूर्णांकerconnect-- > घड़ी->पूर्णांकerconnect)
		(व्योम)icc_set_bw(पूर्णांकerconnect->path, 0, 0);

	वापस ret;
पूर्ण

/* To disable an पूर्णांकerconnect, we just its bandwidth to 0 */
अटल व्योम ipa_पूर्णांकerconnect_disable(काष्ठा ipa *ipa)
अणु
	काष्ठा ipa_पूर्णांकerconnect *पूर्णांकerconnect;
	काष्ठा ipa_घड़ी *घड़ी = ipa->घड़ी;
	पूर्णांक result = 0;
	u32 count;
	पूर्णांक ret;

	count = घड़ी->पूर्णांकerconnect_count;
	पूर्णांकerconnect = घड़ी->पूर्णांकerconnect + count;
	जबतक (count--) अणु
		पूर्णांकerconnect--;
		ret = icc_set_bw(पूर्णांकerconnect->path, 0, 0);
		अगर (ret && !result)
			result = ret;
	पूर्ण

	अगर (result)
		dev_err(&ipa->pdev->dev,
			"error %d disabling IPA interconnects\n", ret);
पूर्ण

/* Turn on IPA घड़ीs, including पूर्णांकerconnects */
अटल पूर्णांक ipa_घड़ी_enable(काष्ठा ipa *ipa)
अणु
	पूर्णांक ret;

	ret = ipa_पूर्णांकerconnect_enable(ipa);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(ipa->घड़ी->core);
	अगर (ret)
		ipa_पूर्णांकerconnect_disable(ipa);

	वापस ret;
पूर्ण

/* Inverse of ipa_घड़ी_enable() */
अटल व्योम ipa_घड़ी_disable(काष्ठा ipa *ipa)
अणु
	clk_disable_unprepare(ipa->घड़ी->core);
	ipa_पूर्णांकerconnect_disable(ipa);
पूर्ण

/* Get an IPA घड़ी reference, but only अगर the reference count is
 * alपढ़ोy non-zero.  Returns true अगर the additional reference was
 * added successfully, or false otherwise.
 */
bool ipa_घड़ी_get_additional(काष्ठा ipa *ipa)
अणु
	वापस refcount_inc_not_zero(&ipa->घड़ी->count);
पूर्ण

/* Get an IPA घड़ी reference.  If the reference count is non-zero, it is
 * incremented and वापस is immediate.  Otherwise it is checked again
 * under protection of the mutex, and अगर appropriate the IPA घड़ी
 * is enabled.
 *
 * Incrementing the reference count is पूर्णांकentionally deferred until
 * after the घड़ी is running and endpoपूर्णांकs are resumed.
 */
व्योम ipa_घड़ी_get(काष्ठा ipa *ipa)
अणु
	काष्ठा ipa_घड़ी *घड़ी = ipa->घड़ी;
	पूर्णांक ret;

	/* If the घड़ी is running, just bump the reference count */
	अगर (ipa_घड़ी_get_additional(ipa))
		वापस;

	/* Otherwise get the mutex and check again */
	mutex_lock(&घड़ी->mutex);

	/* A reference might have been added beक्रमe we got the mutex. */
	अगर (ipa_घड़ी_get_additional(ipa))
		जाओ out_mutex_unlock;

	ret = ipa_घड़ी_enable(ipa);
	अगर (ret) अणु
		dev_err(&ipa->pdev->dev, "error %d enabling IPA clock\n", ret);
		जाओ out_mutex_unlock;
	पूर्ण

	refcount_set(&घड़ी->count, 1);

out_mutex_unlock:
	mutex_unlock(&घड़ी->mutex);
पूर्ण

/* Attempt to हटाओ an IPA घड़ी reference.  If this represents the
 * last reference, disable the IPA घड़ी under protection of the mutex.
 */
व्योम ipa_घड़ी_put(काष्ठा ipa *ipa)
अणु
	काष्ठा ipa_घड़ी *घड़ी = ipa->घड़ी;

	/* If this is not the last reference there's nothing more to करो */
	अगर (!refcount_dec_and_mutex_lock(&घड़ी->count, &घड़ी->mutex))
		वापस;

	ipa_घड़ी_disable(ipa);

	mutex_unlock(&घड़ी->mutex);
पूर्ण

/* Return the current IPA core घड़ी rate */
u32 ipa_घड़ी_rate(काष्ठा ipa *ipa)
अणु
	वापस ipa->घड़ी ? (u32)clk_get_rate(ipa->घड़ी->core) : 0;
पूर्ण

/* Initialize IPA घड़ीing */
काष्ठा ipa_घड़ी *
ipa_घड़ी_init(काष्ठा device *dev, स्थिर काष्ठा ipa_घड़ी_data *data)
अणु
	काष्ठा ipa_घड़ी *घड़ी;
	काष्ठा clk *clk;
	पूर्णांक ret;

	clk = clk_get(dev, "core");
	अगर (IS_ERR(clk)) अणु
		dev_err_probe(dev, PTR_ERR(clk), "error getting core clock\n");

		वापस ERR_CAST(clk);
	पूर्ण

	ret = clk_set_rate(clk, data->core_घड़ी_rate);
	अगर (ret) अणु
		dev_err(dev, "error %d setting core clock rate to %u\n",
			ret, data->core_घड़ी_rate);
		जाओ err_clk_put;
	पूर्ण

	घड़ी = kzalloc(माप(*घड़ी), GFP_KERNEL);
	अगर (!घड़ी) अणु
		ret = -ENOMEM;
		जाओ err_clk_put;
	पूर्ण
	घड़ी->core = clk;
	घड़ी->पूर्णांकerconnect_count = data->पूर्णांकerconnect_count;

	ret = ipa_पूर्णांकerconnect_init(घड़ी, dev, data->पूर्णांकerconnect_data);
	अगर (ret)
		जाओ err_kमुक्त;

	mutex_init(&घड़ी->mutex);
	refcount_set(&घड़ी->count, 0);

	वापस घड़ी;

err_kमुक्त:
	kमुक्त(घड़ी);
err_clk_put:
	clk_put(clk);

	वापस ERR_PTR(ret);
पूर्ण

/* Inverse of ipa_घड़ी_init() */
व्योम ipa_घड़ी_निकास(काष्ठा ipa_घड़ी *घड़ी)
अणु
	काष्ठा clk *clk = घड़ी->core;

	WARN_ON(refcount_पढ़ो(&घड़ी->count) != 0);
	mutex_destroy(&घड़ी->mutex);
	ipa_पूर्णांकerconnect_निकास(घड़ी);
	kमुक्त(घड़ी);
	clk_put(clk);
पूर्ण
