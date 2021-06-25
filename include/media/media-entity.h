<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Media entity
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#अगर_अघोषित _MEDIA_ENTITY_H
#घोषणा _MEDIA_ENTITY_H

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/bug.h>
#समावेश <linux/fwnode.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/media.h>

/* Enums used पूर्णांकernally at the media controller to represent graphs */

/**
 * क्रमागत media_gobj_type - type of a graph object
 *
 * @MEDIA_GRAPH_ENTITY:		Identअगरy a media entity
 * @MEDIA_GRAPH_PAD:		Identअगरy a media pad
 * @MEDIA_GRAPH_LINK:		Identअगरy a media link
 * @MEDIA_GRAPH_INTF_DEVNODE:	Identअगरy a media Kernel API पूर्णांकerface via
 *				a device node
 */
क्रमागत media_gobj_type अणु
	MEDIA_GRAPH_ENTITY,
	MEDIA_GRAPH_PAD,
	MEDIA_GRAPH_LINK,
	MEDIA_GRAPH_INTF_DEVNODE,
पूर्ण;

#घोषणा MEDIA_BITS_PER_TYPE		8
#घोषणा MEDIA_BITS_PER_ID		(32 - MEDIA_BITS_PER_TYPE)
#घोषणा MEDIA_ID_MASK			 GENMASK_ULL(MEDIA_BITS_PER_ID - 1, 0)

/* Structs to represent the objects that beदीर्घ to a media graph */

/**
 * काष्ठा media_gobj - Define a graph object.
 *
 * @mdev:	Poपूर्णांकer to the काष्ठा &media_device that owns the object
 * @id:		Non-zero object ID identअगरier. The ID should be unique
 *		inside a media_device, as it is composed by
 *		%MEDIA_BITS_PER_TYPE to store the type plus
 *		%MEDIA_BITS_PER_ID to store the ID
 * @list:	List entry stored in one of the per-type mdev object lists
 *
 * All objects on the media graph should have this काष्ठा embedded
 */
काष्ठा media_gobj अणु
	काष्ठा media_device	*mdev;
	u32			id;
	काष्ठा list_head	list;
पूर्ण;

#घोषणा MEDIA_ENTITY_ENUM_MAX_DEPTH	16

/**
 * काष्ठा media_entity_क्रमागत - An क्रमागतeration of media entities.
 *
 * @bmap:	Bit map in which each bit represents one entity at काष्ठा
 *		media_entity->पूर्णांकernal_idx.
 * @idx_max:	Number of bits in bmap
 */
काष्ठा media_entity_क्रमागत अणु
	अचिन्हित दीर्घ *bmap;
	पूर्णांक idx_max;
पूर्ण;

/**
 * काष्ठा media_graph - Media graph traversal state
 *
 * @stack:		Graph traversal stack; the stack contains inक्रमmation
 *			on the path the media entities to be walked and the
 *			links through which they were reached.
 * @stack.entity:	poपूर्णांकer to &काष्ठा media_entity at the graph.
 * @stack.link:		poपूर्णांकer to &काष्ठा list_head.
 * @ent_क्रमागत:		Visited entities
 * @top:		The top of the stack
 */
काष्ठा media_graph अणु
	काष्ठा अणु
		काष्ठा media_entity *entity;
		काष्ठा list_head *link;
	पूर्ण stack[MEDIA_ENTITY_ENUM_MAX_DEPTH];

	काष्ठा media_entity_क्रमागत ent_क्रमागत;
	पूर्णांक top;
पूर्ण;

/**
 * काष्ठा media_pipeline - Media pipeline related inक्रमmation
 *
 * @streaming_count:	Streaming start count - streaming stop count
 * @graph:		Media graph walk during pipeline start / stop
 */
काष्ठा media_pipeline अणु
	पूर्णांक streaming_count;
	काष्ठा media_graph graph;
पूर्ण;

/**
 * काष्ठा media_link - A link object part of a media graph.
 *
 * @graph_obj:	Embedded काष्ठाure containing the media object common data
 * @list:	Linked list associated with an entity or an पूर्णांकerface that
 *		owns the link.
 * @gobj0:	Part of a जोड़. Used to get the poपूर्णांकer क्रम the first
 *		graph_object of the link.
 * @source:	Part of a जोड़. Used only अगर the first object (gobj0) is
 *		a pad. In that हाल, it represents the source pad.
 * @पूर्णांकf:	Part of a जोड़. Used only अगर the first object (gobj0) is
 *		an पूर्णांकerface.
 * @gobj1:	Part of a जोड़. Used to get the poपूर्णांकer क्रम the second
 *		graph_object of the link.
 * @sink:	Part of a जोड़. Used only अगर the second object (gobj1) is
 *		a pad. In that हाल, it represents the sink pad.
 * @entity:	Part of a जोड़. Used only अगर the second object (gobj1) is
 *		an entity.
 * @reverse:	Poपूर्णांकer to the link क्रम the reverse direction of a pad to pad
 *		link.
 * @flags:	Link flags, as defined in uapi/media.h (MEDIA_LNK_FL_*)
 * @is_backlink: Indicate अगर the link is a backlink.
 */
काष्ठा media_link अणु
	काष्ठा media_gobj graph_obj;
	काष्ठा list_head list;
	जोड़ अणु
		काष्ठा media_gobj *gobj0;
		काष्ठा media_pad *source;
		काष्ठा media_पूर्णांकerface *पूर्णांकf;
	पूर्ण;
	जोड़ अणु
		काष्ठा media_gobj *gobj1;
		काष्ठा media_pad *sink;
		काष्ठा media_entity *entity;
	पूर्ण;
	काष्ठा media_link *reverse;
	अचिन्हित दीर्घ flags;
	bool is_backlink;
पूर्ण;

/**
 * क्रमागत media_pad_संकेत_type - type of the संकेत inside a media pad
 *
 * @PAD_SIGNAL_DEFAULT:
 *	Default संकेत. Use this when all inमाला_दो or all outमाला_दो are
 *	uniquely identअगरied by the pad number.
 * @PAD_SIGNAL_ANALOG:
 *	The pad contains an analog संकेत. It can be Radio Frequency,
 *	Intermediate Frequency, a baseband संकेत or sub-carriers.
 *	Tuner inमाला_दो, IF-PLL demodulators, composite and s-video संकेतs
 *	should use it.
 * @PAD_SIGNAL_DV:
 *	Contains a digital video संकेत, with can be a bitstream of samples
 *	taken from an analog TV video source. On such हाल, it usually
 *	contains the VBI data on it.
 * @PAD_SIGNAL_AUDIO:
 *	Contains an Intermediate Frequency analog संकेत from an audio
 *	sub-carrier or an audio bitstream. IF संकेतs are provided by tuners
 *	and consumed by	audio AM/FM decoders. Bitstream audio is provided by
 *	an audio decoder.
 */
क्रमागत media_pad_संकेत_type अणु
	PAD_SIGNAL_DEFAULT = 0,
	PAD_SIGNAL_ANALOG,
	PAD_SIGNAL_DV,
	PAD_SIGNAL_AUDIO,
पूर्ण;

/**
 * काष्ठा media_pad - A media pad graph object.
 *
 * @graph_obj:	Embedded काष्ठाure containing the media object common data
 * @entity:	Entity this pad beदीर्घs to
 * @index:	Pad index in the entity pads array, numbered from 0 to n
 * @sig_type:	Type of the संकेत inside a media pad
 * @flags:	Pad flags, as defined in
 *		:ref:`include/uapi/linux/media.h <media_header>`
 *		(seek क्रम ``MEDIA_PAD_FL_*``)
 */
काष्ठा media_pad अणु
	काष्ठा media_gobj graph_obj;	/* must be first field in काष्ठा */
	काष्ठा media_entity *entity;
	u16 index;
	क्रमागत media_pad_संकेत_type sig_type;
	अचिन्हित दीर्घ flags;
पूर्ण;

/**
 * काष्ठा media_entity_operations - Media entity operations
 * @get_fwnode_pad:	Return the pad number based on a fwnode endpoपूर्णांक or
 *			a negative value on error. This operation can be used
 *			to map a fwnode to a media pad number. Optional.
 * @link_setup:		Notअगरy the entity of link changes. The operation can
 *			वापस an error, in which हाल link setup will be
 *			cancelled. Optional.
 * @link_validate:	Return whether a link is valid from the entity poपूर्णांक of
 *			view. The media_pipeline_start() function
 *			validates all links by calling this operation. Optional.
 *
 * .. note::
 *
 *    Those these callbacks are called with काष्ठा &media_device.graph_mutex
 *    mutex held.
 */
काष्ठा media_entity_operations अणु
	पूर्णांक (*get_fwnode_pad)(काष्ठा media_entity *entity,
			      काष्ठा fwnode_endpoपूर्णांक *endpoपूर्णांक);
	पूर्णांक (*link_setup)(काष्ठा media_entity *entity,
			  स्थिर काष्ठा media_pad *local,
			  स्थिर काष्ठा media_pad *remote, u32 flags);
	पूर्णांक (*link_validate)(काष्ठा media_link *link);
पूर्ण;

/**
 * क्रमागत media_entity_type - Media entity type
 *
 * @MEDIA_ENTITY_TYPE_BASE:
 *	The entity isn't embedded in another subप्रणाली काष्ठाure.
 * @MEDIA_ENTITY_TYPE_VIDEO_DEVICE:
 *	The entity is embedded in a काष्ठा video_device instance.
 * @MEDIA_ENTITY_TYPE_V4L2_SUBDEV:
 *	The entity is embedded in a काष्ठा v4l2_subdev instance.
 *
 * Media entity objects are often not instantiated directly, but the media
 * entity काष्ठाure is inherited by (through embedding) other subप्रणाली-specअगरic
 * काष्ठाures. The media entity type identअगरies the type of the subclass
 * काष्ठाure that implements a media entity instance.
 *
 * This allows runसमय type identअगरication of media entities and safe casting to
 * the correct object type. For instance, a media entity काष्ठाure instance
 * embedded in a v4l2_subdev काष्ठाure instance will have the type
 * %MEDIA_ENTITY_TYPE_V4L2_SUBDEV and can safely be cast to a &v4l2_subdev
 * काष्ठाure using the container_of() macro.
 */
क्रमागत media_entity_type अणु
	MEDIA_ENTITY_TYPE_BASE,
	MEDIA_ENTITY_TYPE_VIDEO_DEVICE,
	MEDIA_ENTITY_TYPE_V4L2_SUBDEV,
पूर्ण;

/**
 * काष्ठा media_entity - A media entity graph object.
 *
 * @graph_obj:	Embedded काष्ठाure containing the media object common data.
 * @name:	Entity name.
 * @obj_type:	Type of the object that implements the media_entity.
 * @function:	Entity मुख्य function, as defined in
 *		:ref:`include/uapi/linux/media.h <media_header>`
 *		(seek क्रम ``MEDIA_ENT_F_*``)
 * @flags:	Entity flags, as defined in
 *		:ref:`include/uapi/linux/media.h <media_header>`
 *		(seek क्रम ``MEDIA_ENT_FL_*``)
 * @num_pads:	Number of sink and source pads.
 * @num_links:	Total number of links, क्रमward and back, enabled and disabled.
 * @num_backlinks: Number of backlinks
 * @पूर्णांकernal_idx: An unique पूर्णांकernal entity specअगरic number. The numbers are
 *		re-used अगर entities are unरेजिस्टरed or रेजिस्टरed again.
 * @pads:	Pads array with the size defined by @num_pads.
 * @links:	List of data links.
 * @ops:	Entity operations.
 * @stream_count: Stream count क्रम the entity.
 * @use_count:	Use count क्रम the entity.
 * @pipe:	Pipeline this entity beदीर्घs to.
 * @info:	Union with devnode inक्रमmation.  Kept just क्रम backward
 *		compatibility.
 * @info.dev:	Contains device major and minor info.
 * @info.dev.major: device node major, अगर the device is a devnode.
 * @info.dev.minor: device node minor, अगर the device is a devnode.
 * @major:	Devnode major number (zero अगर not applicable). Kept just
 *		क्रम backward compatibility.
 * @minor:	Devnode minor number (zero अगर not applicable). Kept just
 *		क्रम backward compatibility.
 *
 * .. note::
 *
 *    @stream_count and @use_count reference counts must never be
 *    negative, but are चिन्हित पूर्णांकegers on purpose: a simple ``WARN_ON(<0)``
 *    check can be used to detect reference count bugs that would make them
 *    negative.
 */
काष्ठा media_entity अणु
	काष्ठा media_gobj graph_obj;	/* must be first field in काष्ठा */
	स्थिर अक्षर *name;
	क्रमागत media_entity_type obj_type;
	u32 function;
	अचिन्हित दीर्घ flags;

	u16 num_pads;
	u16 num_links;
	u16 num_backlinks;
	पूर्णांक पूर्णांकernal_idx;

	काष्ठा media_pad *pads;
	काष्ठा list_head links;

	स्थिर काष्ठा media_entity_operations *ops;

	पूर्णांक stream_count;
	पूर्णांक use_count;

	काष्ठा media_pipeline *pipe;

	जोड़ अणु
		काष्ठा अणु
			u32 major;
			u32 minor;
		पूर्ण dev;
	पूर्ण info;
पूर्ण;

/**
 * काष्ठा media_पूर्णांकerface - A media पूर्णांकerface graph object.
 *
 * @graph_obj:		embedded graph object
 * @links:		List of links poपूर्णांकing to graph entities
 * @type:		Type of the पूर्णांकerface as defined in
 *			:ref:`include/uapi/linux/media.h <media_header>`
 *			(seek क्रम ``MEDIA_INTF_T_*``)
 * @flags:		Interface flags as defined in
 *			:ref:`include/uapi/linux/media.h <media_header>`
 *			(seek क्रम ``MEDIA_INTF_FL_*``)
 *
 * .. note::
 *
 *    Currently, no flags क्रम &media_पूर्णांकerface is defined.
 */
काष्ठा media_पूर्णांकerface अणु
	काष्ठा media_gobj		graph_obj;
	काष्ठा list_head		links;
	u32				type;
	u32				flags;
पूर्ण;

/**
 * काष्ठा media_पूर्णांकf_devnode - A media पूर्णांकerface via a device node.
 *
 * @पूर्णांकf:	embedded पूर्णांकerface object
 * @major:	Major number of a device node
 * @minor:	Minor number of a device node
 */
काष्ठा media_पूर्णांकf_devnode अणु
	काष्ठा media_पूर्णांकerface		पूर्णांकf;

	/* Should match the fields at media_v2_पूर्णांकf_devnode */
	u32				major;
	u32				minor;
पूर्ण;

/**
 * media_entity_id() - वापस the media entity graph object id
 *
 * @entity:	poपूर्णांकer to &media_entity
 */
अटल अंतरभूत u32 media_entity_id(काष्ठा media_entity *entity)
अणु
	वापस entity->graph_obj.id;
पूर्ण

/**
 * media_type() - वापस the media object type
 *
 * @gobj:	Poपूर्णांकer to the काष्ठा &media_gobj graph object
 */
अटल अंतरभूत क्रमागत media_gobj_type media_type(काष्ठा media_gobj *gobj)
अणु
	वापस gobj->id >> MEDIA_BITS_PER_ID;
पूर्ण

/**
 * media_id() - वापस the media object ID
 *
 * @gobj:	Poपूर्णांकer to the काष्ठा &media_gobj graph object
 */
अटल अंतरभूत u32 media_id(काष्ठा media_gobj *gobj)
अणु
	वापस gobj->id & MEDIA_ID_MASK;
पूर्ण

/**
 * media_gobj_gen_id() - encapsulates type and ID on at the object ID
 *
 * @type:	object type as define at क्रमागत &media_gobj_type.
 * @local_id:	next ID, from काष्ठा &media_device.id.
 */
अटल अंतरभूत u32 media_gobj_gen_id(क्रमागत media_gobj_type type, u64 local_id)
अणु
	u32 id;

	id = type << MEDIA_BITS_PER_ID;
	id |= local_id & MEDIA_ID_MASK;

	वापस id;
पूर्ण

/**
 * is_media_entity_v4l2_video_device() - Check अगर the entity is a video_device
 * @entity:	poपूर्णांकer to entity
 *
 * Return: %true अगर the entity is an instance of a video_device object and can
 * safely be cast to a काष्ठा video_device using the container_of() macro, or
 * %false otherwise.
 */
अटल अंतरभूत bool is_media_entity_v4l2_video_device(काष्ठा media_entity *entity)
अणु
	वापस entity && entity->obj_type == MEDIA_ENTITY_TYPE_VIDEO_DEVICE;
पूर्ण

/**
 * is_media_entity_v4l2_subdev() - Check अगर the entity is a v4l2_subdev
 * @entity:	poपूर्णांकer to entity
 *
 * Return: %true अगर the entity is an instance of a &v4l2_subdev object and can
 * safely be cast to a काष्ठा &v4l2_subdev using the container_of() macro, or
 * %false otherwise.
 */
अटल अंतरभूत bool is_media_entity_v4l2_subdev(काष्ठा media_entity *entity)
अणु
	वापस entity && entity->obj_type == MEDIA_ENTITY_TYPE_V4L2_SUBDEV;
पूर्ण

/**
 * __media_entity_क्रमागत_init - Initialise an entity क्रमागतeration
 *
 * @ent_क्रमागत: Entity क्रमागतeration to be initialised
 * @idx_max: Maximum number of entities in the क्रमागतeration
 *
 * Return: Returns zero on success or a negative error code.
 */
__must_check पूर्णांक __media_entity_क्रमागत_init(काष्ठा media_entity_क्रमागत *ent_क्रमागत,
					  पूर्णांक idx_max);

/**
 * media_entity_क्रमागत_cleanup - Release resources of an entity क्रमागतeration
 *
 * @ent_क्रमागत: Entity क्रमागतeration to be released
 */
व्योम media_entity_क्रमागत_cleanup(काष्ठा media_entity_क्रमागत *ent_क्रमागत);

/**
 * media_entity_क्रमागत_zero - Clear the entire क्रमागत
 *
 * @ent_क्रमागत: Entity क्रमागतeration to be cleared
 */
अटल अंतरभूत व्योम media_entity_क्रमागत_zero(काष्ठा media_entity_क्रमागत *ent_क्रमागत)
अणु
	biपंचांगap_zero(ent_क्रमागत->bmap, ent_क्रमागत->idx_max);
पूर्ण

/**
 * media_entity_क्रमागत_set - Mark a single entity in the क्रमागत
 *
 * @ent_क्रमागत: Entity क्रमागतeration
 * @entity: Entity to be marked
 */
अटल अंतरभूत व्योम media_entity_क्रमागत_set(काष्ठा media_entity_क्रमागत *ent_क्रमागत,
					 काष्ठा media_entity *entity)
अणु
	अगर (WARN_ON(entity->पूर्णांकernal_idx >= ent_क्रमागत->idx_max))
		वापस;

	__set_bit(entity->पूर्णांकernal_idx, ent_क्रमागत->bmap);
पूर्ण

/**
 * media_entity_क्रमागत_clear - Unmark a single entity in the क्रमागत
 *
 * @ent_क्रमागत: Entity क्रमागतeration
 * @entity: Entity to be unmarked
 */
अटल अंतरभूत व्योम media_entity_क्रमागत_clear(काष्ठा media_entity_क्रमागत *ent_क्रमागत,
					   काष्ठा media_entity *entity)
अणु
	अगर (WARN_ON(entity->पूर्णांकernal_idx >= ent_क्रमागत->idx_max))
		वापस;

	__clear_bit(entity->पूर्णांकernal_idx, ent_क्रमागत->bmap);
पूर्ण

/**
 * media_entity_क्रमागत_test - Test whether the entity is marked
 *
 * @ent_क्रमागत: Entity क्रमागतeration
 * @entity: Entity to be tested
 *
 * Returns %true अगर the entity was marked.
 */
अटल अंतरभूत bool media_entity_क्रमागत_test(काष्ठा media_entity_क्रमागत *ent_क्रमागत,
					  काष्ठा media_entity *entity)
अणु
	अगर (WARN_ON(entity->पूर्णांकernal_idx >= ent_क्रमागत->idx_max))
		वापस true;

	वापस test_bit(entity->पूर्णांकernal_idx, ent_क्रमागत->bmap);
पूर्ण

/**
 * media_entity_क्रमागत_test_and_set - Test whether the entity is marked,
 *	and mark it
 *
 * @ent_क्रमागत: Entity क्रमागतeration
 * @entity: Entity to be tested
 *
 * Returns %true अगर the entity was marked, and mark it beक्रमe करोing so.
 */
अटल अंतरभूत bool
media_entity_क्रमागत_test_and_set(काष्ठा media_entity_क्रमागत *ent_क्रमागत,
			       काष्ठा media_entity *entity)
अणु
	अगर (WARN_ON(entity->पूर्णांकernal_idx >= ent_क्रमागत->idx_max))
		वापस true;

	वापस __test_and_set_bit(entity->पूर्णांकernal_idx, ent_क्रमागत->bmap);
पूर्ण

/**
 * media_entity_क्रमागत_empty - Test whether the entire क्रमागत is empty
 *
 * @ent_क्रमागत: Entity क्रमागतeration
 *
 * Return: %true अगर the entity was empty.
 */
अटल अंतरभूत bool media_entity_क्रमागत_empty(काष्ठा media_entity_क्रमागत *ent_क्रमागत)
अणु
	वापस biपंचांगap_empty(ent_क्रमागत->bmap, ent_क्रमागत->idx_max);
पूर्ण

/**
 * media_entity_क्रमागत_पूर्णांकersects - Test whether two क्रमागतs पूर्णांकersect
 *
 * @ent_क्रमागत1: First entity क्रमागतeration
 * @ent_क्रमागत2: Second entity क्रमागतeration
 *
 * Return: %true अगर entity क्रमागतerations @ent_क्रमागत1 and @ent_क्रमागत2 पूर्णांकersect,
 * otherwise %false.
 */
अटल अंतरभूत bool media_entity_क्रमागत_पूर्णांकersects(
	काष्ठा media_entity_क्रमागत *ent_क्रमागत1,
	काष्ठा media_entity_क्रमागत *ent_क्रमागत2)
अणु
	WARN_ON(ent_क्रमागत1->idx_max != ent_क्रमागत2->idx_max);

	वापस biपंचांगap_पूर्णांकersects(ent_क्रमागत1->bmap, ent_क्रमागत2->bmap,
				 min(ent_क्रमागत1->idx_max, ent_क्रमागत2->idx_max));
पूर्ण

/**
 * gobj_to_entity - वापसs the काष्ठा &media_entity poपूर्णांकer from the
 *	@gobj contained on it.
 *
 * @gobj: Poपूर्णांकer to the काष्ठा &media_gobj graph object
 */
#घोषणा gobj_to_entity(gobj) \
		container_of(gobj, काष्ठा media_entity, graph_obj)

/**
 * gobj_to_pad - वापसs the काष्ठा &media_pad poपूर्णांकer from the
 *	@gobj contained on it.
 *
 * @gobj: Poपूर्णांकer to the काष्ठा &media_gobj graph object
 */
#घोषणा gobj_to_pad(gobj) \
		container_of(gobj, काष्ठा media_pad, graph_obj)

/**
 * gobj_to_link - वापसs the काष्ठा &media_link poपूर्णांकer from the
 *	@gobj contained on it.
 *
 * @gobj: Poपूर्णांकer to the काष्ठा &media_gobj graph object
 */
#घोषणा gobj_to_link(gobj) \
		container_of(gobj, काष्ठा media_link, graph_obj)

/**
 * gobj_to_पूर्णांकf - वापसs the काष्ठा &media_पूर्णांकerface poपूर्णांकer from the
 *	@gobj contained on it.
 *
 * @gobj: Poपूर्णांकer to the काष्ठा &media_gobj graph object
 */
#घोषणा gobj_to_पूर्णांकf(gobj) \
		container_of(gobj, काष्ठा media_पूर्णांकerface, graph_obj)

/**
 * पूर्णांकf_to_devnode - वापसs the काष्ठा media_पूर्णांकf_devnode poपूर्णांकer from the
 *	@पूर्णांकf contained on it.
 *
 * @पूर्णांकf: Poपूर्णांकer to काष्ठा &media_पूर्णांकf_devnode
 */
#घोषणा पूर्णांकf_to_devnode(पूर्णांकf) \
		container_of(पूर्णांकf, काष्ठा media_पूर्णांकf_devnode, पूर्णांकf)

/**
 *  media_gobj_create - Initialize a graph object
 *
 * @mdev:	Poपूर्णांकer to the &media_device that contains the object
 * @type:	Type of the object
 * @gobj:	Poपूर्णांकer to the काष्ठा &media_gobj graph object
 *
 * This routine initializes the embedded काष्ठा &media_gobj inside a
 * media graph object. It is called स्वतःmatically अगर ``media_*_create``
 * function calls are used. However, अगर the object (entity, link, pad,
 * पूर्णांकerface) is embedded on some other object, this function should be
 * called beक्रमe रेजिस्टरing the object at the media controller.
 */
व्योम media_gobj_create(काष्ठा media_device *mdev,
		    क्रमागत media_gobj_type type,
		    काष्ठा media_gobj *gobj);

/**
 *  media_gobj_destroy - Stop using a graph object on a media device
 *
 * @gobj:	Poपूर्णांकer to the काष्ठा &media_gobj graph object
 *
 * This should be called by all routines like media_device_unरेजिस्टर()
 * that हटाओ/destroy media graph objects.
 */
व्योम media_gobj_destroy(काष्ठा media_gobj *gobj);

/**
 * media_entity_pads_init() - Initialize the entity pads
 *
 * @entity:	entity where the pads beदीर्घ
 * @num_pads:	total number of sink and source pads
 * @pads:	Array of @num_pads pads.
 *
 * The pads array is managed by the entity driver and passed to
 * media_entity_pads_init() where its poपूर्णांकer will be stored in the
 * &media_entity काष्ठाure.
 *
 * If no pads are needed, drivers could either directly fill
 * &media_entity->num_pads with 0 and &media_entity->pads with %शून्य or call
 * this function that will करो the same.
 *
 * As the number of pads is known in advance, the pads array is not allocated
 * dynamically but is managed by the entity driver. Most drivers will embed the
 * pads array in a driver-specअगरic काष्ठाure, aव्योमing dynamic allocation.
 *
 * Drivers must set the direction of every pad in the pads array beक्रमe calling
 * media_entity_pads_init(). The function will initialize the other pads fields.
 */
पूर्णांक media_entity_pads_init(काष्ठा media_entity *entity, u16 num_pads,
		      काष्ठा media_pad *pads);

/**
 * media_entity_cleanup() - मुक्त resources associated with an entity
 *
 * @entity:	entity where the pads beदीर्घ
 *
 * This function must be called during the cleanup phase after unरेजिस्टरing
 * the entity (currently, it करोes nothing).
 */
#अगर IS_ENABLED(CONFIG_MEDIA_CONTROLLER)
अटल अंतरभूत व्योम media_entity_cleanup(काष्ठा media_entity *entity) अणुपूर्ण
#अन्यथा
#घोषणा media_entity_cleanup(entity) करो अणु पूर्ण जबतक (false)
#पूर्ण_अगर

/**
 * media_get_pad_index() - retrieves a pad index from an entity
 *
 * @entity:	entity where the pads beदीर्घ
 * @is_sink:	true अगर the pad is a sink, false अगर it is a source
 * @sig_type:	type of संकेत of the pad to be search
 *
 * This helper function finds the first pad index inside an entity that
 * satisfies both @is_sink and @sig_type conditions.
 *
 * Return:
 *
 * On success, वापस the pad number. If the pad was not found or the media
 * entity is a शून्य poपूर्णांकer, वापस -EINVAL.
 */
पूर्णांक media_get_pad_index(काष्ठा media_entity *entity, bool is_sink,
			क्रमागत media_pad_संकेत_type sig_type);

/**
 * media_create_pad_link() - creates a link between two entities.
 *
 * @source:	poपूर्णांकer to &media_entity of the source pad.
 * @source_pad:	number of the source pad in the pads array
 * @sink:	poपूर्णांकer to &media_entity of the sink pad.
 * @sink_pad:	number of the sink pad in the pads array.
 * @flags:	Link flags, as defined in
 *		:ref:`include/uapi/linux/media.h <media_header>`
 *		( seek क्रम ``MEDIA_LNK_FL_*``)
 *
 * Valid values क्रम flags:
 *
 * %MEDIA_LNK_FL_ENABLED
 *   Indicates that the link is enabled and can be used to transfer media data.
 *   When two or more links target a sink pad, only one of them can be
 *   enabled at a समय.
 *
 * %MEDIA_LNK_FL_IMMUTABLE
 *   Indicates that the link enabled state can't be modअगरied at runसमय. If
 *   %MEDIA_LNK_FL_IMMUTABLE is set, then %MEDIA_LNK_FL_ENABLED must also be
 *   set, since an immutable link is always enabled.
 *
 * .. note::
 *
 *    Beक्रमe calling this function, media_entity_pads_init() and
 *    media_device_रेजिस्टर_entity() should be called previously क्रम both ends.
 */
__must_check पूर्णांक media_create_pad_link(काष्ठा media_entity *source,
			u16 source_pad, काष्ठा media_entity *sink,
			u16 sink_pad, u32 flags);

/**
 * media_create_pad_links() - creates a link between two entities.
 *
 * @mdev: Poपूर्णांकer to the media_device that contains the object
 * @source_function: Function of the source entities. Used only अगर @source is
 *	शून्य.
 * @source: poपूर्णांकer to &media_entity of the source pad. If शून्य, it will use
 *	all entities that matches the @sink_function.
 * @source_pad: number of the source pad in the pads array
 * @sink_function: Function of the sink entities. Used only अगर @sink is शून्य.
 * @sink: poपूर्णांकer to &media_entity of the sink pad. If शून्य, it will use
 *	all entities that matches the @sink_function.
 * @sink_pad: number of the sink pad in the pads array.
 * @flags: Link flags, as defined in include/uapi/linux/media.h.
 * @allow_both_undefined: अगर %true, then both @source and @sink can be शून्य.
 *	In such हाल, it will create a crossbar between all entities that
 *	matches @source_function to all entities that matches @sink_function.
 *	If %false, it will वापस 0 and won't create any link अगर both @source
 *	and @sink are शून्य.
 *
 * Valid values क्रम flags:
 *
 * A %MEDIA_LNK_FL_ENABLED flag indicates that the link is enabled and can be
 *	used to transfer media data. If multiple links are created and this
 *	flag is passed as an argument, only the first created link will have
 *	this flag.
 *
 * A %MEDIA_LNK_FL_IMMUTABLE flag indicates that the link enabled state can't
 *	be modअगरied at runसमय. If %MEDIA_LNK_FL_IMMUTABLE is set, then
 *	%MEDIA_LNK_FL_ENABLED must also be set since an immutable link is
 *	always enabled.
 *
 * It is common क्रम some devices to have multiple source and/or sink entities
 * of the same type that should be linked. While media_create_pad_link()
 * creates link by link, this function is meant to allow 1:n, n:1 and even
 * cross-bar (n:n) links.
 *
 * .. note::
 *
 *    Beक्रमe calling this function, media_entity_pads_init() and
 *    media_device_रेजिस्टर_entity() should be called previously क्रम the
 *    entities to be linked.
 */
पूर्णांक media_create_pad_links(स्थिर काष्ठा media_device *mdev,
			   स्थिर u32 source_function,
			   काष्ठा media_entity *source,
			   स्थिर u16 source_pad,
			   स्थिर u32 sink_function,
			   काष्ठा media_entity *sink,
			   स्थिर u16 sink_pad,
			   u32 flags,
			   स्थिर bool allow_both_undefined);

व्योम __media_entity_हटाओ_links(काष्ठा media_entity *entity);

/**
 * media_entity_हटाओ_links() - हटाओ all links associated with an entity
 *
 * @entity:	poपूर्णांकer to &media_entity
 *
 * .. note::
 *
 *    This is called स्वतःmatically when an entity is unरेजिस्टरed via
 *    media_device_रेजिस्टर_entity().
 */
व्योम media_entity_हटाओ_links(काष्ठा media_entity *entity);

/**
 * __media_entity_setup_link - Configure a media link without locking
 * @link: The link being configured
 * @flags: Link configuration flags
 *
 * The bulk of link setup is handled by the two entities connected through the
 * link. This function notअगरies both entities of the link configuration change.
 *
 * If the link is immutable or अगर the current and new configuration are
 * identical, वापस immediately.
 *
 * The user is expected to hold link->source->parent->mutex. If not,
 * media_entity_setup_link() should be used instead.
 */
पूर्णांक __media_entity_setup_link(काष्ठा media_link *link, u32 flags);

/**
 * media_entity_setup_link() - changes the link flags properties in runसमय
 *
 * @link:	poपूर्णांकer to &media_link
 * @flags:	the requested new link flags
 *
 * The only configurable property is the %MEDIA_LNK_FL_ENABLED link flag
 * to enable/disable a link. Links marked with the
 * %MEDIA_LNK_FL_IMMUTABLE link flag can not be enabled or disabled.
 *
 * When a link is enabled or disabled, the media framework calls the
 * link_setup operation क्रम the two entities at the source and sink of the
 * link, in that order. If the second link_setup call fails, another
 * link_setup call is made on the first entity to restore the original link
 * flags.
 *
 * Media device drivers can be notअगरied of link setup operations by setting the
 * &media_device.link_notअगरy poपूर्णांकer to a callback function. If provided, the
 * notअगरication callback will be called beक्रमe enabling and after disabling
 * links.
 *
 * Entity drivers must implement the link_setup operation अगर any of their links
 * is non-immutable. The operation must either configure the hardware or store
 * the configuration inक्रमmation to be applied later.
 *
 * Link configuration must not have any side effect on other links. If an
 * enabled link at a sink pad prevents another link at the same pad from
 * being enabled, the link_setup operation must वापस %-EBUSY and can't
 * implicitly disable the first enabled link.
 *
 * .. note::
 *
 *    The valid values of the flags क्रम the link is the same as described
 *    on media_create_pad_link(), क्रम pad to pad links or the same as described
 *    on media_create_पूर्णांकf_link(), क्रम पूर्णांकerface to entity links.
 */
पूर्णांक media_entity_setup_link(काष्ठा media_link *link, u32 flags);

/**
 * media_entity_find_link - Find a link between two pads
 * @source: Source pad
 * @sink: Sink pad
 *
 * Return: वापसs a poपूर्णांकer to the link between the two entities. If no
 * such link exists, वापस %शून्य.
 */
काष्ठा media_link *media_entity_find_link(काष्ठा media_pad *source,
		काष्ठा media_pad *sink);

/**
 * media_entity_remote_pad - Find the pad at the remote end of a link
 * @pad: Pad at the local end of the link
 *
 * Search क्रम a remote pad connected to the given pad by iterating over all
 * links originating or terminating at that pad until an enabled link is found.
 *
 * Return: वापसs a poपूर्णांकer to the pad at the remote end of the first found
 * enabled link, or %शून्य अगर no enabled link has been found.
 */
काष्ठा media_pad *media_entity_remote_pad(स्थिर काष्ठा media_pad *pad);

/**
 * media_entity_get_fwnode_pad - Get pad number from fwnode
 *
 * @entity: The entity
 * @fwnode: Poपूर्णांकer to the fwnode_handle which should be used to find the pad
 * @direction_flags: Expected direction of the pad, as defined in
 *		     :ref:`include/uapi/linux/media.h <media_header>`
 *		     (seek क्रम ``MEDIA_PAD_FL_*``)
 *
 * This function can be used to resolve the media pad number from
 * a fwnode. This is useful क्रम devices which use more complex
 * mappings of media pads.
 *
 * If the entity करोes not implement the get_fwnode_pad() operation
 * then this function searches the entity क्रम the first pad that
 * matches the @direction_flags.
 *
 * Return: वापसs the pad number on success or a negative error code.
 */
पूर्णांक media_entity_get_fwnode_pad(काष्ठा media_entity *entity,
				काष्ठा fwnode_handle *fwnode,
				अचिन्हित दीर्घ direction_flags);

/**
 * media_graph_walk_init - Allocate resources used by graph walk.
 *
 * @graph: Media graph काष्ठाure that will be used to walk the graph
 * @mdev: Poपूर्णांकer to the &media_device that contains the object
 *
 * The caller is required to hold the media_device graph_mutex during the graph
 * walk until the graph state is released.
 *
 * Returns zero on success or a negative error code otherwise.
 */
__must_check पूर्णांक media_graph_walk_init(
	काष्ठा media_graph *graph, काष्ठा media_device *mdev);

/**
 * media_graph_walk_cleanup - Release resources used by graph walk.
 *
 * @graph: Media graph काष्ठाure that will be used to walk the graph
 */
व्योम media_graph_walk_cleanup(काष्ठा media_graph *graph);

/**
 * media_graph_walk_start - Start walking the media graph at a
 *	given entity
 *
 * @graph: Media graph काष्ठाure that will be used to walk the graph
 * @entity: Starting entity
 *
 * Beक्रमe using this function, media_graph_walk_init() must be
 * used to allocate resources used क्रम walking the graph. This
 * function initializes the graph traversal काष्ठाure to walk the
 * entities graph starting at the given entity. The traversal
 * काष्ठाure must not be modअगरied by the caller during graph
 * traversal. After the graph walk, the resources must be released
 * using media_graph_walk_cleanup().
 */
व्योम media_graph_walk_start(काष्ठा media_graph *graph,
			    काष्ठा media_entity *entity);

/**
 * media_graph_walk_next - Get the next entity in the graph
 * @graph: Media graph काष्ठाure
 *
 * Perक्रमm a depth-first traversal of the given media entities graph.
 *
 * The graph काष्ठाure must have been previously initialized with a call to
 * media_graph_walk_start().
 *
 * Return: वापसs the next entity in the graph or %शून्य अगर the whole graph
 * have been traversed.
 */
काष्ठा media_entity *media_graph_walk_next(काष्ठा media_graph *graph);

/**
 * media_pipeline_start - Mark a pipeline as streaming
 * @entity: Starting entity
 * @pipe: Media pipeline to be asचिन्हित to all entities in the pipeline.
 *
 * Mark all entities connected to a given entity through enabled links, either
 * directly or indirectly, as streaming. The given pipeline object is asचिन्हित
 * to every entity in the pipeline and stored in the media_entity pipe field.
 *
 * Calls to this function can be nested, in which हाल the same number of
 * media_pipeline_stop() calls will be required to stop streaming. The
 * pipeline poपूर्णांकer must be identical क्रम all nested calls to
 * media_pipeline_start().
 */
__must_check पूर्णांक media_pipeline_start(काष्ठा media_entity *entity,
				      काष्ठा media_pipeline *pipe);
/**
 * __media_pipeline_start - Mark a pipeline as streaming
 *
 * @entity: Starting entity
 * @pipe: Media pipeline to be asचिन्हित to all entities in the pipeline.
 *
 * ..note:: This is the non-locking version of media_pipeline_start()
 */
__must_check पूर्णांक __media_pipeline_start(काष्ठा media_entity *entity,
					काष्ठा media_pipeline *pipe);

/**
 * media_pipeline_stop - Mark a pipeline as not streaming
 * @entity: Starting entity
 *
 * Mark all entities connected to a given entity through enabled links, either
 * directly or indirectly, as not streaming. The media_entity pipe field is
 * reset to %शून्य.
 *
 * If multiple calls to media_pipeline_start() have been made, the same
 * number of calls to this function are required to mark the pipeline as not
 * streaming.
 */
व्योम media_pipeline_stop(काष्ठा media_entity *entity);

/**
 * __media_pipeline_stop - Mark a pipeline as not streaming
 *
 * @entity: Starting entity
 *
 * .. note:: This is the non-locking version of media_pipeline_stop()
 */
व्योम __media_pipeline_stop(काष्ठा media_entity *entity);

/**
 * media_devnode_create() - creates and initializes a device node पूर्णांकerface
 *
 * @mdev:	poपूर्णांकer to काष्ठा &media_device
 * @type:	type of the पूर्णांकerface, as given by
 *		:ref:`include/uapi/linux/media.h <media_header>`
 *		( seek क्रम ``MEDIA_INTF_T_*``) macros.
 * @flags:	Interface flags, as defined in
 *		:ref:`include/uapi/linux/media.h <media_header>`
 *		( seek क्रम ``MEDIA_INTF_FL_*``)
 * @major:	Device node major number.
 * @minor:	Device node minor number.
 *
 * Return: अगर succeeded, वापसs a poपूर्णांकer to the newly allocated
 *	&media_पूर्णांकf_devnode poपूर्णांकer.
 *
 * .. note::
 *
 *    Currently, no flags क्रम &media_पूर्णांकerface is defined.
 */
काष्ठा media_पूर्णांकf_devnode *
__must_check media_devnode_create(काष्ठा media_device *mdev,
				  u32 type, u32 flags,
				  u32 major, u32 minor);
/**
 * media_devnode_हटाओ() - हटाओs a device node पूर्णांकerface
 *
 * @devnode:	poपूर्णांकer to &media_पूर्णांकf_devnode to be मुक्तd.
 *
 * When a device node पूर्णांकerface is हटाओd, all links to it are स्वतःmatically
 * हटाओd.
 */
व्योम media_devnode_हटाओ(काष्ठा media_पूर्णांकf_devnode *devnode);
काष्ठा media_link *

/**
 * media_create_पूर्णांकf_link() - creates a link between an entity and an पूर्णांकerface
 *
 * @entity:	poपूर्णांकer to %media_entity
 * @पूर्णांकf:	poपूर्णांकer to %media_पूर्णांकerface
 * @flags:	Link flags, as defined in
 *		:ref:`include/uapi/linux/media.h <media_header>`
 *		( seek क्रम ``MEDIA_LNK_FL_*``)
 *
 *
 * Valid values क्रम flags:
 *
 * %MEDIA_LNK_FL_ENABLED
 *   Indicates that the पूर्णांकerface is connected to the entity hardware.
 *   That's the शेष value क्रम पूर्णांकerfaces. An पूर्णांकerface may be disabled अगर
 *   the hardware is busy due to the usage of some other पूर्णांकerface that it is
 *   currently controlling the hardware.
 *
 *   A typical example is an hybrid TV device that handle only one type of
 *   stream on a given समय. So, when the digital TV is streaming,
 *   the V4L2 पूर्णांकerfaces won't be enabled, as such device is not able to
 *   also stream analog TV or radio.
 *
 * .. note::
 *
 *    Beक्रमe calling this function, media_devnode_create() should be called क्रम
 *    the पूर्णांकerface and media_device_रेजिस्टर_entity() should be called क्रम the
 *    पूर्णांकerface that will be part of the link.
 */
__must_check media_create_पूर्णांकf_link(काष्ठा media_entity *entity,
				    काष्ठा media_पूर्णांकerface *पूर्णांकf,
				    u32 flags);
/**
 * __media_हटाओ_पूर्णांकf_link() - हटाओ a single पूर्णांकerface link
 *
 * @link:	poपूर्णांकer to &media_link.
 *
 * .. note:: This is an unlocked version of media_हटाओ_पूर्णांकf_link()
 */
व्योम __media_हटाओ_पूर्णांकf_link(काष्ठा media_link *link);

/**
 * media_हटाओ_पूर्णांकf_link() - हटाओ a single पूर्णांकerface link
 *
 * @link:	poपूर्णांकer to &media_link.
 *
 * .. note:: Prefer to use this one, instead of __media_हटाओ_पूर्णांकf_link()
 */
व्योम media_हटाओ_पूर्णांकf_link(काष्ठा media_link *link);

/**
 * __media_हटाओ_पूर्णांकf_links() - हटाओ all links associated with an पूर्णांकerface
 *
 * @पूर्णांकf:	poपूर्णांकer to &media_पूर्णांकerface
 *
 * .. note:: This is an unlocked version of media_हटाओ_पूर्णांकf_links().
 */
व्योम __media_हटाओ_पूर्णांकf_links(काष्ठा media_पूर्णांकerface *पूर्णांकf);

/**
 * media_हटाओ_पूर्णांकf_links() - हटाओ all links associated with an पूर्णांकerface
 *
 * @पूर्णांकf:	poपूर्णांकer to &media_पूर्णांकerface
 *
 * .. note::
 *
 *   #) This is called स्वतःmatically when an entity is unरेजिस्टरed via
 *      media_device_रेजिस्टर_entity() and by media_devnode_हटाओ().
 *
 *   #) Prefer to use this one, instead of __media_हटाओ_पूर्णांकf_links().
 */
व्योम media_हटाओ_पूर्णांकf_links(काष्ठा media_पूर्णांकerface *पूर्णांकf);

/**
 * media_entity_call - Calls a काष्ठा media_entity_operations operation on
 *	an entity
 *
 * @entity: entity where the @operation will be called
 * @operation: type of the operation. Should be the name of a member of
 *	काष्ठा &media_entity_operations.
 *
 * This helper function will check अगर @operation is not %शून्य. On such हाल,
 * it will issue a call to @operation\(@entity, @args\).
 */

#घोषणा media_entity_call(entity, operation, args...)			\
	(((entity)->ops && (entity)->ops->operation) ?			\
	 (entity)->ops->operation((entity) , ##args) : -ENOIOCTLCMD)

#पूर्ण_अगर
