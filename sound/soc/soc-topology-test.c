<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * soc-topology-test.c  --  ALSA SoC Topology Kernel Unit Tests
 *
 * Copyright(c) 2021 Intel Corporation. All rights reserved.
 */

#समावेश <linux/firmware.h>
#समावेश <sound/core.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-topology.h>
#समावेश <kunit/test.h>

/* ===== HELPER FUNCTIONS =================================================== */

/*
 * snd_soc_component needs device to operate on (primarily क्रम prपूर्णांकs), create
 * fake one, as we करोn't रेजिस्टर with PCI or anything अन्यथा
 * device_driver name is used in some of the prपूर्णांकs (fmt_single_name) so
 * we also mock up minimal one
 */
अटल काष्ठा device *test_dev;

अटल काष्ठा device_driver test_drv = अणु
	.name = "sound-soc-topology-test-driver",
पूर्ण;

अटल पूर्णांक snd_soc_tplg_test_init(काष्ठा kunit *test)
अणु
	test_dev = root_device_रेजिस्टर("sound-soc-topology-test");
	test_dev = get_device(test_dev);
	अगर (!test_dev)
		वापस -ENODEV;

	test_dev->driver = &test_drv;

	वापस 0;
पूर्ण

अटल व्योम snd_soc_tplg_test_निकास(काष्ठा kunit *test)
अणु
	put_device(test_dev);
	root_device_unरेजिस्टर(test_dev);
पूर्ण

/*
 * helper काष्ठा we use when रेजिस्टरing component, as we load topology during
 * component probe, we need to pass काष्ठा kunit somehow to probe function, so
 * we can report test result
 */
काष्ठा kunit_soc_component अणु
	काष्ठा kunit *kunit;
	पूर्णांक expect; /* what result we expect when loading topology */
	काष्ठा snd_soc_component comp;
	काष्ठा snd_soc_card card;
	काष्ठा firmware fw;
पूर्ण;

अटल पूर्णांक d_probe(काष्ठा snd_soc_component *component)
अणु
	काष्ठा kunit_soc_component *kunit_comp =
			container_of(component, काष्ठा kunit_soc_component, comp);
	पूर्णांक ret;

	ret = snd_soc_tplg_component_load(component, शून्य, &kunit_comp->fw);
	KUNIT_EXPECT_EQ_MSG(kunit_comp->kunit, kunit_comp->expect, ret,
			    "Failed topology load");

	वापस 0;
पूर्ण

अटल व्योम d_हटाओ(काष्ठा snd_soc_component *component)
अणु
	काष्ठा kunit_soc_component *kunit_comp =
			container_of(component, काष्ठा kunit_soc_component, comp);
	पूर्णांक ret;

	ret = snd_soc_tplg_component_हटाओ(component);
	KUNIT_EXPECT_EQ(kunit_comp->kunit, 0, ret);
पूर्ण

/*
 * ASoC minimal boiler plate
 */
SND_SOC_DAILINK_DEF(dummy, DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(platक्रमm, DAILINK_COMP_ARRAY(COMP_PLATFORM("sound-soc-topology-test")));

अटल काष्ठा snd_soc_dai_link kunit_dai_links[] = अणु
	अणु
		.name = "KUNIT Audio Port",
		.id = 0,
		.stream_name = "Audio Playback/Capture",
		.nonatomic = 1,
		.dynamic = 1,
		.trigger = अणुSND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(dummy, dummy, platक्रमm),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver test_component = अणु
	.name = "sound-soc-topology-test",
	.probe = d_probe,
	.हटाओ = d_हटाओ,
	.non_legacy_dai_naming = 1,
पूर्ण;

/* ===== TOPOLOGY TEMPLATES ================================================= */

// Structural representation of topology which can be generated with:
// $ touch empty
// $ alsatplg -c empty -o empty.tplg
// $ xxd -i empty.tplg

काष्ठा tplg_पंचांगpl_001 अणु
	काष्ठा snd_soc_tplg_hdr header;
	काष्ठा snd_soc_tplg_manअगरest manअगरest;
पूर्ण __packed;

अटल काष्ठा tplg_पंचांगpl_001 tplg_पंचांगpl_empty = अणु
	.header = अणु
		.magic = cpu_to_le32(SND_SOC_TPLG_MAGIC),
		.abi = cpu_to_le32(5),
		.version = 0,
		.type = cpu_to_le32(SND_SOC_TPLG_TYPE_MANIFEST),
		.size = cpu_to_le32(माप(काष्ठा snd_soc_tplg_hdr)),
		.venकरोr_type = 0,
		.payload_size = cpu_to_le32(माप(काष्ठा snd_soc_tplg_manअगरest)),
		.index = 0,
		.count = cpu_to_le32(1),
	पूर्ण,

	.manअगरest = अणु
		.size = cpu_to_le32(माप(काष्ठा snd_soc_tplg_manअगरest)),
		/* rest of fields is 0 */
	पूर्ण,
पूर्ण;

// Structural representation of topology containing SectionPCM

काष्ठा tplg_पंचांगpl_002 अणु
	काष्ठा snd_soc_tplg_hdr header;
	काष्ठा snd_soc_tplg_manअगरest manअगरest;
	काष्ठा snd_soc_tplg_hdr pcm_header;
	काष्ठा snd_soc_tplg_pcm pcm;
पूर्ण __packed;

अटल काष्ठा tplg_पंचांगpl_002 tplg_पंचांगpl_with_pcm = अणु
	.header = अणु
		.magic = cpu_to_le32(SND_SOC_TPLG_MAGIC),
		.abi = cpu_to_le32(5),
		.version = 0,
		.type = cpu_to_le32(SND_SOC_TPLG_TYPE_MANIFEST),
		.size = cpu_to_le32(माप(काष्ठा snd_soc_tplg_hdr)),
		.venकरोr_type = 0,
		.payload_size = cpu_to_le32(माप(काष्ठा snd_soc_tplg_manअगरest)),
		.index = 0,
		.count = cpu_to_le32(1),
	पूर्ण,
	.manअगरest = अणु
		.size = cpu_to_le32(माप(काष्ठा snd_soc_tplg_manअगरest)),
		.pcm_elems = cpu_to_le32(1),
		/* rest of fields is 0 */
	पूर्ण,
	.pcm_header = अणु
		.magic = cpu_to_le32(SND_SOC_TPLG_MAGIC),
		.abi = cpu_to_le32(5),
		.version = 0,
		.type = cpu_to_le32(SND_SOC_TPLG_TYPE_PCM),
		.size = cpu_to_le32(माप(काष्ठा snd_soc_tplg_hdr)),
		.venकरोr_type = 0,
		.payload_size = cpu_to_le32(माप(काष्ठा snd_soc_tplg_pcm)),
		.index = 0,
		.count = cpu_to_le32(1),
	पूर्ण,
	.pcm = अणु
		.size = cpu_to_le32(माप(काष्ठा snd_soc_tplg_pcm)),
		.pcm_name = "KUNIT Audio",
		.dai_name = "kunit-audio-dai",
		.pcm_id = 0,
		.dai_id = 0,
		.playback = cpu_to_le32(1),
		.capture = cpu_to_le32(1),
		.compress = 0,
		.stream = अणु
			[0] = अणु
				.channels = cpu_to_le32(2),
			पूर्ण,
			[1] = अणु
				.channels = cpu_to_le32(2),
			पूर्ण,
		पूर्ण,
		.num_streams = 0,
		.caps = अणु
			[0] = अणु
				.name = "kunit-audio-playback",
				.channels_min = cpu_to_le32(2),
				.channels_max = cpu_to_le32(2),
			पूर्ण,
			[1] = अणु
				.name = "kunit-audio-capture",
				.channels_min = cpu_to_le32(2),
				.channels_max = cpu_to_le32(2),
			पूर्ण,
		पूर्ण,
		.flag_mask = 0,
		.flags = 0,
		.priv = अणु 0 पूर्ण,
	पूर्ण,
पूर्ण;

/* ===== TEST CASES ========================================================= */

// TEST CASE
// Test passing शून्य component as parameter to snd_soc_tplg_component_load

/*
 * need to override generic probe function with one using शून्य when calling
 * topology load during component initialization, we करोn't need .हटाओ
 * handler as load should fail
 */
अटल पूर्णांक d_probe_null_comp(काष्ठा snd_soc_component *component)
अणु
	काष्ठा kunit_soc_component *kunit_comp =
			container_of(component, काष्ठा kunit_soc_component, comp);
	पूर्णांक ret;

	/* instead of passing component poपूर्णांकer as first argument, pass शून्य here */
	ret = snd_soc_tplg_component_load(शून्य, शून्य, &kunit_comp->fw);
	KUNIT_EXPECT_EQ_MSG(kunit_comp->kunit, kunit_comp->expect, ret,
			    "Failed topology load");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver test_component_null_comp = अणु
	.name = "sound-soc-topology-test",
	.probe = d_probe_null_comp,
	.non_legacy_dai_naming = 1,
पूर्ण;

अटल व्योम snd_soc_tplg_test_load_with_null_comp(काष्ठा kunit *test)
अणु
	काष्ठा kunit_soc_component *kunit_comp;
	पूर्णांक ret;

	/* prepare */
	kunit_comp = kunit_kzalloc(test, माप(*kunit_comp), GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = -EINVAL; /* expect failure */

	kunit_comp->card.dev = test_dev,
	kunit_comp->card.name = "kunit-card",
	kunit_comp->card.owner = THIS_MODULE,
	kunit_comp->card.dai_link = kunit_dai_links,
	kunit_comp->card.num_links = ARRAY_SIZE(kunit_dai_links),
	kunit_comp->card.fully_routed = true,

	/* run test */
	ret = snd_soc_रेजिस्टर_card(&kunit_comp->card);
	अगर (ret != 0 && ret != -EPROBE_DEFER)
		KUNIT_FAIL(test, "Failed to register card");

	ret = snd_soc_component_initialize(&kunit_comp->comp, &test_component_null_comp, test_dev);
	KUNIT_EXPECT_EQ(test, 0, ret);

	ret = snd_soc_add_component(&kunit_comp->comp, शून्य, 0);
	KUNIT_EXPECT_EQ(test, 0, ret);

	/* cleanup */
	ret = snd_soc_unरेजिस्टर_card(&kunit_comp->card);
	KUNIT_EXPECT_EQ(test, 0, ret);

	snd_soc_unरेजिस्टर_component(test_dev);
पूर्ण

// TEST CASE
// Test passing शून्य ops as parameter to snd_soc_tplg_component_load

/*
 * शून्य ops is शेष हाल, we pass empty topology (fw), so we करोn't have
 * anything to parse and just करो nothing, which results in वापस 0; from
 * calling soc_tplg_dapm_complete in soc_tplg_process_headers
 */
अटल व्योम snd_soc_tplg_test_load_with_null_ops(काष्ठा kunit *test)
अणु
	काष्ठा kunit_soc_component *kunit_comp;
	पूर्णांक ret;

	/* prepare */
	kunit_comp = kunit_kzalloc(test, माप(*kunit_comp), GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = 0; /* expect success */

	kunit_comp->card.dev = test_dev,
	kunit_comp->card.name = "kunit-card",
	kunit_comp->card.owner = THIS_MODULE,
	kunit_comp->card.dai_link = kunit_dai_links,
	kunit_comp->card.num_links = ARRAY_SIZE(kunit_dai_links),
	kunit_comp->card.fully_routed = true,

	/* run test */
	ret = snd_soc_रेजिस्टर_card(&kunit_comp->card);
	अगर (ret != 0 && ret != -EPROBE_DEFER)
		KUNIT_FAIL(test, "Failed to register card");

	ret = snd_soc_component_initialize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, ret);

	ret = snd_soc_add_component(&kunit_comp->comp, शून्य, 0);
	KUNIT_EXPECT_EQ(test, 0, ret);

	/* cleanup */
	ret = snd_soc_unरेजिस्टर_card(&kunit_comp->card);
	KUNIT_EXPECT_EQ(test, 0, ret);

	snd_soc_unरेजिस्टर_component(test_dev);
पूर्ण

// TEST CASE
// Test passing शून्य fw as parameter to snd_soc_tplg_component_load

/*
 * need to override generic probe function with one using शून्य poपूर्णांकer to fw
 * when calling topology load during component initialization, we करोn't need
 * .हटाओ handler as load should fail
 */
अटल पूर्णांक d_probe_null_fw(काष्ठा snd_soc_component *component)
अणु
	काष्ठा kunit_soc_component *kunit_comp =
			container_of(component, काष्ठा kunit_soc_component, comp);
	पूर्णांक ret;

	/* instead of passing fw poपूर्णांकer as third argument, pass शून्य here */
	ret = snd_soc_tplg_component_load(component, शून्य, शून्य);
	KUNIT_EXPECT_EQ_MSG(kunit_comp->kunit, kunit_comp->expect, ret,
			    "Failed topology load");

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver test_component_null_fw = अणु
	.name = "sound-soc-topology-test",
	.probe = d_probe_null_fw,
	.non_legacy_dai_naming = 1,
पूर्ण;

अटल व्योम snd_soc_tplg_test_load_with_null_fw(काष्ठा kunit *test)
अणु
	काष्ठा kunit_soc_component *kunit_comp;
	पूर्णांक ret;

	/* prepare */
	kunit_comp = kunit_kzalloc(test, माप(*kunit_comp), GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = -EINVAL; /* expect failure */

	kunit_comp->card.dev = test_dev,
	kunit_comp->card.name = "kunit-card",
	kunit_comp->card.owner = THIS_MODULE,
	kunit_comp->card.dai_link = kunit_dai_links,
	kunit_comp->card.num_links = ARRAY_SIZE(kunit_dai_links),
	kunit_comp->card.fully_routed = true,

	/* run test */
	ret = snd_soc_रेजिस्टर_card(&kunit_comp->card);
	अगर (ret != 0 && ret != -EPROBE_DEFER)
		KUNIT_FAIL(test, "Failed to register card");

	ret = snd_soc_component_initialize(&kunit_comp->comp, &test_component_null_fw, test_dev);
	KUNIT_EXPECT_EQ(test, 0, ret);

	ret = snd_soc_add_component(&kunit_comp->comp, शून्य, 0);
	KUNIT_EXPECT_EQ(test, 0, ret);

	/* cleanup */
	ret = snd_soc_unरेजिस्टर_card(&kunit_comp->card);
	KUNIT_EXPECT_EQ(test, 0, ret);

	snd_soc_unरेजिस्टर_component(test_dev);
पूर्ण

// TEST CASE
// Test passing "empty" topology file
अटल व्योम snd_soc_tplg_test_load_empty_tplg(काष्ठा kunit *test)
अणु
	काष्ठा kunit_soc_component *kunit_comp;
	काष्ठा tplg_पंचांगpl_001 *data;
	पूर्णांक size;
	पूर्णांक ret;

	/* prepare */
	kunit_comp = kunit_kzalloc(test, माप(*kunit_comp), GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = 0; /* expect success */

	size = माप(tplg_पंचांगpl_empty);
	data = kunit_kzalloc(kunit_comp->kunit, size, GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(kunit_comp->kunit, data);

	स_नकल(data, &tplg_पंचांगpl_empty, माप(tplg_पंचांगpl_empty));

	kunit_comp->fw.data = (u8 *)data;
	kunit_comp->fw.size = size;

	kunit_comp->card.dev = test_dev,
	kunit_comp->card.name = "kunit-card",
	kunit_comp->card.owner = THIS_MODULE,
	kunit_comp->card.dai_link = kunit_dai_links,
	kunit_comp->card.num_links = ARRAY_SIZE(kunit_dai_links),
	kunit_comp->card.fully_routed = true,

	/* run test */
	ret = snd_soc_रेजिस्टर_card(&kunit_comp->card);
	अगर (ret != 0 && ret != -EPROBE_DEFER)
		KUNIT_FAIL(test, "Failed to register card");

	ret = snd_soc_component_initialize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, ret);

	ret = snd_soc_add_component(&kunit_comp->comp, शून्य, 0);
	KUNIT_EXPECT_EQ(test, 0, ret);

	/* cleanup */
	ret = snd_soc_unरेजिस्टर_card(&kunit_comp->card);
	KUNIT_EXPECT_EQ(test, 0, ret);

	snd_soc_unरेजिस्टर_component(test_dev);
पूर्ण

// TEST CASE
// Test "empty" topology file, but with bad "magic"
// In theory we could loop through all possible bad values, but it takes too
// दीर्घ, so just use SND_SOC_TPLG_MAGIC + 1
अटल व्योम snd_soc_tplg_test_load_empty_tplg_bad_magic(काष्ठा kunit *test)
अणु
	काष्ठा kunit_soc_component *kunit_comp;
	काष्ठा tplg_पंचांगpl_001 *data;
	पूर्णांक size;
	पूर्णांक ret;

	/* prepare */
	kunit_comp = kunit_kzalloc(test, माप(*kunit_comp), GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = -EINVAL; /* expect failure */

	size = माप(tplg_पंचांगpl_empty);
	data = kunit_kzalloc(kunit_comp->kunit, size, GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(kunit_comp->kunit, data);

	स_नकल(data, &tplg_पंचांगpl_empty, माप(tplg_पंचांगpl_empty));
	/*
	 * override abi
	 * any value != magic number is wrong
	 */
	data->header.magic = cpu_to_le32(SND_SOC_TPLG_MAGIC + 1);

	kunit_comp->fw.data = (u8 *)data;
	kunit_comp->fw.size = size;

	kunit_comp->card.dev = test_dev,
	kunit_comp->card.name = "kunit-card",
	kunit_comp->card.owner = THIS_MODULE,
	kunit_comp->card.dai_link = kunit_dai_links,
	kunit_comp->card.num_links = ARRAY_SIZE(kunit_dai_links),
	kunit_comp->card.fully_routed = true,

	/* run test */
	ret = snd_soc_रेजिस्टर_card(&kunit_comp->card);
	अगर (ret != 0 && ret != -EPROBE_DEFER)
		KUNIT_FAIL(test, "Failed to register card");

	ret = snd_soc_component_initialize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, ret);

	ret = snd_soc_add_component(&kunit_comp->comp, शून्य, 0);
	KUNIT_EXPECT_EQ(test, 0, ret);

	/* cleanup */
	ret = snd_soc_unरेजिस्टर_card(&kunit_comp->card);
	KUNIT_EXPECT_EQ(test, 0, ret);

	snd_soc_unरेजिस्टर_component(test_dev);
पूर्ण

// TEST CASE
// Test "empty" topology file, but with bad "abi"
// In theory we could loop through all possible bad values, but it takes too
// दीर्घ, so just use SND_SOC_TPLG_ABI_VERSION + 1
अटल व्योम snd_soc_tplg_test_load_empty_tplg_bad_abi(काष्ठा kunit *test)
अणु
	काष्ठा kunit_soc_component *kunit_comp;
	काष्ठा tplg_पंचांगpl_001 *data;
	पूर्णांक size;
	पूर्णांक ret;

	/* prepare */
	kunit_comp = kunit_kzalloc(test, माप(*kunit_comp), GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = -EINVAL; /* expect failure */

	size = माप(tplg_पंचांगpl_empty);
	data = kunit_kzalloc(kunit_comp->kunit, size, GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(kunit_comp->kunit, data);

	स_नकल(data, &tplg_पंचांगpl_empty, माप(tplg_पंचांगpl_empty));
	/*
	 * override abi
	 * any value != accepted range is wrong
	 */
	data->header.abi = cpu_to_le32(SND_SOC_TPLG_ABI_VERSION + 1);

	kunit_comp->fw.data = (u8 *)data;
	kunit_comp->fw.size = size;

	kunit_comp->card.dev = test_dev,
	kunit_comp->card.name = "kunit-card",
	kunit_comp->card.owner = THIS_MODULE,
	kunit_comp->card.dai_link = kunit_dai_links,
	kunit_comp->card.num_links = ARRAY_SIZE(kunit_dai_links),
	kunit_comp->card.fully_routed = true,

	/* run test */
	ret = snd_soc_रेजिस्टर_card(&kunit_comp->card);
	अगर (ret != 0 && ret != -EPROBE_DEFER)
		KUNIT_FAIL(test, "Failed to register card");

	ret = snd_soc_component_initialize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, ret);

	ret = snd_soc_add_component(&kunit_comp->comp, शून्य, 0);
	KUNIT_EXPECT_EQ(test, 0, ret);

	/* cleanup */
	ret = snd_soc_unरेजिस्टर_card(&kunit_comp->card);
	KUNIT_EXPECT_EQ(test, 0, ret);

	snd_soc_unरेजिस्टर_component(test_dev);
पूर्ण

// TEST CASE
// Test "empty" topology file, but with bad "size"
// In theory we could loop through all possible bad values, but it takes too
// दीर्घ, so just use माप(काष्ठा snd_soc_tplg_hdr) + 1
अटल व्योम snd_soc_tplg_test_load_empty_tplg_bad_size(काष्ठा kunit *test)
अणु
	काष्ठा kunit_soc_component *kunit_comp;
	काष्ठा tplg_पंचांगpl_001 *data;
	पूर्णांक size;
	पूर्णांक ret;

	/* prepare */
	kunit_comp = kunit_kzalloc(test, माप(*kunit_comp), GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = -EINVAL; /* expect failure */

	size = माप(tplg_पंचांगpl_empty);
	data = kunit_kzalloc(kunit_comp->kunit, size, GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(kunit_comp->kunit, data);

	स_नकल(data, &tplg_पंचांगpl_empty, माप(tplg_पंचांगpl_empty));
	/*
	 * override size
	 * any value != काष्ठा size is wrong
	 */
	data->header.size = cpu_to_le32(माप(काष्ठा snd_soc_tplg_hdr) + 1);

	kunit_comp->fw.data = (u8 *)data;
	kunit_comp->fw.size = size;

	kunit_comp->card.dev = test_dev,
	kunit_comp->card.name = "kunit-card",
	kunit_comp->card.owner = THIS_MODULE,
	kunit_comp->card.dai_link = kunit_dai_links,
	kunit_comp->card.num_links = ARRAY_SIZE(kunit_dai_links),
	kunit_comp->card.fully_routed = true,

	/* run test */
	ret = snd_soc_रेजिस्टर_card(&kunit_comp->card);
	अगर (ret != 0 && ret != -EPROBE_DEFER)
		KUNIT_FAIL(test, "Failed to register card");

	ret = snd_soc_component_initialize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, ret);

	ret = snd_soc_add_component(&kunit_comp->comp, शून्य, 0);
	KUNIT_EXPECT_EQ(test, 0, ret);

	/* cleanup */
	ret = snd_soc_unरेजिस्टर_card(&kunit_comp->card);
	KUNIT_EXPECT_EQ(test, 0, ret);

	snd_soc_unरेजिस्टर_component(test_dev);
पूर्ण

// TEST CASE
// Test "empty" topology file, but with bad "payload_size"
// In theory we could loop through all possible bad values, but it takes too
// दीर्घ, so just use the known wrong one
अटल व्योम snd_soc_tplg_test_load_empty_tplg_bad_payload_size(काष्ठा kunit *test)
अणु
	काष्ठा kunit_soc_component *kunit_comp;
	काष्ठा tplg_पंचांगpl_001 *data;
	पूर्णांक size;
	पूर्णांक ret;

	/* prepare */
	kunit_comp = kunit_kzalloc(test, माप(*kunit_comp), GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = -EINVAL; /* expect failure */

	size = माप(tplg_पंचांगpl_empty);
	data = kunit_kzalloc(kunit_comp->kunit, size, GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(kunit_comp->kunit, data);

	स_नकल(data, &tplg_पंचांगpl_empty, माप(tplg_पंचांगpl_empty));
	/*
	 * override payload size
	 * there is only explicit check क्रम 0, so check with it, other values
	 * are handled by just not पढ़ोing behind खातापूर्ण
	 */
	data->header.payload_size = 0;

	kunit_comp->fw.data = (u8 *)data;
	kunit_comp->fw.size = size;

	kunit_comp->card.dev = test_dev,
	kunit_comp->card.name = "kunit-card",
	kunit_comp->card.owner = THIS_MODULE,
	kunit_comp->card.dai_link = kunit_dai_links,
	kunit_comp->card.num_links = ARRAY_SIZE(kunit_dai_links),
	kunit_comp->card.fully_routed = true,

	/* run test */
	ret = snd_soc_रेजिस्टर_card(&kunit_comp->card);
	अगर (ret != 0 && ret != -EPROBE_DEFER)
		KUNIT_FAIL(test, "Failed to register card");

	ret = snd_soc_component_initialize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, ret);

	ret = snd_soc_add_component(&kunit_comp->comp, शून्य, 0);
	KUNIT_EXPECT_EQ(test, 0, ret);

	/* cleanup */
	snd_soc_unरेजिस्टर_component(test_dev);

	ret = snd_soc_unरेजिस्टर_card(&kunit_comp->card);
	KUNIT_EXPECT_EQ(test, 0, ret);
पूर्ण

// TEST CASE
// Test passing topology file with PCM definition
अटल व्योम snd_soc_tplg_test_load_pcm_tplg(काष्ठा kunit *test)
अणु
	काष्ठा kunit_soc_component *kunit_comp;
	u8 *data;
	पूर्णांक size;
	पूर्णांक ret;

	/* prepare */
	kunit_comp = kunit_kzalloc(test, माप(*kunit_comp), GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = 0; /* expect success */

	size = माप(tplg_पंचांगpl_with_pcm);
	data = kunit_kzalloc(kunit_comp->kunit, size, GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(kunit_comp->kunit, data);

	स_नकल(data, &tplg_पंचांगpl_with_pcm, माप(tplg_पंचांगpl_with_pcm));

	kunit_comp->fw.data = data;
	kunit_comp->fw.size = size;

	kunit_comp->card.dev = test_dev,
	kunit_comp->card.name = "kunit-card",
	kunit_comp->card.owner = THIS_MODULE,
	kunit_comp->card.dai_link = kunit_dai_links,
	kunit_comp->card.num_links = ARRAY_SIZE(kunit_dai_links),
	kunit_comp->card.fully_routed = true,

	/* run test */
	ret = snd_soc_रेजिस्टर_card(&kunit_comp->card);
	अगर (ret != 0 && ret != -EPROBE_DEFER)
		KUNIT_FAIL(test, "Failed to register card");

	ret = snd_soc_component_initialize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, ret);

	ret = snd_soc_add_component(&kunit_comp->comp, शून्य, 0);
	KUNIT_EXPECT_EQ(test, 0, ret);

	snd_soc_unरेजिस्टर_component(test_dev);

	/* cleanup */
	ret = snd_soc_unरेजिस्टर_card(&kunit_comp->card);
	KUNIT_EXPECT_EQ(test, 0, ret);
पूर्ण

// TEST CASE
// Test passing topology file with PCM definition
// with component reload
अटल व्योम snd_soc_tplg_test_load_pcm_tplg_reload_comp(काष्ठा kunit *test)
अणु
	काष्ठा kunit_soc_component *kunit_comp;
	u8 *data;
	पूर्णांक size;
	पूर्णांक ret;
	पूर्णांक i;

	/* prepare */
	kunit_comp = kunit_kzalloc(test, माप(*kunit_comp), GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = 0; /* expect success */

	size = माप(tplg_पंचांगpl_with_pcm);
	data = kunit_kzalloc(kunit_comp->kunit, size, GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(kunit_comp->kunit, data);

	स_नकल(data, &tplg_पंचांगpl_with_pcm, माप(tplg_पंचांगpl_with_pcm));

	kunit_comp->fw.data = data;
	kunit_comp->fw.size = size;

	kunit_comp->card.dev = test_dev,
	kunit_comp->card.name = "kunit-card",
	kunit_comp->card.owner = THIS_MODULE,
	kunit_comp->card.dai_link = kunit_dai_links,
	kunit_comp->card.num_links = ARRAY_SIZE(kunit_dai_links),
	kunit_comp->card.fully_routed = true,

	/* run test */
	ret = snd_soc_रेजिस्टर_card(&kunit_comp->card);
	अगर (ret != 0 && ret != -EPROBE_DEFER)
		KUNIT_FAIL(test, "Failed to register card");

	क्रम (i = 0; i < 100; i++) अणु
		ret = snd_soc_component_initialize(&kunit_comp->comp, &test_component, test_dev);
		KUNIT_EXPECT_EQ(test, 0, ret);

		ret = snd_soc_add_component(&kunit_comp->comp, शून्य, 0);
		KUNIT_EXPECT_EQ(test, 0, ret);

		snd_soc_unरेजिस्टर_component(test_dev);
	पूर्ण

	/* cleanup */
	ret = snd_soc_unरेजिस्टर_card(&kunit_comp->card);
	KUNIT_EXPECT_EQ(test, 0, ret);
पूर्ण

// TEST CASE
// Test passing topology file with PCM definition
// with card reload
अटल व्योम snd_soc_tplg_test_load_pcm_tplg_reload_card(काष्ठा kunit *test)
अणु
	काष्ठा kunit_soc_component *kunit_comp;
	u8 *data;
	पूर्णांक size;
	पूर्णांक ret;
	पूर्णांक i;

	/* prepare */
	kunit_comp = kunit_kzalloc(test, माप(*kunit_comp), GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(test, kunit_comp);
	kunit_comp->kunit = test;
	kunit_comp->expect = 0; /* expect success */

	size = माप(tplg_पंचांगpl_with_pcm);
	data = kunit_kzalloc(kunit_comp->kunit, size, GFP_KERNEL);
	KUNIT_EXPECT_NOT_ERR_OR_शून्य(kunit_comp->kunit, data);

	स_नकल(data, &tplg_पंचांगpl_with_pcm, माप(tplg_पंचांगpl_with_pcm));

	kunit_comp->fw.data = data;
	kunit_comp->fw.size = size;

	kunit_comp->card.dev = test_dev,
	kunit_comp->card.name = "kunit-card",
	kunit_comp->card.owner = THIS_MODULE,
	kunit_comp->card.dai_link = kunit_dai_links,
	kunit_comp->card.num_links = ARRAY_SIZE(kunit_dai_links),
	kunit_comp->card.fully_routed = true,

	/* run test */
	ret = snd_soc_component_initialize(&kunit_comp->comp, &test_component, test_dev);
	KUNIT_EXPECT_EQ(test, 0, ret);

	ret = snd_soc_add_component(&kunit_comp->comp, शून्य, 0);
	KUNIT_EXPECT_EQ(test, 0, ret);

	क्रम (i = 0; i < 100; i++) अणु
		ret = snd_soc_रेजिस्टर_card(&kunit_comp->card);
		अगर (ret != 0 && ret != -EPROBE_DEFER)
			KUNIT_FAIL(test, "Failed to register card");

		ret = snd_soc_unरेजिस्टर_card(&kunit_comp->card);
		KUNIT_EXPECT_EQ(test, 0, ret);
	पूर्ण

	/* cleanup */
	snd_soc_unरेजिस्टर_component(test_dev);
पूर्ण

/* ===== KUNIT MODULE DEFINITIONS =========================================== */

अटल काष्ठा kunit_हाल snd_soc_tplg_test_हालs[] = अणु
	KUNIT_CASE(snd_soc_tplg_test_load_with_null_comp),
	KUNIT_CASE(snd_soc_tplg_test_load_with_null_ops),
	KUNIT_CASE(snd_soc_tplg_test_load_with_null_fw),
	KUNIT_CASE(snd_soc_tplg_test_load_empty_tplg),
	KUNIT_CASE(snd_soc_tplg_test_load_empty_tplg_bad_magic),
	KUNIT_CASE(snd_soc_tplg_test_load_empty_tplg_bad_abi),
	KUNIT_CASE(snd_soc_tplg_test_load_empty_tplg_bad_size),
	KUNIT_CASE(snd_soc_tplg_test_load_empty_tplg_bad_payload_size),
	KUNIT_CASE(snd_soc_tplg_test_load_pcm_tplg),
	KUNIT_CASE(snd_soc_tplg_test_load_pcm_tplg_reload_comp),
	KUNIT_CASE(snd_soc_tplg_test_load_pcm_tplg_reload_card),
	अणुपूर्ण
पूर्ण;

अटल काष्ठा kunit_suite snd_soc_tplg_test_suite = अणु
	.name = "snd_soc_tplg_test",
	.init = snd_soc_tplg_test_init,
	.निकास = snd_soc_tplg_test_निकास,
	.test_हालs = snd_soc_tplg_test_हालs,
पूर्ण;

kunit_test_suites(&snd_soc_tplg_test_suite);

MODULE_LICENSE("GPL");
