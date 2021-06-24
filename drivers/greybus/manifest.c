<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Greybus manअगरest parsing
 *
 * Copyright 2014-2015 Google Inc.
 * Copyright 2014-2015 Linaro Ltd.
 */

#समावेश <linux/greybus.h>

अटल स्थिर अक्षर *get_descriptor_type_string(u8 type)
अणु
	चयन (type) अणु
	हाल GREYBUS_TYPE_INVALID:
		वापस "invalid";
	हाल GREYBUS_TYPE_STRING:
		वापस "string";
	हाल GREYBUS_TYPE_INTERFACE:
		वापस "interface";
	हाल GREYBUS_TYPE_CPORT:
		वापस "cport";
	हाल GREYBUS_TYPE_BUNDLE:
		वापस "bundle";
	शेष:
		WARN_ON(1);
		वापस "unknown";
	पूर्ण
पूर्ण

/*
 * We scan the manअगरest once to identअगरy where all the descriptors
 * are.  The result is a list of these manअगरest_desc काष्ठाures.  We
 * then pick through them क्रम what we're looking क्रम (starting with
 * the पूर्णांकerface descriptor).  As each is processed we हटाओ it from
 * the list.  When we're करोne the list should (probably) be empty.
 */
काष्ठा manअगरest_desc अणु
	काष्ठा list_head		links;

	माप_प्रकार				size;
	व्योम				*data;
	क्रमागत greybus_descriptor_type	type;
पूर्ण;

अटल व्योम release_manअगरest_descriptor(काष्ठा manअगरest_desc *descriptor)
अणु
	list_del(&descriptor->links);
	kमुक्त(descriptor);
पूर्ण

अटल व्योम release_manअगरest_descriptors(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा manअगरest_desc *descriptor;
	काष्ठा manअगरest_desc *next;

	list_क्रम_each_entry_safe(descriptor, next, &पूर्णांकf->manअगरest_descs, links)
		release_manअगरest_descriptor(descriptor);
पूर्ण

अटल व्योम release_cport_descriptors(काष्ठा list_head *head, u8 bundle_id)
अणु
	काष्ठा manअगरest_desc *desc, *पंचांगp;
	काष्ठा greybus_descriptor_cport *desc_cport;

	list_क्रम_each_entry_safe(desc, पंचांगp, head, links) अणु
		desc_cport = desc->data;

		अगर (desc->type != GREYBUS_TYPE_CPORT)
			जारी;

		अगर (desc_cport->bundle == bundle_id)
			release_manअगरest_descriptor(desc);
	पूर्ण
पूर्ण

अटल काष्ठा manअगरest_desc *get_next_bundle_desc(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा manअगरest_desc *descriptor;
	काष्ठा manअगरest_desc *next;

	list_क्रम_each_entry_safe(descriptor, next, &पूर्णांकf->manअगरest_descs, links)
		अगर (descriptor->type == GREYBUS_TYPE_BUNDLE)
			वापस descriptor;

	वापस शून्य;
पूर्ण

/*
 * Validate the given descriptor.  Its reported size must fit within
 * the number of bytes reमुख्यing, and it must have a recognized
 * type.  Check that the reported size is at least as big as what
 * we expect to see.  (It could be bigger, perhaps क्रम a new version
 * of the क्रमmat.)
 *
 * Returns the (non-zero) number of bytes consumed by the descriptor,
 * or a negative त्रुटि_सं.
 */
अटल पूर्णांक identअगरy_descriptor(काष्ठा gb_पूर्णांकerface *पूर्णांकf,
			       काष्ठा greybus_descriptor *desc, माप_प्रकार size)
अणु
	काष्ठा greybus_descriptor_header *desc_header = &desc->header;
	काष्ठा manअगरest_desc *descriptor;
	माप_प्रकार desc_size;
	माप_प्रकार expected_size;

	अगर (size < माप(*desc_header)) अणु
		dev_err(&पूर्णांकf->dev, "manifest too small (%zu < %zu)\n", size,
			माप(*desc_header));
		वापस -EINVAL;		/* Must at least have header */
	पूर्ण

	desc_size = le16_to_cpu(desc_header->size);
	अगर (desc_size > size) अणु
		dev_err(&पूर्णांकf->dev, "descriptor too big (%zu > %zu)\n",
			desc_size, size);
		वापस -EINVAL;
	पूर्ण

	/* Descriptor needs to at least have a header */
	expected_size = माप(*desc_header);

	चयन (desc_header->type) अणु
	हाल GREYBUS_TYPE_STRING:
		expected_size += माप(काष्ठा greybus_descriptor_string);
		expected_size += desc->string.length;

		/* String descriptors are padded to 4 byte boundaries */
		expected_size = ALIGN(expected_size, 4);
		अवरोध;
	हाल GREYBUS_TYPE_INTERFACE:
		expected_size += माप(काष्ठा greybus_descriptor_पूर्णांकerface);
		अवरोध;
	हाल GREYBUS_TYPE_BUNDLE:
		expected_size += माप(काष्ठा greybus_descriptor_bundle);
		अवरोध;
	हाल GREYBUS_TYPE_CPORT:
		expected_size += माप(काष्ठा greybus_descriptor_cport);
		अवरोध;
	हाल GREYBUS_TYPE_INVALID:
	शेष:
		dev_err(&पूर्णांकf->dev, "invalid descriptor type (%u)\n",
			desc_header->type);
		वापस -EINVAL;
	पूर्ण

	अगर (desc_size < expected_size) अणु
		dev_err(&पूर्णांकf->dev, "%s descriptor too small (%zu < %zu)\n",
			get_descriptor_type_string(desc_header->type),
			desc_size, expected_size);
		वापस -EINVAL;
	पूर्ण

	/* Descriptor bigger than what we expect */
	अगर (desc_size > expected_size) अणु
		dev_warn(&पूर्णांकf->dev, "%s descriptor size mismatch (want %zu got %zu)\n",
			 get_descriptor_type_string(desc_header->type),
			 expected_size, desc_size);
	पूर्ण

	descriptor = kzalloc(माप(*descriptor), GFP_KERNEL);
	अगर (!descriptor)
		वापस -ENOMEM;

	descriptor->size = desc_size;
	descriptor->data = (अक्षर *)desc + माप(*desc_header);
	descriptor->type = desc_header->type;
	list_add_tail(&descriptor->links, &पूर्णांकf->manअगरest_descs);

	/* desc_size is positive and is known to fit in a चिन्हित पूर्णांक */

	वापस desc_size;
पूर्ण

/*
 * Find the string descriptor having the given id, validate it, and
 * allocate a duplicate copy of it.  The duplicate has an extra byte
 * which guarantees the वापसed string is NUL-terminated.
 *
 * String index 0 is valid (it represents "no string"), and क्रम
 * that a null poपूर्णांकer is वापसed.
 *
 * Otherwise वापसs a poपूर्णांकer to a newly-allocated copy of the
 * descriptor string, or an error-coded poपूर्णांकer on failure.
 */
अटल अक्षर *gb_string_get(काष्ठा gb_पूर्णांकerface *पूर्णांकf, u8 string_id)
अणु
	काष्ठा greybus_descriptor_string *desc_string;
	काष्ठा manअगरest_desc *descriptor;
	bool found = false;
	अक्षर *string;

	/* A zero string id means no string (but no error) */
	अगर (!string_id)
		वापस शून्य;

	list_क्रम_each_entry(descriptor, &पूर्णांकf->manअगरest_descs, links) अणु
		अगर (descriptor->type != GREYBUS_TYPE_STRING)
			जारी;

		desc_string = descriptor->data;
		अगर (desc_string->id == string_id) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found)
		वापस ERR_PTR(-ENOENT);

	/* Allocate an extra byte so we can guarantee it's NUL-terminated */
	string = kmemdup(&desc_string->string, desc_string->length + 1,
			 GFP_KERNEL);
	अगर (!string)
		वापस ERR_PTR(-ENOMEM);
	string[desc_string->length] = '\0';

	/* Ok we've used this string, so we're करोne with it */
	release_manअगरest_descriptor(descriptor);

	वापस string;
पूर्ण

/*
 * Find cport descriptors in the manअगरest associated with the given
 * bundle, and set up data काष्ठाures क्रम the functions that use
 * them.  Returns the number of cports set up क्रम the bundle, or 0
 * अगर there is an error.
 */
अटल u32 gb_manअगरest_parse_cports(काष्ठा gb_bundle *bundle)
अणु
	काष्ठा gb_पूर्णांकerface *पूर्णांकf = bundle->पूर्णांकf;
	काष्ठा greybus_descriptor_cport *desc_cport;
	काष्ठा manअगरest_desc *desc, *next, *पंचांगp;
	LIST_HEAD(list);
	u8 bundle_id = bundle->id;
	u16 cport_id;
	u32 count = 0;
	पूर्णांक i;

	/* Set up all cport descriptors associated with this bundle */
	list_क्रम_each_entry_safe(desc, next, &पूर्णांकf->manअगरest_descs, links) अणु
		अगर (desc->type != GREYBUS_TYPE_CPORT)
			जारी;

		desc_cport = desc->data;
		अगर (desc_cport->bundle != bundle_id)
			जारी;

		cport_id = le16_to_cpu(desc_cport->id);
		अगर (cport_id > CPORT_ID_MAX)
			जाओ निकास;

		/* Nothing अन्यथा should have its cport_id as control cport id */
		अगर (cport_id == GB_CONTROL_CPORT_ID) अणु
			dev_err(&bundle->dev, "invalid cport id found (%02u)\n",
				cport_id);
			जाओ निकास;
		पूर्ण

		/*
		 * Found one, move it to our temporary list after checking क्रम
		 * duplicates.
		 */
		list_क्रम_each_entry(पंचांगp, &list, links) अणु
			desc_cport = पंचांगp->data;
			अगर (cport_id == le16_to_cpu(desc_cport->id)) अणु
				dev_err(&bundle->dev,
					"duplicate CPort %u found\n", cport_id);
				जाओ निकास;
			पूर्ण
		पूर्ण
		list_move_tail(&desc->links, &list);
		count++;
	पूर्ण

	अगर (!count)
		वापस 0;

	bundle->cport_desc = kसुस्मृति(count, माप(*bundle->cport_desc),
				     GFP_KERNEL);
	अगर (!bundle->cport_desc)
		जाओ निकास;

	bundle->num_cports = count;

	i = 0;
	list_क्रम_each_entry_safe(desc, next, &list, links) अणु
		desc_cport = desc->data;
		स_नकल(&bundle->cport_desc[i++], desc_cport,
		       माप(*desc_cport));

		/* Release the cport descriptor */
		release_manअगरest_descriptor(desc);
	पूर्ण

	वापस count;
निकास:
	release_cport_descriptors(&list, bundle_id);
	/*
	 * Free all cports क्रम this bundle to aव्योम 'excess descriptors'
	 * warnings.
	 */
	release_cport_descriptors(&पूर्णांकf->manअगरest_descs, bundle_id);

	वापस 0;	/* Error; count should also be 0 */
पूर्ण

/*
 * Find bundle descriptors in the manअगरest and set up their data
 * काष्ठाures.  Returns the number of bundles set up क्रम the
 * given पूर्णांकerface.
 */
अटल u32 gb_manअगरest_parse_bundles(काष्ठा gb_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा manअगरest_desc *desc;
	काष्ठा gb_bundle *bundle;
	काष्ठा gb_bundle *bundle_next;
	u32 count = 0;
	u8 bundle_id;
	u8 class;

	जबतक ((desc = get_next_bundle_desc(पूर्णांकf))) अणु
		काष्ठा greybus_descriptor_bundle *desc_bundle;

		/* Found one.  Set up its bundle काष्ठाure*/
		desc_bundle = desc->data;
		bundle_id = desc_bundle->id;
		class = desc_bundle->class;

		/* Done with this bundle descriptor */
		release_manअगरest_descriptor(desc);

		/* Ignore any legacy control bundles */
		अगर (bundle_id == GB_CONTROL_BUNDLE_ID) अणु
			dev_dbg(&पूर्णांकf->dev, "%s - ignoring control bundle\n",
				__func__);
			release_cport_descriptors(&पूर्णांकf->manअगरest_descs,
						  bundle_id);
			जारी;
		पूर्ण

		/* Nothing अन्यथा should have its class set to control class */
		अगर (class == GREYBUS_CLASS_CONTROL) अणु
			dev_err(&पूर्णांकf->dev,
				"bundle %u cannot use control class\n",
				bundle_id);
			जाओ cleanup;
		पूर्ण

		bundle = gb_bundle_create(पूर्णांकf, bundle_id, class);
		अगर (!bundle)
			जाओ cleanup;

		/*
		 * Now go set up this bundle's functions and cports.
		 *
		 * A 'bundle' represents a device in greybus. It may require
		 * multiple cports क्रम its functioning. If we fail to setup any
		 * cport of a bundle, we better reject the complete bundle as
		 * the device may not be able to function properly then.
		 *
		 * But, failing to setup a cport of bundle X करोesn't mean that
		 * the device corresponding to bundle Y will not work properly.
		 * Bundles should be treated as separate independent devices.
		 *
		 * While parsing manअगरest क्रम an पूर्णांकerface, treat bundles as
		 * separate entities and करोn't reject entire पूर्णांकerface and its
		 * bundles on failing to initialize a cport. But make sure the
		 * bundle which needs the cport, माला_लो destroyed properly.
		 */
		अगर (!gb_manअगरest_parse_cports(bundle)) अणु
			gb_bundle_destroy(bundle);
			जारी;
		पूर्ण

		count++;
	पूर्ण

	वापस count;
cleanup:
	/* An error occurred; unकरो any changes we've made */
	list_क्रम_each_entry_safe(bundle, bundle_next, &पूर्णांकf->bundles, links) अणु
		gb_bundle_destroy(bundle);
		count--;
	पूर्ण
	वापस 0;	/* Error; count should also be 0 */
पूर्ण

अटल bool gb_manअगरest_parse_पूर्णांकerface(काष्ठा gb_पूर्णांकerface *पूर्णांकf,
					काष्ठा manअगरest_desc *पूर्णांकerface_desc)
अणु
	काष्ठा greybus_descriptor_पूर्णांकerface *desc_पूर्णांकf = पूर्णांकerface_desc->data;
	काष्ठा gb_control *control = पूर्णांकf->control;
	अक्षर *str;

	/* Handle the strings first--they can fail */
	str = gb_string_get(पूर्णांकf, desc_पूर्णांकf->venकरोr_stringid);
	अगर (IS_ERR(str))
		वापस false;
	control->venकरोr_string = str;

	str = gb_string_get(पूर्णांकf, desc_पूर्णांकf->product_stringid);
	अगर (IS_ERR(str))
		जाओ out_मुक्त_venकरोr_string;
	control->product_string = str;

	/* Assign feature flags communicated via manअगरest */
	पूर्णांकf->features = desc_पूर्णांकf->features;

	/* Release the पूर्णांकerface descriptor, now that we're करोne with it */
	release_manअगरest_descriptor(पूर्णांकerface_desc);

	/* An पूर्णांकerface must have at least one bundle descriptor */
	अगर (!gb_manअगरest_parse_bundles(पूर्णांकf)) अणु
		dev_err(&पूर्णांकf->dev, "manifest bundle descriptors not valid\n");
		जाओ out_err;
	पूर्ण

	वापस true;
out_err:
	kमुक्त(control->product_string);
	control->product_string = शून्य;
out_मुक्त_venकरोr_string:
	kमुक्त(control->venकरोr_string);
	control->venकरोr_string = शून्य;

	वापस false;
पूर्ण

/*
 * Parse a buffer containing an पूर्णांकerface manअगरest.
 *
 * If we find anything wrong with the content/क्रमmat of the buffer
 * we reject it.
 *
 * The first requirement is that the manअगरest's version is
 * one we can parse.
 *
 * We make an initial pass through the buffer and identअगरy all of
 * the descriptors it contains, keeping track क्रम each its type
 * and the location size of its data in the buffer.
 *
 * Next we scan the descriptors, looking क्रम an पूर्णांकerface descriptor;
 * there must be exactly one of those.  When found, we record the
 * inक्रमmation it contains, and then हटाओ that descriptor (and any
 * string descriptors it refers to) from further consideration.
 *
 * After that we look क्रम the पूर्णांकerface's bundles--there must be at
 * least one of those.
 *
 * Returns true अगर parsing was successful, false otherwise.
 */
bool gb_manअगरest_parse(काष्ठा gb_पूर्णांकerface *पूर्णांकf, व्योम *data, माप_प्रकार size)
अणु
	काष्ठा greybus_manअगरest *manअगरest;
	काष्ठा greybus_manअगरest_header *header;
	काष्ठा greybus_descriptor *desc;
	काष्ठा manअगरest_desc *descriptor;
	काष्ठा manअगरest_desc *पूर्णांकerface_desc = शून्य;
	u16 manअगरest_size;
	u32 found = 0;
	bool result;

	/* Manअगरest descriptor list should be empty here */
	अगर (WARN_ON(!list_empty(&पूर्णांकf->manअगरest_descs)))
		वापस false;

	/* we have to have at _least_ the manअगरest header */
	अगर (size < माप(*header)) अणु
		dev_err(&पूर्णांकf->dev, "short manifest (%zu < %zu)\n",
			size, माप(*header));
		वापस false;
	पूर्ण

	/* Make sure the size is right */
	manअगरest = data;
	header = &manअगरest->header;
	manअगरest_size = le16_to_cpu(header->size);
	अगर (manअगरest_size != size) अणु
		dev_err(&पूर्णांकf->dev, "manifest size mismatch (%zu != %u)\n",
			size, manअगरest_size);
		वापस false;
	पूर्ण

	/* Validate major/minor number */
	अगर (header->version_major > GREYBUS_VERSION_MAJOR) अणु
		dev_err(&पूर्णांकf->dev, "manifest version too new (%u.%u > %u.%u)\n",
			header->version_major, header->version_minor,
			GREYBUS_VERSION_MAJOR, GREYBUS_VERSION_MINOR);
		वापस false;
	पूर्ण

	/* OK, find all the descriptors */
	desc = manअगरest->descriptors;
	size -= माप(*header);
	जबतक (size) अणु
		पूर्णांक desc_size;

		desc_size = identअगरy_descriptor(पूर्णांकf, desc, size);
		अगर (desc_size < 0) अणु
			result = false;
			जाओ out;
		पूर्ण
		desc = (काष्ठा greybus_descriptor *)((अक्षर *)desc + desc_size);
		size -= desc_size;
	पूर्ण

	/* There must be a single पूर्णांकerface descriptor */
	list_क्रम_each_entry(descriptor, &पूर्णांकf->manअगरest_descs, links) अणु
		अगर (descriptor->type == GREYBUS_TYPE_INTERFACE)
			अगर (!found++)
				पूर्णांकerface_desc = descriptor;
	पूर्ण
	अगर (found != 1) अणु
		dev_err(&पूर्णांकf->dev, "manifest must have 1 interface descriptor (%u found)\n",
			found);
		result = false;
		जाओ out;
	पूर्ण

	/* Parse the manअगरest, starting with the पूर्णांकerface descriptor */
	result = gb_manअगरest_parse_पूर्णांकerface(पूर्णांकf, पूर्णांकerface_desc);

	/*
	 * We really should have no reमुख्यing descriptors, but we
	 * करोn't know what newer क्रमmat manअगरests might leave.
	 */
	अगर (result && !list_empty(&पूर्णांकf->manअगरest_descs))
		dev_info(&पूर्णांकf->dev, "excess descriptors in interface manifest\n");
out:
	release_manअगरest_descriptors(पूर्णांकf);

	वापस result;
पूर्ण
