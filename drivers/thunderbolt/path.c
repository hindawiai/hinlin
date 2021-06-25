<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Thunderbolt driver - path/tunnel functionality
 *
 * Copyright (c) 2014 Andreas Noever <andreas.noever@gmail.com>
 * Copyright (C) 2019, Intel Corporation
 */

#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/delay.h>
#समावेश <linux/kसमय.स>

#समावेश "tb.h"

अटल व्योम tb_dump_hop(स्थिर काष्ठा tb_path_hop *hop, स्थिर काष्ठा tb_regs_hop *regs)
अणु
	स्थिर काष्ठा tb_port *port = hop->in_port;

	tb_port_dbg(port, " In HopID: %d => Out port: %d Out HopID: %d\n",
		    hop->in_hop_index, regs->out_port, regs->next_hop);
	tb_port_dbg(port, "  Weight: %d Priority: %d Credits: %d Drop: %d\n",
		    regs->weight, regs->priority,
		    regs->initial_credits, regs->drop_packages);
	tb_port_dbg(port, "   Counter enabled: %d Counter index: %d\n",
		    regs->counter_enable, regs->counter);
	tb_port_dbg(port, "  Flow Control (In/Eg): %d/%d Shared Buffer (In/Eg): %d/%d\n",
		    regs->ingress_fc, regs->egress_fc,
		    regs->ingress_shared_buffer, regs->egress_shared_buffer);
	tb_port_dbg(port, "  Unknown1: %#x Unknown2: %#x Unknown3: %#x\n",
		    regs->unknown1, regs->unknown2, regs->unknown3);
पूर्ण

अटल काष्ठा tb_port *tb_path_find_dst_port(काष्ठा tb_port *src, पूर्णांक src_hopid,
					     पूर्णांक dst_hopid)
अणु
	काष्ठा tb_port *port, *out_port = शून्य;
	काष्ठा tb_regs_hop hop;
	काष्ठा tb_चयन *sw;
	पूर्णांक i, ret, hopid;

	hopid = src_hopid;
	port = src;

	क्रम (i = 0; port && i < TB_PATH_MAX_HOPS; i++) अणु
		sw = port->sw;

		ret = tb_port_पढ़ो(port, &hop, TB_CFG_HOPS, 2 * hopid, 2);
		अगर (ret) अणु
			tb_port_warn(port, "failed to read path at %d\n", hopid);
			वापस शून्य;
		पूर्ण

		अगर (!hop.enable)
			वापस शून्य;

		out_port = &sw->ports[hop.out_port];
		hopid = hop.next_hop;
		port = out_port->remote;
	पूर्ण

	वापस out_port && hopid == dst_hopid ? out_port : शून्य;
पूर्ण

अटल पूर्णांक tb_path_find_src_hopid(काष्ठा tb_port *src,
	स्थिर काष्ठा tb_port *dst, पूर्णांक dst_hopid)
अणु
	काष्ठा tb_port *out;
	पूर्णांक i;

	क्रम (i = TB_PATH_MIN_HOPID; i <= src->config.max_in_hop_id; i++) अणु
		out = tb_path_find_dst_port(src, i, dst_hopid);
		अगर (out == dst)
			वापस i;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * tb_path_discover() - Discover a path
 * @src: First input port of a path
 * @src_hopid: Starting HopID of a path (%-1 अगर करोn't care)
 * @dst: Expected destination port of the path (%शून्य अगर करोn't care)
 * @dst_hopid: HopID to the @dst (%-1 अगर करोn't care)
 * @last: Last port is filled here अगर not %शून्य
 * @name: Name of the path
 *
 * Follows a path starting from @src and @src_hopid to the last output
 * port of the path. Allocates HopIDs क्रम the visited ports. Call
 * tb_path_मुक्त() to release the path and allocated HopIDs when the path
 * is not needed anymore.
 *
 * Note function discovers also incomplete paths so caller should check
 * that the @dst port is the expected one. If it is not, the path can be
 * cleaned up by calling tb_path_deactivate() beक्रमe tb_path_मुक्त().
 *
 * Return: Discovered path on success, %शून्य in हाल of failure
 */
काष्ठा tb_path *tb_path_discover(काष्ठा tb_port *src, पूर्णांक src_hopid,
				 काष्ठा tb_port *dst, पूर्णांक dst_hopid,
				 काष्ठा tb_port **last, स्थिर अक्षर *name)
अणु
	काष्ठा tb_port *out_port;
	काष्ठा tb_regs_hop hop;
	काष्ठा tb_path *path;
	काष्ठा tb_चयन *sw;
	काष्ठा tb_port *p;
	माप_प्रकार num_hops;
	पूर्णांक ret, i, h;

	अगर (src_hopid < 0 && dst) अणु
		/*
		 * For incomplete paths the पूर्णांकermediate HopID can be
		 * dअगरferent from the one used by the protocol adapter
		 * so in that हाल find a path that ends on @dst with
		 * matching @dst_hopid. That should give us the correct
		 * HopID क्रम the @src.
		 */
		src_hopid = tb_path_find_src_hopid(src, dst, dst_hopid);
		अगर (!src_hopid)
			वापस शून्य;
	पूर्ण

	p = src;
	h = src_hopid;
	num_hops = 0;

	क्रम (i = 0; p && i < TB_PATH_MAX_HOPS; i++) अणु
		sw = p->sw;

		ret = tb_port_पढ़ो(p, &hop, TB_CFG_HOPS, 2 * h, 2);
		अगर (ret) अणु
			tb_port_warn(p, "failed to read path at %d\n", h);
			वापस शून्य;
		पूर्ण

		/* If the hop is not enabled we got an incomplete path */
		अगर (!hop.enable)
			अवरोध;

		out_port = &sw->ports[hop.out_port];
		अगर (last)
			*last = out_port;

		h = hop.next_hop;
		p = out_port->remote;
		num_hops++;
	पूर्ण

	path = kzalloc(माप(*path), GFP_KERNEL);
	अगर (!path)
		वापस शून्य;

	path->name = name;
	path->tb = src->sw->tb;
	path->path_length = num_hops;
	path->activated = true;

	path->hops = kसुस्मृति(num_hops, माप(*path->hops), GFP_KERNEL);
	अगर (!path->hops) अणु
		kमुक्त(path);
		वापस शून्य;
	पूर्ण

	p = src;
	h = src_hopid;

	क्रम (i = 0; i < num_hops; i++) अणु
		पूर्णांक next_hop;

		sw = p->sw;

		ret = tb_port_पढ़ो(p, &hop, TB_CFG_HOPS, 2 * h, 2);
		अगर (ret) अणु
			tb_port_warn(p, "failed to read path at %d\n", h);
			जाओ err;
		पूर्ण

		अगर (tb_port_alloc_in_hopid(p, h, h) < 0)
			जाओ err;

		out_port = &sw->ports[hop.out_port];
		next_hop = hop.next_hop;

		अगर (tb_port_alloc_out_hopid(out_port, next_hop, next_hop) < 0) अणु
			tb_port_release_in_hopid(p, h);
			जाओ err;
		पूर्ण

		path->hops[i].in_port = p;
		path->hops[i].in_hop_index = h;
		path->hops[i].in_counter_index = -1;
		path->hops[i].out_port = out_port;
		path->hops[i].next_hop_index = next_hop;

		h = next_hop;
		p = out_port->remote;
	पूर्ण

	वापस path;

err:
	tb_port_warn(src, "failed to discover path starting at HopID %d\n",
		     src_hopid);
	tb_path_मुक्त(path);
	वापस शून्य;
पूर्ण

/**
 * tb_path_alloc() - allocate a thunderbolt path between two ports
 * @tb: Doमुख्य poपूर्णांकer
 * @src: Source port of the path
 * @src_hopid: HopID used क्रम the first ingress port in the path
 * @dst: Destination port of the path
 * @dst_hopid: HopID used क्रम the last egress port in the path
 * @link_nr: Preferred link अगर there are dual links on the path
 * @name: Name of the path
 *
 * Creates path between two ports starting with given @src_hopid. Reserves
 * HopIDs क्रम each port (they can be dअगरferent from @src_hopid depending on
 * how many HopIDs each port alपढ़ोy have reserved). If there are dual
 * links on the path, prioritizes using @link_nr but takes पूर्णांकo account
 * that the lanes may be bonded.
 *
 * Return: Returns a tb_path on success or शून्य on failure.
 */
काष्ठा tb_path *tb_path_alloc(काष्ठा tb *tb, काष्ठा tb_port *src, पूर्णांक src_hopid,
			      काष्ठा tb_port *dst, पूर्णांक dst_hopid, पूर्णांक link_nr,
			      स्थिर अक्षर *name)
अणु
	काष्ठा tb_port *in_port, *out_port, *first_port, *last_port;
	पूर्णांक in_hopid, out_hopid;
	काष्ठा tb_path *path;
	माप_प्रकार num_hops;
	पूर्णांक i, ret;

	path = kzalloc(माप(*path), GFP_KERNEL);
	अगर (!path)
		वापस शून्य;

	first_port = last_port = शून्य;
	i = 0;
	tb_क्रम_each_port_on_path(src, dst, in_port) अणु
		अगर (!first_port)
			first_port = in_port;
		last_port = in_port;
		i++;
	पूर्ण

	/* Check that src and dst are reachable */
	अगर (first_port != src || last_port != dst) अणु
		kमुक्त(path);
		वापस शून्य;
	पूर्ण

	/* Each hop takes two ports */
	num_hops = i / 2;

	path->hops = kसुस्मृति(num_hops, माप(*path->hops), GFP_KERNEL);
	अगर (!path->hops) अणु
		kमुक्त(path);
		वापस शून्य;
	पूर्ण

	in_hopid = src_hopid;
	out_port = शून्य;

	क्रम (i = 0; i < num_hops; i++) अणु
		in_port = tb_next_port_on_path(src, dst, out_port);
		अगर (!in_port)
			जाओ err;

		/* When lanes are bonded primary link must be used */
		अगर (!in_port->bonded && in_port->dual_link_port &&
		    in_port->link_nr != link_nr)
			in_port = in_port->dual_link_port;

		ret = tb_port_alloc_in_hopid(in_port, in_hopid, in_hopid);
		अगर (ret < 0)
			जाओ err;
		in_hopid = ret;

		out_port = tb_next_port_on_path(src, dst, in_port);
		अगर (!out_port)
			जाओ err;

		/*
		 * Pick up right port when going from non-bonded to
		 * bonded or from bonded to non-bonded.
		 */
		अगर (out_port->dual_link_port) अणु
			अगर (!in_port->bonded && out_port->bonded &&
			    out_port->link_nr) अणु
				/*
				 * Use primary link when going from
				 * non-bonded to bonded.
				 */
				out_port = out_port->dual_link_port;
			पूर्ण अन्यथा अगर (!out_port->bonded &&
				   out_port->link_nr != link_nr) अणु
				/*
				 * If out port is not bonded follow
				 * link_nr.
				 */
				out_port = out_port->dual_link_port;
			पूर्ण
		पूर्ण

		अगर (i == num_hops - 1)
			ret = tb_port_alloc_out_hopid(out_port, dst_hopid,
						      dst_hopid);
		अन्यथा
			ret = tb_port_alloc_out_hopid(out_port, -1, -1);

		अगर (ret < 0)
			जाओ err;
		out_hopid = ret;

		path->hops[i].in_hop_index = in_hopid;
		path->hops[i].in_port = in_port;
		path->hops[i].in_counter_index = -1;
		path->hops[i].out_port = out_port;
		path->hops[i].next_hop_index = out_hopid;

		in_hopid = out_hopid;
	पूर्ण

	path->tb = tb;
	path->path_length = num_hops;
	path->name = name;

	वापस path;

err:
	tb_path_मुक्त(path);
	वापस शून्य;
पूर्ण

/**
 * tb_path_मुक्त() - मुक्त a path
 * @path: Path to मुक्त
 *
 * Frees a path. The path करोes not need to be deactivated.
 */
व्योम tb_path_मुक्त(काष्ठा tb_path *path)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < path->path_length; i++) अणु
		स्थिर काष्ठा tb_path_hop *hop = &path->hops[i];

		अगर (hop->in_port)
			tb_port_release_in_hopid(hop->in_port,
						 hop->in_hop_index);
		अगर (hop->out_port)
			tb_port_release_out_hopid(hop->out_port,
						  hop->next_hop_index);
	पूर्ण

	kमुक्त(path->hops);
	kमुक्त(path);
पूर्ण

अटल व्योम __tb_path_deallocate_nfc(काष्ठा tb_path *path, पूर्णांक first_hop)
अणु
	पूर्णांक i, res;
	क्रम (i = first_hop; i < path->path_length; i++) अणु
		res = tb_port_add_nfc_credits(path->hops[i].in_port,
					      -path->nfc_credits);
		अगर (res)
			tb_port_warn(path->hops[i].in_port,
				     "nfc credits deallocation failed for hop %d\n",
				     i);
	पूर्ण
पूर्ण

अटल पूर्णांक __tb_path_deactivate_hop(काष्ठा tb_port *port, पूर्णांक hop_index,
				    bool clear_fc)
अणु
	काष्ठा tb_regs_hop hop;
	kसमय_प्रकार समयout;
	पूर्णांक ret;

	/* Disable the path */
	ret = tb_port_पढ़ो(port, &hop, TB_CFG_HOPS, 2 * hop_index, 2);
	अगर (ret)
		वापस ret;

	/* Alपढ़ोy disabled */
	अगर (!hop.enable)
		वापस 0;

	hop.enable = 0;

	ret = tb_port_ग_लिखो(port, &hop, TB_CFG_HOPS, 2 * hop_index, 2);
	अगर (ret)
		वापस ret;

	/* Wait until it is drained */
	समयout = kसमय_add_ms(kसमय_get(), 500);
	करो अणु
		ret = tb_port_पढ़ो(port, &hop, TB_CFG_HOPS, 2 * hop_index, 2);
		अगर (ret)
			वापस ret;

		अगर (!hop.pending) अणु
			अगर (clear_fc) अणु
				/*
				 * Clear flow control. Protocol adapters
				 * IFC and ISE bits are venकरोr defined
				 * in the USB4 spec so we clear them
				 * only क्रम pre-USB4 adapters.
				 */
				अगर (!tb_चयन_is_usb4(port->sw)) अणु
					hop.ingress_fc = 0;
					hop.ingress_shared_buffer = 0;
				पूर्ण
				hop.egress_fc = 0;
				hop.egress_shared_buffer = 0;

				वापस tb_port_ग_लिखो(port, &hop, TB_CFG_HOPS,
						     2 * hop_index, 2);
			पूर्ण

			वापस 0;
		पूर्ण

		usleep_range(10, 20);
	पूर्ण जबतक (kसमय_beक्रमe(kसमय_get(), समयout));

	वापस -ETIMEDOUT;
पूर्ण

अटल व्योम __tb_path_deactivate_hops(काष्ठा tb_path *path, पूर्णांक first_hop)
अणु
	पूर्णांक i, res;

	क्रम (i = first_hop; i < path->path_length; i++) अणु
		res = __tb_path_deactivate_hop(path->hops[i].in_port,
					       path->hops[i].in_hop_index,
					       path->clear_fc);
		अगर (res && res != -ENODEV)
			tb_port_warn(path->hops[i].in_port,
				     "hop deactivation failed for hop %d, index %d\n",
				     i, path->hops[i].in_hop_index);
	पूर्ण
पूर्ण

व्योम tb_path_deactivate(काष्ठा tb_path *path)
अणु
	अगर (!path->activated) अणु
		tb_WARN(path->tb, "trying to deactivate an inactive path\n");
		वापस;
	पूर्ण
	tb_dbg(path->tb,
	       "deactivating %s path from %llx:%u to %llx:%u\n",
	       path->name, tb_route(path->hops[0].in_port->sw),
	       path->hops[0].in_port->port,
	       tb_route(path->hops[path->path_length - 1].out_port->sw),
	       path->hops[path->path_length - 1].out_port->port);
	__tb_path_deactivate_hops(path, 0);
	__tb_path_deallocate_nfc(path, 0);
	path->activated = false;
पूर्ण

/**
 * tb_path_activate() - activate a path
 * @path: Path to activate
 *
 * Activate a path starting with the last hop and iterating backwards. The
 * caller must fill path->hops beक्रमe calling tb_path_activate().
 *
 * Return: Returns 0 on success or an error code on failure.
 */
पूर्णांक tb_path_activate(काष्ठा tb_path *path)
अणु
	पूर्णांक i, res;
	क्रमागत tb_path_port out_mask, in_mask;
	अगर (path->activated) अणु
		tb_WARN(path->tb, "trying to activate already activated path\n");
		वापस -EINVAL;
	पूर्ण

	tb_dbg(path->tb,
	       "activating %s path from %llx:%u to %llx:%u\n",
	       path->name, tb_route(path->hops[0].in_port->sw),
	       path->hops[0].in_port->port,
	       tb_route(path->hops[path->path_length - 1].out_port->sw),
	       path->hops[path->path_length - 1].out_port->port);

	/* Clear counters. */
	क्रम (i = path->path_length - 1; i >= 0; i--) अणु
		अगर (path->hops[i].in_counter_index == -1)
			जारी;
		res = tb_port_clear_counter(path->hops[i].in_port,
					    path->hops[i].in_counter_index);
		अगर (res)
			जाओ err;
	पूर्ण

	/* Add non flow controlled credits. */
	क्रम (i = path->path_length - 1; i >= 0; i--) अणु
		res = tb_port_add_nfc_credits(path->hops[i].in_port,
					      path->nfc_credits);
		अगर (res) अणु
			__tb_path_deallocate_nfc(path, i);
			जाओ err;
		पूर्ण
	पूर्ण

	/* Activate hops. */
	क्रम (i = path->path_length - 1; i >= 0; i--) अणु
		काष्ठा tb_regs_hop hop = अणु 0 पूर्ण;

		/* If it is left active deactivate it first */
		__tb_path_deactivate_hop(path->hops[i].in_port,
				path->hops[i].in_hop_index, path->clear_fc);

		/* dword 0 */
		hop.next_hop = path->hops[i].next_hop_index;
		hop.out_port = path->hops[i].out_port->port;
		hop.initial_credits = path->hops[i].initial_credits;
		hop.unknown1 = 0;
		hop.enable = 1;

		/* dword 1 */
		out_mask = (i == path->path_length - 1) ?
				TB_PATH_DESTINATION : TB_PATH_INTERNAL;
		in_mask = (i == 0) ? TB_PATH_SOURCE : TB_PATH_INTERNAL;
		hop.weight = path->weight;
		hop.unknown2 = 0;
		hop.priority = path->priority;
		hop.drop_packages = path->drop_packages;
		hop.counter = path->hops[i].in_counter_index;
		hop.counter_enable = path->hops[i].in_counter_index != -1;
		hop.ingress_fc = path->ingress_fc_enable & in_mask;
		hop.egress_fc = path->egress_fc_enable & out_mask;
		hop.ingress_shared_buffer = path->ingress_shared_buffer
					    & in_mask;
		hop.egress_shared_buffer = path->egress_shared_buffer
					    & out_mask;
		hop.unknown3 = 0;

		tb_port_dbg(path->hops[i].in_port, "Writing hop %d\n", i);
		tb_dump_hop(&path->hops[i], &hop);
		res = tb_port_ग_लिखो(path->hops[i].in_port, &hop, TB_CFG_HOPS,
				    2 * path->hops[i].in_hop_index, 2);
		अगर (res) अणु
			__tb_path_deactivate_hops(path, i);
			__tb_path_deallocate_nfc(path, 0);
			जाओ err;
		पूर्ण
	पूर्ण
	path->activated = true;
	tb_dbg(path->tb, "path activation complete\n");
	वापस 0;
err:
	tb_WARN(path->tb, "path activation failed\n");
	वापस res;
पूर्ण

/**
 * tb_path_is_invalid() - check whether any ports on the path are invalid
 * @path: Path to check
 *
 * Return: Returns true अगर the path is invalid, false otherwise.
 */
bool tb_path_is_invalid(काष्ठा tb_path *path)
अणु
	पूर्णांक i = 0;
	क्रम (i = 0; i < path->path_length; i++) अणु
		अगर (path->hops[i].in_port->sw->is_unplugged)
			वापस true;
		अगर (path->hops[i].out_port->sw->is_unplugged)
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * tb_path_port_on_path() - Does the path go through certain port
 * @path: Path to check
 * @port: Switch to check
 *
 * Goes over all hops on path and checks अगर @port is any of them.
 * Direction करोes not matter.
 */
bool tb_path_port_on_path(स्थिर काष्ठा tb_path *path, स्थिर काष्ठा tb_port *port)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < path->path_length; i++) अणु
		अगर (path->hops[i].in_port == port ||
		    path->hops[i].out_port == port)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
