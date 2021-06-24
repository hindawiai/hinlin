<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Media entity
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * Contacts: Laurent Pinअक्षरt <laurent.pinअक्षरt@ideasonboard.com>
 *	     Sakari Ailus <sakari.ailus@iki.fi>
 */

#समावेश <linux/biपंचांगap.h>
#समावेश <linux/property.h>
#समावेश <linux/slab.h>
#समावेश <media/media-entity.h>
#समावेश <media/media-device.h>

अटल अंतरभूत स्थिर अक्षर *gobj_type(क्रमागत media_gobj_type type)
अणु
	चयन (type) अणु
	हाल MEDIA_GRAPH_ENTITY:
		वापस "entity";
	हाल MEDIA_GRAPH_PAD:
		वापस "pad";
	हाल MEDIA_GRAPH_LINK:
		वापस "link";
	हाल MEDIA_GRAPH_INTF_DEVNODE:
		वापस "intf-devnode";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल अंतरभूत स्थिर अक्षर *पूर्णांकf_type(काष्ठा media_पूर्णांकerface *पूर्णांकf)
अणु
	चयन (पूर्णांकf->type) अणु
	हाल MEDIA_INTF_T_DVB_FE:
		वापस "dvb-frontend";
	हाल MEDIA_INTF_T_DVB_DEMUX:
		वापस "dvb-demux";
	हाल MEDIA_INTF_T_DVB_DVR:
		वापस "dvb-dvr";
	हाल MEDIA_INTF_T_DVB_CA:
		वापस  "dvb-ca";
	हाल MEDIA_INTF_T_DVB_NET:
		वापस "dvb-net";
	हाल MEDIA_INTF_T_V4L_VIDEO:
		वापस "v4l-video";
	हाल MEDIA_INTF_T_V4L_VBI:
		वापस "v4l-vbi";
	हाल MEDIA_INTF_T_V4L_RADIO:
		वापस "v4l-radio";
	हाल MEDIA_INTF_T_V4L_SUBDEV:
		वापस "v4l-subdev";
	हाल MEDIA_INTF_T_V4L_SWRADIO:
		वापस "v4l-swradio";
	हाल MEDIA_INTF_T_V4L_TOUCH:
		वापस "v4l-touch";
	शेष:
		वापस "unknown-intf";
	पूर्ण
पूर्ण;

__must_check पूर्णांक __media_entity_क्रमागत_init(काष्ठा media_entity_क्रमागत *ent_क्रमागत,
					  पूर्णांक idx_max)
अणु
	idx_max = ALIGN(idx_max, BITS_PER_LONG);
	ent_क्रमागत->bmap = kसुस्मृति(idx_max / BITS_PER_LONG, माप(दीर्घ),
				 GFP_KERNEL);
	अगर (!ent_क्रमागत->bmap)
		वापस -ENOMEM;

	biपंचांगap_zero(ent_क्रमागत->bmap, idx_max);
	ent_क्रमागत->idx_max = idx_max;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__media_entity_क्रमागत_init);

व्योम media_entity_क्रमागत_cleanup(काष्ठा media_entity_क्रमागत *ent_क्रमागत)
अणु
	kमुक्त(ent_क्रमागत->bmap);
पूर्ण
EXPORT_SYMBOL_GPL(media_entity_क्रमागत_cleanup);

/**
 *  dev_dbg_obj - Prपूर्णांकs in debug mode a change on some object
 *
 * @event_name:	Name of the event to report. Could be __func__
 * @gobj:	Poपूर्णांकer to the object
 *
 * Enabled only अगर DEBUG or CONFIG_DYNAMIC_DEBUG. Otherwise, it
 * won't produce any code.
 */
अटल व्योम dev_dbg_obj(स्थिर अक्षर *event_name,  काष्ठा media_gobj *gobj)
अणु
#अगर defined(DEBUG) || defined (CONFIG_DYNAMIC_DEBUG)
	चयन (media_type(gobj)) अणु
	हाल MEDIA_GRAPH_ENTITY:
		dev_dbg(gobj->mdev->dev,
			"%s id %u: entity '%s'\n",
			event_name, media_id(gobj),
			gobj_to_entity(gobj)->name);
		अवरोध;
	हाल MEDIA_GRAPH_LINK:
	अणु
		काष्ठा media_link *link = gobj_to_link(gobj);

		dev_dbg(gobj->mdev->dev,
			"%s id %u: %s link id %u ==> id %u\n",
			event_name, media_id(gobj),
			media_type(link->gobj0) == MEDIA_GRAPH_PAD ?
				"data" : "interface",
			media_id(link->gobj0),
			media_id(link->gobj1));
		अवरोध;
	पूर्ण
	हाल MEDIA_GRAPH_PAD:
	अणु
		काष्ठा media_pad *pad = gobj_to_pad(gobj);

		dev_dbg(gobj->mdev->dev,
			"%s id %u: %s%spad '%s':%d\n",
			event_name, media_id(gobj),
			pad->flags & MEDIA_PAD_FL_SINK   ? "sink " : "",
			pad->flags & MEDIA_PAD_FL_SOURCE ? "source " : "",
			pad->entity->name, pad->index);
		अवरोध;
	पूर्ण
	हाल MEDIA_GRAPH_INTF_DEVNODE:
	अणु
		काष्ठा media_पूर्णांकerface *पूर्णांकf = gobj_to_पूर्णांकf(gobj);
		काष्ठा media_पूर्णांकf_devnode *devnode = पूर्णांकf_to_devnode(पूर्णांकf);

		dev_dbg(gobj->mdev->dev,
			"%s id %u: intf_devnode %s - major: %d, minor: %d\n",
			event_name, media_id(gobj),
			पूर्णांकf_type(पूर्णांकf),
			devnode->major, devnode->minor);
		अवरोध;
	पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

व्योम media_gobj_create(काष्ठा media_device *mdev,
			   क्रमागत media_gobj_type type,
			   काष्ठा media_gobj *gobj)
अणु
	BUG_ON(!mdev);

	gobj->mdev = mdev;

	/* Create a per-type unique object ID */
	gobj->id = media_gobj_gen_id(type, ++mdev->id);

	चयन (type) अणु
	हाल MEDIA_GRAPH_ENTITY:
		list_add_tail(&gobj->list, &mdev->entities);
		अवरोध;
	हाल MEDIA_GRAPH_PAD:
		list_add_tail(&gobj->list, &mdev->pads);
		अवरोध;
	हाल MEDIA_GRAPH_LINK:
		list_add_tail(&gobj->list, &mdev->links);
		अवरोध;
	हाल MEDIA_GRAPH_INTF_DEVNODE:
		list_add_tail(&gobj->list, &mdev->पूर्णांकerfaces);
		अवरोध;
	पूर्ण

	mdev->topology_version++;

	dev_dbg_obj(__func__, gobj);
पूर्ण

व्योम media_gobj_destroy(काष्ठा media_gobj *gobj)
अणु
	/* Do nothing अगर the object is not linked. */
	अगर (gobj->mdev == शून्य)
		वापस;

	dev_dbg_obj(__func__, gobj);

	gobj->mdev->topology_version++;

	/* Remove the object from mdev list */
	list_del(&gobj->list);

	gobj->mdev = शून्य;
पूर्ण

/*
 * TODO: Get rid of this.
 */
#घोषणा MEDIA_ENTITY_MAX_PADS		512

पूर्णांक media_entity_pads_init(काष्ठा media_entity *entity, u16 num_pads,
			   काष्ठा media_pad *pads)
अणु
	काष्ठा media_device *mdev = entity->graph_obj.mdev;
	अचिन्हित पूर्णांक i;

	अगर (num_pads >= MEDIA_ENTITY_MAX_PADS)
		वापस -E2BIG;

	entity->num_pads = num_pads;
	entity->pads = pads;

	अगर (mdev)
		mutex_lock(&mdev->graph_mutex);

	क्रम (i = 0; i < num_pads; i++) अणु
		pads[i].entity = entity;
		pads[i].index = i;
		अगर (mdev)
			media_gobj_create(mdev, MEDIA_GRAPH_PAD,
					&entity->pads[i].graph_obj);
	पूर्ण

	अगर (mdev)
		mutex_unlock(&mdev->graph_mutex);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(media_entity_pads_init);

/* -----------------------------------------------------------------------------
 * Graph traversal
 */

अटल काष्ठा media_entity *
media_entity_other(काष्ठा media_entity *entity, काष्ठा media_link *link)
अणु
	अगर (link->source->entity == entity)
		वापस link->sink->entity;
	अन्यथा
		वापस link->source->entity;
पूर्ण

/* push an entity to traversal stack */
अटल व्योम stack_push(काष्ठा media_graph *graph,
		       काष्ठा media_entity *entity)
अणु
	अगर (graph->top == MEDIA_ENTITY_ENUM_MAX_DEPTH - 1) अणु
		WARN_ON(1);
		वापस;
	पूर्ण
	graph->top++;
	graph->stack[graph->top].link = entity->links.next;
	graph->stack[graph->top].entity = entity;
पूर्ण

अटल काष्ठा media_entity *stack_pop(काष्ठा media_graph *graph)
अणु
	काष्ठा media_entity *entity;

	entity = graph->stack[graph->top].entity;
	graph->top--;

	वापस entity;
पूर्ण

#घोषणा link_top(en)	((en)->stack[(en)->top].link)
#घोषणा stack_top(en)	((en)->stack[(en)->top].entity)

/**
 * media_graph_walk_init - Allocate resources क्रम graph walk
 * @graph: Media graph काष्ठाure that will be used to walk the graph
 * @mdev: Media device
 *
 * Reserve resources क्रम graph walk in media device's current
 * state. The memory must be released using
 * media_graph_walk_मुक्त().
 *
 * Returns error on failure, zero on success.
 */
__must_check पूर्णांक media_graph_walk_init(
	काष्ठा media_graph *graph, काष्ठा media_device *mdev)
अणु
	वापस media_entity_क्रमागत_init(&graph->ent_क्रमागत, mdev);
पूर्ण
EXPORT_SYMBOL_GPL(media_graph_walk_init);

/**
 * media_graph_walk_cleanup - Release resources related to graph walking
 * @graph: Media graph काष्ठाure that was used to walk the graph
 */
व्योम media_graph_walk_cleanup(काष्ठा media_graph *graph)
अणु
	media_entity_क्रमागत_cleanup(&graph->ent_क्रमागत);
पूर्ण
EXPORT_SYMBOL_GPL(media_graph_walk_cleanup);

व्योम media_graph_walk_start(काष्ठा media_graph *graph,
			    काष्ठा media_entity *entity)
अणु
	media_entity_क्रमागत_zero(&graph->ent_क्रमागत);
	media_entity_क्रमागत_set(&graph->ent_क्रमागत, entity);

	graph->top = 0;
	graph->stack[graph->top].entity = शून्य;
	stack_push(graph, entity);
	dev_dbg(entity->graph_obj.mdev->dev,
		"begin graph walk at '%s'\n", entity->name);
पूर्ण
EXPORT_SYMBOL_GPL(media_graph_walk_start);

अटल व्योम media_graph_walk_iter(काष्ठा media_graph *graph)
अणु
	काष्ठा media_entity *entity = stack_top(graph);
	काष्ठा media_link *link;
	काष्ठा media_entity *next;

	link = list_entry(link_top(graph), typeof(*link), list);

	/* The link is not enabled so we करो not follow. */
	अगर (!(link->flags & MEDIA_LNK_FL_ENABLED)) अणु
		link_top(graph) = link_top(graph)->next;
		dev_dbg(entity->graph_obj.mdev->dev,
			"walk: skipping disabled link '%s':%u -> '%s':%u\n",
			link->source->entity->name, link->source->index,
			link->sink->entity->name, link->sink->index);
		वापस;
	पूर्ण

	/* Get the entity in the other end of the link . */
	next = media_entity_other(entity, link);

	/* Has the entity alपढ़ोy been visited? */
	अगर (media_entity_क्रमागत_test_and_set(&graph->ent_क्रमागत, next)) अणु
		link_top(graph) = link_top(graph)->next;
		dev_dbg(entity->graph_obj.mdev->dev,
			"walk: skipping entity '%s' (already seen)\n",
			next->name);
		वापस;
	पूर्ण

	/* Push the new entity to stack and start over. */
	link_top(graph) = link_top(graph)->next;
	stack_push(graph, next);
	dev_dbg(entity->graph_obj.mdev->dev, "walk: pushing '%s' on stack\n",
		next->name);
	lockdep_निश्चित_held(&entity->graph_obj.mdev->graph_mutex);
पूर्ण

काष्ठा media_entity *media_graph_walk_next(काष्ठा media_graph *graph)
अणु
	काष्ठा media_entity *entity;

	अगर (stack_top(graph) == शून्य)
		वापस शून्य;

	/*
	 * Depth first search. Push entity to stack and जारी from
	 * top of the stack until no more entities on the level can be
	 * found.
	 */
	जबतक (link_top(graph) != &stack_top(graph)->links)
		media_graph_walk_iter(graph);

	entity = stack_pop(graph);
	dev_dbg(entity->graph_obj.mdev->dev,
		"walk: returning entity '%s'\n", entity->name);

	वापस entity;
पूर्ण
EXPORT_SYMBOL_GPL(media_graph_walk_next);

पूर्णांक media_entity_get_fwnode_pad(काष्ठा media_entity *entity,
				काष्ठा fwnode_handle *fwnode,
				अचिन्हित दीर्घ direction_flags)
अणु
	काष्ठा fwnode_endpoपूर्णांक endpoपूर्णांक;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!entity->ops || !entity->ops->get_fwnode_pad) अणु
		क्रम (i = 0; i < entity->num_pads; i++) अणु
			अगर (entity->pads[i].flags & direction_flags)
				वापस i;
		पूर्ण

		वापस -ENXIO;
	पूर्ण

	ret = fwnode_graph_parse_endpoपूर्णांक(fwnode, &endpoपूर्णांक);
	अगर (ret)
		वापस ret;

	ret = entity->ops->get_fwnode_pad(entity, &endpoपूर्णांक);
	अगर (ret < 0)
		वापस ret;

	अगर (ret >= entity->num_pads)
		वापस -ENXIO;

	अगर (!(entity->pads[ret].flags & direction_flags))
		वापस -ENXIO;

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(media_entity_get_fwnode_pad);

/* -----------------------------------------------------------------------------
 * Pipeline management
 */

__must_check पूर्णांक __media_pipeline_start(काष्ठा media_entity *entity,
					काष्ठा media_pipeline *pipe)
अणु
	काष्ठा media_device *mdev = entity->graph_obj.mdev;
	काष्ठा media_graph *graph = &pipe->graph;
	काष्ठा media_entity *entity_err = entity;
	काष्ठा media_link *link;
	पूर्णांक ret;

	अगर (!pipe->streaming_count++) अणु
		ret = media_graph_walk_init(&pipe->graph, mdev);
		अगर (ret)
			जाओ error_graph_walk_start;
	पूर्ण

	media_graph_walk_start(&pipe->graph, entity);

	जबतक ((entity = media_graph_walk_next(graph))) अणु
		DECLARE_BITMAP(active, MEDIA_ENTITY_MAX_PADS);
		DECLARE_BITMAP(has_no_links, MEDIA_ENTITY_MAX_PADS);

		entity->stream_count++;

		अगर (entity->pipe && entity->pipe != pipe) अणु
			pr_err("Pipe active for %s. Can't start for %s\n",
				entity->name,
				entity_err->name);
			ret = -EBUSY;
			जाओ error;
		पूर्ण

		entity->pipe = pipe;

		/* Alपढ़ोy streaming --- no need to check. */
		अगर (entity->stream_count > 1)
			जारी;

		अगर (!entity->ops || !entity->ops->link_validate)
			जारी;

		biपंचांगap_zero(active, entity->num_pads);
		biपंचांगap_fill(has_no_links, entity->num_pads);

		list_क्रम_each_entry(link, &entity->links, list) अणु
			काष्ठा media_pad *pad = link->sink->entity == entity
						? link->sink : link->source;

			/* Mark that a pad is connected by a link. */
			biपंचांगap_clear(has_no_links, pad->index, 1);

			/*
			 * Pads that either करो not need to connect or
			 * are connected through an enabled link are
			 * fine.
			 */
			अगर (!(pad->flags & MEDIA_PAD_FL_MUST_CONNECT) ||
			    link->flags & MEDIA_LNK_FL_ENABLED)
				biपंचांगap_set(active, pad->index, 1);

			/*
			 * Link validation will only take place क्रम
			 * sink ends of the link that are enabled.
			 */
			अगर (link->sink != pad ||
			    !(link->flags & MEDIA_LNK_FL_ENABLED))
				जारी;

			ret = entity->ops->link_validate(link);
			अगर (ret < 0 && ret != -ENOIOCTLCMD) अणु
				dev_dbg(entity->graph_obj.mdev->dev,
					"link validation failed for '%s':%u -> '%s':%u, error %d\n",
					link->source->entity->name,
					link->source->index,
					entity->name, link->sink->index, ret);
				जाओ error;
			पूर्ण
		पूर्ण

		/* Either no links or validated links are fine. */
		biपंचांगap_or(active, active, has_no_links, entity->num_pads);

		अगर (!biपंचांगap_full(active, entity->num_pads)) अणु
			ret = -ENOLINK;
			dev_dbg(entity->graph_obj.mdev->dev,
				"'%s':%u must be connected by an enabled link\n",
				entity->name,
				(अचिन्हित)find_first_zero_bit(
					active, entity->num_pads));
			जाओ error;
		पूर्ण
	पूर्ण

	वापस 0;

error:
	/*
	 * Link validation on graph failed. We revert what we did and
	 * वापस the error.
	 */
	media_graph_walk_start(graph, entity_err);

	जबतक ((entity_err = media_graph_walk_next(graph))) अणु
		/* Sanity check क्रम negative stream_count */
		अगर (!WARN_ON_ONCE(entity_err->stream_count <= 0)) अणु
			entity_err->stream_count--;
			अगर (entity_err->stream_count == 0)
				entity_err->pipe = शून्य;
		पूर्ण

		/*
		 * We haven't increased stream_count further than this
		 * so we quit here.
		 */
		अगर (entity_err == entity)
			अवरोध;
	पूर्ण

error_graph_walk_start:
	अगर (!--pipe->streaming_count)
		media_graph_walk_cleanup(graph);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__media_pipeline_start);

__must_check पूर्णांक media_pipeline_start(काष्ठा media_entity *entity,
				      काष्ठा media_pipeline *pipe)
अणु
	काष्ठा media_device *mdev = entity->graph_obj.mdev;
	पूर्णांक ret;

	mutex_lock(&mdev->graph_mutex);
	ret = __media_pipeline_start(entity, pipe);
	mutex_unlock(&mdev->graph_mutex);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(media_pipeline_start);

व्योम __media_pipeline_stop(काष्ठा media_entity *entity)
अणु
	काष्ठा media_graph *graph = &entity->pipe->graph;
	काष्ठा media_pipeline *pipe = entity->pipe;

	/*
	 * If the following check fails, the driver has perक्रमmed an
	 * unbalanced call to media_pipeline_stop()
	 */
	अगर (WARN_ON(!pipe))
		वापस;

	media_graph_walk_start(graph, entity);

	जबतक ((entity = media_graph_walk_next(graph))) अणु
		/* Sanity check क्रम negative stream_count */
		अगर (!WARN_ON_ONCE(entity->stream_count <= 0)) अणु
			entity->stream_count--;
			अगर (entity->stream_count == 0)
				entity->pipe = शून्य;
		पूर्ण
	पूर्ण

	अगर (!--pipe->streaming_count)
		media_graph_walk_cleanup(graph);

पूर्ण
EXPORT_SYMBOL_GPL(__media_pipeline_stop);

व्योम media_pipeline_stop(काष्ठा media_entity *entity)
अणु
	काष्ठा media_device *mdev = entity->graph_obj.mdev;

	mutex_lock(&mdev->graph_mutex);
	__media_pipeline_stop(entity);
	mutex_unlock(&mdev->graph_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(media_pipeline_stop);

/* -----------------------------------------------------------------------------
 * Links management
 */

अटल काष्ठा media_link *media_add_link(काष्ठा list_head *head)
अणु
	काष्ठा media_link *link;

	link = kzalloc(माप(*link), GFP_KERNEL);
	अगर (link == शून्य)
		वापस शून्य;

	list_add_tail(&link->list, head);

	वापस link;
पूर्ण

अटल व्योम __media_entity_हटाओ_link(काष्ठा media_entity *entity,
				       काष्ठा media_link *link)
अणु
	काष्ठा media_link *rlink, *पंचांगp;
	काष्ठा media_entity *remote;

	अगर (link->source->entity == entity)
		remote = link->sink->entity;
	अन्यथा
		remote = link->source->entity;

	list_क्रम_each_entry_safe(rlink, पंचांगp, &remote->links, list) अणु
		अगर (rlink != link->reverse)
			जारी;

		अगर (link->source->entity == entity)
			remote->num_backlinks--;

		/* Remove the remote link */
		list_del(&rlink->list);
		media_gobj_destroy(&rlink->graph_obj);
		kमुक्त(rlink);

		अगर (--remote->num_links == 0)
			अवरोध;
	पूर्ण
	list_del(&link->list);
	media_gobj_destroy(&link->graph_obj);
	kमुक्त(link);
पूर्ण

पूर्णांक media_get_pad_index(काष्ठा media_entity *entity, bool is_sink,
			क्रमागत media_pad_संकेत_type sig_type)
अणु
	पूर्णांक i;
	bool pad_is_sink;

	अगर (!entity)
		वापस -EINVAL;

	क्रम (i = 0; i < entity->num_pads; i++) अणु
		अगर (entity->pads[i].flags & MEDIA_PAD_FL_SINK)
			pad_is_sink = true;
		अन्यथा अगर (entity->pads[i].flags & MEDIA_PAD_FL_SOURCE)
			pad_is_sink = false;
		अन्यथा
			जारी;	/* This is an error! */

		अगर (pad_is_sink != is_sink)
			जारी;
		अगर (entity->pads[i].sig_type == sig_type)
			वापस i;
	पूर्ण
	वापस -EINVAL;
पूर्ण
EXPORT_SYMBOL_GPL(media_get_pad_index);

पूर्णांक
media_create_pad_link(काष्ठा media_entity *source, u16 source_pad,
			 काष्ठा media_entity *sink, u16 sink_pad, u32 flags)
अणु
	काष्ठा media_link *link;
	काष्ठा media_link *backlink;

	अगर (WARN_ON(!source || !sink) ||
	    WARN_ON(source_pad >= source->num_pads) ||
	    WARN_ON(sink_pad >= sink->num_pads))
		वापस -EINVAL;
	अगर (WARN_ON(!(source->pads[source_pad].flags & MEDIA_PAD_FL_SOURCE)))
		वापस -EINVAL;
	अगर (WARN_ON(!(sink->pads[sink_pad].flags & MEDIA_PAD_FL_SINK)))
		वापस -EINVAL;

	link = media_add_link(&source->links);
	अगर (link == शून्य)
		वापस -ENOMEM;

	link->source = &source->pads[source_pad];
	link->sink = &sink->pads[sink_pad];
	link->flags = flags & ~MEDIA_LNK_FL_INTERFACE_LINK;

	/* Initialize graph object embedded at the new link */
	media_gobj_create(source->graph_obj.mdev, MEDIA_GRAPH_LINK,
			&link->graph_obj);

	/* Create the backlink. Backlinks are used to help graph traversal and
	 * are not reported to userspace.
	 */
	backlink = media_add_link(&sink->links);
	अगर (backlink == शून्य) अणु
		__media_entity_हटाओ_link(source, link);
		वापस -ENOMEM;
	पूर्ण

	backlink->source = &source->pads[source_pad];
	backlink->sink = &sink->pads[sink_pad];
	backlink->flags = flags;
	backlink->is_backlink = true;

	/* Initialize graph object embedded at the new link */
	media_gobj_create(sink->graph_obj.mdev, MEDIA_GRAPH_LINK,
			&backlink->graph_obj);

	link->reverse = backlink;
	backlink->reverse = link;

	sink->num_backlinks++;
	sink->num_links++;
	source->num_links++;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(media_create_pad_link);

पूर्णांक media_create_pad_links(स्थिर काष्ठा media_device *mdev,
			   स्थिर u32 source_function,
			   काष्ठा media_entity *source,
			   स्थिर u16 source_pad,
			   स्थिर u32 sink_function,
			   काष्ठा media_entity *sink,
			   स्थिर u16 sink_pad,
			   u32 flags,
			   स्थिर bool allow_both_undefined)
अणु
	काष्ठा media_entity *entity;
	अचिन्हित function;
	पूर्णांक ret;

	/* Trivial हाल: 1:1 relation */
	अगर (source && sink)
		वापस media_create_pad_link(source, source_pad,
					     sink, sink_pad, flags);

	/* Worse हाल scenario: n:n relation */
	अगर (!source && !sink) अणु
		अगर (!allow_both_undefined)
			वापस 0;
		media_device_क्रम_each_entity(source, mdev) अणु
			अगर (source->function != source_function)
				जारी;
			media_device_क्रम_each_entity(sink, mdev) अणु
				अगर (sink->function != sink_function)
					जारी;
				ret = media_create_pad_link(source, source_pad,
							    sink, sink_pad,
							    flags);
				अगर (ret)
					वापस ret;
				flags &= ~(MEDIA_LNK_FL_ENABLED |
					   MEDIA_LNK_FL_IMMUTABLE);
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण

	/* Handle 1:n and n:1 हालs */
	अगर (source)
		function = sink_function;
	अन्यथा
		function = source_function;

	media_device_क्रम_each_entity(entity, mdev) अणु
		अगर (entity->function != function)
			जारी;

		अगर (source)
			ret = media_create_pad_link(source, source_pad,
						    entity, sink_pad, flags);
		अन्यथा
			ret = media_create_pad_link(entity, source_pad,
						    sink, sink_pad, flags);
		अगर (ret)
			वापस ret;
		flags &= ~(MEDIA_LNK_FL_ENABLED | MEDIA_LNK_FL_IMMUTABLE);
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(media_create_pad_links);

व्योम __media_entity_हटाओ_links(काष्ठा media_entity *entity)
अणु
	काष्ठा media_link *link, *पंचांगp;

	list_क्रम_each_entry_safe(link, पंचांगp, &entity->links, list)
		__media_entity_हटाओ_link(entity, link);

	entity->num_links = 0;
	entity->num_backlinks = 0;
पूर्ण
EXPORT_SYMBOL_GPL(__media_entity_हटाओ_links);

व्योम media_entity_हटाओ_links(काष्ठा media_entity *entity)
अणु
	काष्ठा media_device *mdev = entity->graph_obj.mdev;

	/* Do nothing अगर the entity is not रेजिस्टरed. */
	अगर (mdev == शून्य)
		वापस;

	mutex_lock(&mdev->graph_mutex);
	__media_entity_हटाओ_links(entity);
	mutex_unlock(&mdev->graph_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(media_entity_हटाओ_links);

अटल पूर्णांक __media_entity_setup_link_notअगरy(काष्ठा media_link *link, u32 flags)
अणु
	पूर्णांक ret;

	/* Notअगरy both entities. */
	ret = media_entity_call(link->source->entity, link_setup,
				link->source, link->sink, flags);
	अगर (ret < 0 && ret != -ENOIOCTLCMD)
		वापस ret;

	ret = media_entity_call(link->sink->entity, link_setup,
				link->sink, link->source, flags);
	अगर (ret < 0 && ret != -ENOIOCTLCMD) अणु
		media_entity_call(link->source->entity, link_setup,
				  link->source, link->sink, link->flags);
		वापस ret;
	पूर्ण

	link->flags = flags;
	link->reverse->flags = link->flags;

	वापस 0;
पूर्ण

पूर्णांक __media_entity_setup_link(काष्ठा media_link *link, u32 flags)
अणु
	स्थिर u32 mask = MEDIA_LNK_FL_ENABLED;
	काष्ठा media_device *mdev;
	काष्ठा media_entity *source, *sink;
	पूर्णांक ret = -EBUSY;

	अगर (link == शून्य)
		वापस -EINVAL;

	/* The non-modअगरiable link flags must not be modअगरied. */
	अगर ((link->flags & ~mask) != (flags & ~mask))
		वापस -EINVAL;

	अगर (link->flags & MEDIA_LNK_FL_IMMUTABLE)
		वापस link->flags == flags ? 0 : -EINVAL;

	अगर (link->flags == flags)
		वापस 0;

	source = link->source->entity;
	sink = link->sink->entity;

	अगर (!(link->flags & MEDIA_LNK_FL_DYNAMIC) &&
	    (source->stream_count || sink->stream_count))
		वापस -EBUSY;

	mdev = source->graph_obj.mdev;

	अगर (mdev->ops && mdev->ops->link_notअगरy) अणु
		ret = mdev->ops->link_notअगरy(link, flags,
					     MEDIA_DEV_NOTIFY_PRE_LINK_CH);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	ret = __media_entity_setup_link_notअगरy(link, flags);

	अगर (mdev->ops && mdev->ops->link_notअगरy)
		mdev->ops->link_notअगरy(link, flags,
				       MEDIA_DEV_NOTIFY_POST_LINK_CH);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(__media_entity_setup_link);

पूर्णांक media_entity_setup_link(काष्ठा media_link *link, u32 flags)
अणु
	पूर्णांक ret;

	mutex_lock(&link->graph_obj.mdev->graph_mutex);
	ret = __media_entity_setup_link(link, flags);
	mutex_unlock(&link->graph_obj.mdev->graph_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(media_entity_setup_link);

काष्ठा media_link *
media_entity_find_link(काष्ठा media_pad *source, काष्ठा media_pad *sink)
अणु
	काष्ठा media_link *link;

	list_क्रम_each_entry(link, &source->entity->links, list) अणु
		अगर (link->source->entity == source->entity &&
		    link->source->index == source->index &&
		    link->sink->entity == sink->entity &&
		    link->sink->index == sink->index)
			वापस link;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(media_entity_find_link);

काष्ठा media_pad *media_entity_remote_pad(स्थिर काष्ठा media_pad *pad)
अणु
	काष्ठा media_link *link;

	list_क्रम_each_entry(link, &pad->entity->links, list) अणु
		अगर (!(link->flags & MEDIA_LNK_FL_ENABLED))
			जारी;

		अगर (link->source == pad)
			वापस link->sink;

		अगर (link->sink == pad)
			वापस link->source;
	पूर्ण

	वापस शून्य;

पूर्ण
EXPORT_SYMBOL_GPL(media_entity_remote_pad);

अटल व्योम media_पूर्णांकerface_init(काष्ठा media_device *mdev,
				 काष्ठा media_पूर्णांकerface *पूर्णांकf,
				 u32 gobj_type,
				 u32 पूर्णांकf_type, u32 flags)
अणु
	पूर्णांकf->type = पूर्णांकf_type;
	पूर्णांकf->flags = flags;
	INIT_LIST_HEAD(&पूर्णांकf->links);

	media_gobj_create(mdev, gobj_type, &पूर्णांकf->graph_obj);
पूर्ण

/* Functions related to the media पूर्णांकerface via device nodes */

काष्ठा media_पूर्णांकf_devnode *media_devnode_create(काष्ठा media_device *mdev,
						u32 type, u32 flags,
						u32 major, u32 minor)
अणु
	काष्ठा media_पूर्णांकf_devnode *devnode;

	devnode = kzalloc(माप(*devnode), GFP_KERNEL);
	अगर (!devnode)
		वापस शून्य;

	devnode->major = major;
	devnode->minor = minor;

	media_पूर्णांकerface_init(mdev, &devnode->पूर्णांकf, MEDIA_GRAPH_INTF_DEVNODE,
			     type, flags);

	वापस devnode;
पूर्ण
EXPORT_SYMBOL_GPL(media_devnode_create);

व्योम media_devnode_हटाओ(काष्ठा media_पूर्णांकf_devnode *devnode)
अणु
	media_हटाओ_पूर्णांकf_links(&devnode->पूर्णांकf);
	media_gobj_destroy(&devnode->पूर्णांकf.graph_obj);
	kमुक्त(devnode);
पूर्ण
EXPORT_SYMBOL_GPL(media_devnode_हटाओ);

काष्ठा media_link *media_create_पूर्णांकf_link(काष्ठा media_entity *entity,
					    काष्ठा media_पूर्णांकerface *पूर्णांकf,
					    u32 flags)
अणु
	काष्ठा media_link *link;

	link = media_add_link(&पूर्णांकf->links);
	अगर (link == शून्य)
		वापस शून्य;

	link->पूर्णांकf = पूर्णांकf;
	link->entity = entity;
	link->flags = flags | MEDIA_LNK_FL_INTERFACE_LINK;

	/* Initialize graph object embedded at the new link */
	media_gobj_create(पूर्णांकf->graph_obj.mdev, MEDIA_GRAPH_LINK,
			&link->graph_obj);

	वापस link;
पूर्ण
EXPORT_SYMBOL_GPL(media_create_पूर्णांकf_link);

व्योम __media_हटाओ_पूर्णांकf_link(काष्ठा media_link *link)
अणु
	list_del(&link->list);
	media_gobj_destroy(&link->graph_obj);
	kमुक्त(link);
पूर्ण
EXPORT_SYMBOL_GPL(__media_हटाओ_पूर्णांकf_link);

व्योम media_हटाओ_पूर्णांकf_link(काष्ठा media_link *link)
अणु
	काष्ठा media_device *mdev = link->graph_obj.mdev;

	/* Do nothing अगर the पूर्णांकf is not रेजिस्टरed. */
	अगर (mdev == शून्य)
		वापस;

	mutex_lock(&mdev->graph_mutex);
	__media_हटाओ_पूर्णांकf_link(link);
	mutex_unlock(&mdev->graph_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(media_हटाओ_पूर्णांकf_link);

व्योम __media_हटाओ_पूर्णांकf_links(काष्ठा media_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा media_link *link, *पंचांगp;

	list_क्रम_each_entry_safe(link, पंचांगp, &पूर्णांकf->links, list)
		__media_हटाओ_पूर्णांकf_link(link);

पूर्ण
EXPORT_SYMBOL_GPL(__media_हटाओ_पूर्णांकf_links);

व्योम media_हटाओ_पूर्णांकf_links(काष्ठा media_पूर्णांकerface *पूर्णांकf)
अणु
	काष्ठा media_device *mdev = पूर्णांकf->graph_obj.mdev;

	/* Do nothing अगर the पूर्णांकf is not रेजिस्टरed. */
	अगर (mdev == शून्य)
		वापस;

	mutex_lock(&mdev->graph_mutex);
	__media_हटाओ_पूर्णांकf_links(पूर्णांकf);
	mutex_unlock(&mdev->graph_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(media_हटाओ_पूर्णांकf_links);
