<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018-2019, Vladimir Oltean <olteanv@gmail.com>
 */
#समावेश "sja1105.h"

/* In the dynamic configuration पूर्णांकerface, the चयन exposes a रेजिस्टर-like
 * view of some of the अटल configuration tables.
 * Many बार the field organization of the dynamic tables is abbreviated (not
 * all fields are dynamically reconfigurable) and dअगरferent from the अटल
 * ones, but the key reason क्रम having it is that we can spare a चयन reset
 * क्रम settings that can be changed dynamically.
 *
 * This file creates a per-चयन-family असलtraction called
 * काष्ठा sja1105_dynamic_table_ops and two operations that work with it:
 * - sja1105_dynamic_config_ग_लिखो
 * - sja1105_dynamic_config_पढ़ो
 *
 * Compared to the काष्ठा sja1105_table_ops from sja1105_अटल_config.c,
 * the dynamic accessors work with a compound buffer:
 *
 * packed_buf
 *
 * |
 * V
 * +-----------------------------------------+------------------+
 * |              ENTRY BUFFER               |  COMMAND BUFFER  |
 * +-----------------------------------------+------------------+
 *
 * <----------------------- packed_size ------------------------>
 *
 * The ENTRY BUFFER may or may not have the same layout, or size, as its अटल
 * configuration table entry counterpart. When it करोes, the same packing
 * function is reused (bar exceptional हालs - see
 * sja1105pqrs_dyn_l2_lookup_entry_packing).
 *
 * The reason क्रम the COMMAND BUFFER being at the end is to be able to send
 * a dynamic ग_लिखो command through a single SPI burst. By the समय the चयन
 * reacts to the command, the ENTRY BUFFER is alपढ़ोy populated with the data
 * sent by the core.
 *
 * The COMMAND BUFFER is always SJA1105_SIZE_DYN_CMD bytes (one 32-bit word) in
 * size.
 *
 * Someबार the ENTRY BUFFER करोes not really exist (when the number of fields
 * that can be reconfigured is small), then the चयन repurposes some of the
 * unused 32 bits of the COMMAND BUFFER to hold ENTRY data.
 *
 * The key members of काष्ठा sja1105_dynamic_table_ops are:
 * - .entry_packing: A function that deals with packing an ENTRY काष्ठाure
 *		     पूर्णांकo an SPI buffer, or retrieving an ENTRY काष्ठाure
 *		     from one.
 *		     The @packed_buf poपूर्णांकer it's given करोes always poपूर्णांक to
 *		     the ENTRY portion of the buffer.
 * - .cmd_packing: A function that deals with packing/unpacking the COMMAND
 *		   काष्ठाure to/from the SPI buffer.
 *		   It is given the same @packed_buf poपूर्णांकer as .entry_packing,
 *		   so most of the समय, the @packed_buf poपूर्णांकs *behind* the
 *		   COMMAND offset inside the buffer.
 *		   To access the COMMAND portion of the buffer, the function
 *		   knows its correct offset.
 *		   Giving both functions the same poपूर्णांकer is handy because in
 *		   extreme हालs (see sja1105pqrs_dyn_l2_lookup_entry_packing)
 *		   the .entry_packing is able to jump to the COMMAND portion,
 *		   or vice-versa (sja1105pqrs_l2_lookup_cmd_packing).
 * - .access: A biपंचांगap of:
 *	OP_READ: Set अगर the hardware manual marks the ENTRY portion of the
 *		 dynamic configuration table buffer as R (पढ़ोable) after
 *		 an SPI पढ़ो command (the चयन will populate the buffer).
 *	OP_WRITE: Set अगर the manual marks the ENTRY portion of the dynamic
 *		  table buffer as W (writable) after an SPI ग_लिखो command
 *		  (the चयन will पढ़ो the fields provided in the buffer).
 *	OP_DEL: Set अगर the manual says the VALIDENT bit is supported in the
 *		COMMAND portion of this dynamic config buffer (i.e. the
 *		specअगरied entry can be invalidated through a SPI ग_लिखो
 *		command).
 *	OP_SEARCH: Set अगर the manual says that the index of an entry can
 *		   be retrieved in the COMMAND portion of the buffer based
 *		   on its ENTRY portion, as a result of a SPI ग_लिखो command.
 *		   Only the TCAM-based FDB table on SJA1105 P/Q/R/S supports
 *		   this.
 * - .max_entry_count: The number of entries, counting from zero, that can be
 *		       reconfigured through the dynamic पूर्णांकerface. If a अटल
 *		       table can be reconfigured at all dynamically, this
 *		       number always matches the maximum number of supported
 *		       अटल entries.
 * - .packed_size: The length in bytes of the compound ENTRY + COMMAND BUFFER.
 *		   Note that someबार the compound buffer may contain holes in
 *		   it (see sja1105_vlan_lookup_cmd_packing). The @packed_buf is
 *		   contiguous however, so @packed_size includes any unused
 *		   bytes.
 * - .addr: The base SPI address at which the buffer must be written to the
 *	    चयन's memory. When looking at the hardware manual, this must
 *	    always match the lowest करोcumented address क्रम the ENTRY, and not
 *	    that of the COMMAND, since the other 32-bit words will follow aदीर्घ
 *	    at the correct addresses.
 */

#घोषणा SJA1105_SIZE_DYN_CMD					4

#घोषणा SJA1105ET_SIZE_VL_LOOKUP_DYN_CMD			\
	SJA1105_SIZE_DYN_CMD

#घोषणा SJA1105PQRS_SIZE_VL_LOOKUP_DYN_CMD			\
	(SJA1105_SIZE_DYN_CMD + SJA1105_SIZE_VL_LOOKUP_ENTRY)

#घोषणा SJA1105ET_SIZE_MAC_CONFIG_DYN_ENTRY			\
	SJA1105_SIZE_DYN_CMD

#घोषणा SJA1105ET_SIZE_L2_LOOKUP_DYN_CMD			\
	(SJA1105_SIZE_DYN_CMD + SJA1105ET_SIZE_L2_LOOKUP_ENTRY)

#घोषणा SJA1105PQRS_SIZE_L2_LOOKUP_DYN_CMD			\
	(SJA1105_SIZE_DYN_CMD + SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY)

#घोषणा SJA1105_SIZE_VLAN_LOOKUP_DYN_CMD			\
	(SJA1105_SIZE_DYN_CMD + 4 + SJA1105_SIZE_VLAN_LOOKUP_ENTRY)

#घोषणा SJA1105_SIZE_L2_FORWARDING_DYN_CMD			\
	(SJA1105_SIZE_DYN_CMD + SJA1105_SIZE_L2_FORWARDING_ENTRY)

#घोषणा SJA1105ET_SIZE_MAC_CONFIG_DYN_CMD			\
	(SJA1105_SIZE_DYN_CMD + SJA1105ET_SIZE_MAC_CONFIG_DYN_ENTRY)

#घोषणा SJA1105PQRS_SIZE_MAC_CONFIG_DYN_CMD			\
	(SJA1105_SIZE_DYN_CMD + SJA1105PQRS_SIZE_MAC_CONFIG_ENTRY)

#घोषणा SJA1105ET_SIZE_L2_LOOKUP_PARAMS_DYN_CMD			\
	SJA1105_SIZE_DYN_CMD

#घोषणा SJA1105PQRS_SIZE_L2_LOOKUP_PARAMS_DYN_CMD		\
	(SJA1105_SIZE_DYN_CMD + SJA1105PQRS_SIZE_L2_LOOKUP_PARAMS_ENTRY)

#घोषणा SJA1105ET_SIZE_GENERAL_PARAMS_DYN_CMD			\
	SJA1105_SIZE_DYN_CMD

#घोषणा SJA1105PQRS_SIZE_GENERAL_PARAMS_DYN_CMD			\
	(SJA1105_SIZE_DYN_CMD + SJA1105PQRS_SIZE_GENERAL_PARAMS_ENTRY)

#घोषणा SJA1105PQRS_SIZE_AVB_PARAMS_DYN_CMD			\
	(SJA1105_SIZE_DYN_CMD + SJA1105PQRS_SIZE_AVB_PARAMS_ENTRY)

#घोषणा SJA1105_SIZE_RETAGGING_DYN_CMD				\
	(SJA1105_SIZE_DYN_CMD + SJA1105_SIZE_RETAGGING_ENTRY)

#घोषणा SJA1105ET_SIZE_CBS_DYN_CMD				\
	(SJA1105_SIZE_DYN_CMD + SJA1105ET_SIZE_CBS_ENTRY)

#घोषणा SJA1105PQRS_SIZE_CBS_DYN_CMD				\
	(SJA1105_SIZE_DYN_CMD + SJA1105PQRS_SIZE_CBS_ENTRY)

#घोषणा SJA1105_MAX_DYN_CMD_SIZE				\
	SJA1105PQRS_SIZE_GENERAL_PARAMS_DYN_CMD

काष्ठा sja1105_dyn_cmd अणु
	bool search;
	u64 valid;
	u64 rdwrset;
	u64 errors;
	u64 valident;
	u64 index;
पूर्ण;

क्रमागत sja1105_hostcmd अणु
	SJA1105_HOSTCMD_SEARCH = 1,
	SJA1105_HOSTCMD_READ = 2,
	SJA1105_HOSTCMD_WRITE = 3,
	SJA1105_HOSTCMD_INVALIDATE = 4,
पूर्ण;

/* Command and entry overlap */
अटल व्योम
sja1105et_vl_lookup_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				क्रमागत packing_op op)
अणु
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(buf, &cmd->valid,   31, 31, size, op);
	sja1105_packing(buf, &cmd->errors,  30, 30, size, op);
	sja1105_packing(buf, &cmd->rdwrset, 29, 29, size, op);
	sja1105_packing(buf, &cmd->index,    9,  0, size, op);
पूर्ण

/* Command and entry are separate */
अटल व्योम
sja1105pqrs_vl_lookup_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				  क्रमागत packing_op op)
अणु
	u8 *p = buf + SJA1105_SIZE_VL_LOOKUP_ENTRY;
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(p, &cmd->valid,   31, 31, size, op);
	sja1105_packing(p, &cmd->errors,  30, 30, size, op);
	sja1105_packing(p, &cmd->rdwrset, 29, 29, size, op);
	sja1105_packing(p, &cmd->index,    9,  0, size, op);
पूर्ण

अटल माप_प्रकार sja1105et_vl_lookup_entry_packing(व्योम *buf, व्योम *entry_ptr,
						क्रमागत packing_op op)
अणु
	काष्ठा sja1105_vl_lookup_entry *entry = entry_ptr;
	स्थिर पूर्णांक size = SJA1105ET_SIZE_VL_LOOKUP_DYN_CMD;

	sja1105_packing(buf, &entry->egrmirr,  21, 17, size, op);
	sja1105_packing(buf, &entry->ingrmirr, 16, 16, size, op);
	वापस size;
पूर्ण

अटल व्योम
sja1105pqrs_l2_lookup_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				  क्रमागत packing_op op)
अणु
	u8 *p = buf + SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY;
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;
	u64 hostcmd;

	sja1105_packing(p, &cmd->valid,    31, 31, size, op);
	sja1105_packing(p, &cmd->rdwrset,  30, 30, size, op);
	sja1105_packing(p, &cmd->errors,   29, 29, size, op);
	sja1105_packing(p, &cmd->valident, 27, 27, size, op);

	/* VALIDENT is supposed to indicate "keep or not", but in SJA1105 E/T,
	 * using it to delete a management route was unsupported. UM10944
	 * said about it:
	 *
	 *   In हाल of a ग_लिखो access with the MGMTROUTE flag set,
	 *   the flag will be ignored. It will always be found cleared
	 *   क्रम पढ़ो accesses with the MGMTROUTE flag set.
	 *
	 * SJA1105 P/Q/R/S keeps the same behavior w.r.t. VALIDENT, but there
	 * is now another flag called HOSTCMD which करोes more stuff (quoting
	 * from UM11040):
	 *
	 *   A ग_लिखो request is accepted only when HOSTCMD is set to ग_लिखो host
	 *   or invalid. A पढ़ो request is accepted only when HOSTCMD is set to
	 *   search host or पढ़ो host.
	 *
	 * So it is possible to translate a RDWRSET/VALIDENT combination पूर्णांकo
	 * HOSTCMD so that we keep the dynamic command API in place, and
	 * at the same समय achieve compatibility with the management route
	 * command काष्ठाure.
	 */
	अगर (cmd->rdwrset == SPI_READ) अणु
		अगर (cmd->search)
			hostcmd = SJA1105_HOSTCMD_SEARCH;
		अन्यथा
			hostcmd = SJA1105_HOSTCMD_READ;
	पूर्ण अन्यथा अणु
		/* SPI_WRITE */
		अगर (cmd->valident)
			hostcmd = SJA1105_HOSTCMD_WRITE;
		अन्यथा
			hostcmd = SJA1105_HOSTCMD_INVALIDATE;
	पूर्ण
	sja1105_packing(p, &hostcmd, 25, 23, size, op);

	/* Hack - The hardware takes the 'index' field within
	 * काष्ठा sja1105_l2_lookup_entry as the index on which this command
	 * will operate. However it will ignore everything अन्यथा, so 'index'
	 * is logically part of command but physically part of entry.
	 * Populate the 'index' entry field from within the command callback,
	 * such that our API करोesn't need to ask क्रम a full-blown entry
	 * काष्ठाure when e.g. a delete is requested.
	 */
	sja1105_packing(buf, &cmd->index, 15, 6,
			SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY, op);
पूर्ण

/* The चयन is so retarded that it makes our command/entry असलtraction
 * crumble apart.
 *
 * On P/Q/R/S, the चयन tries to say whether a FDB entry
 * is अटलally programmed or dynamically learned via a flag called LOCKEDS.
 * The hardware manual says about this fiels:
 *
 *   On ग_लिखो will specअगरy the क्रमmat of ENTRY.
 *   On पढ़ो the flag will be found cleared at बार the VALID flag is found
 *   set.  The flag will also be found cleared in response to a पढ़ो having the
 *   MGMTROUTE flag set.  In response to a पढ़ो with the MGMTROUTE flag
 *   cleared, the flag be set अगर the most recent access operated on an entry
 *   that was either loaded by configuration or through dynamic reconfiguration
 *   (as opposed to स्वतःmatically learned entries).
 *
 * The trouble with this flag is that it's part of the *command* to access the
 * dynamic पूर्णांकerface, and not part of the *entry* retrieved from it.
 * Otherwise said, क्रम a sja1105_dynamic_config_पढ़ो, LOCKEDS is supposed to be
 * an output from the चयन पूर्णांकo the command buffer, and क्रम a
 * sja1105_dynamic_config_ग_लिखो, the चयन treats LOCKEDS as an input
 * (hence we can ग_लिखो either अटल, or स्वतःmatically learned entries, from
 * the core).
 * But the manual contradicts itself in the last phrase where it says that on
 * पढ़ो, LOCKEDS will be set to 1 क्रम all FDB entries written through the
 * dynamic पूर्णांकerface (thereक्रमe, the value of LOCKEDS from the
 * sja1105_dynamic_config_ग_लिखो is not really used क्रम anything, it'll store a
 * 1 anyway).
 * This means you can't really ग_लिखो a FDB entry with LOCKEDS=0 (स्वतःmatically
 * learned) पूर्णांकo the चयन, which kind of makes sense.
 * As क्रम पढ़ोing through the dynamic पूर्णांकerface, it करोesn't make too much sense
 * to put LOCKEDS पूर्णांकo the command, since the चयन will inevitably have to
 * ignore it (otherwise a command would be like "पढ़ो the FDB entry 123, but
 * only अगर it's dynamically learned" <- well how am I supposed to know?) and
 * just use it as an output buffer क्रम its findings. But guess what... that's
 * what the entry buffer is क्रम!
 * Unक्रमtunately, what really अवरोधs this असलtraction is the fact that it
 * wasn't deचिन्हित having the fact in mind that the चयन can output
 * entry-related data as ग_लिखोback through the command buffer.
 * However, whether a FDB entry is अटलally or dynamically learned *is* part
 * of the entry and not the command data, no matter what the चयन thinks.
 * In order to करो that, we'll need to wrap around the
 * sja1105pqrs_l2_lookup_entry_packing from sja1105_अटल_config.c, and take
 * a peek outside of the caller-supplied @buf (the entry buffer), to reach the
 * command buffer.
 */
अटल माप_प्रकार
sja1105pqrs_dyn_l2_lookup_entry_packing(व्योम *buf, व्योम *entry_ptr,
					क्रमागत packing_op op)
अणु
	काष्ठा sja1105_l2_lookup_entry *entry = entry_ptr;
	u8 *cmd = buf + SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY;
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(cmd, &entry->lockeds, 28, 28, size, op);

	वापस sja1105pqrs_l2_lookup_entry_packing(buf, entry_ptr, op);
पूर्ण

अटल व्योम
sja1105et_l2_lookup_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				क्रमागत packing_op op)
अणु
	u8 *p = buf + SJA1105ET_SIZE_L2_LOOKUP_ENTRY;
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(p, &cmd->valid,    31, 31, size, op);
	sja1105_packing(p, &cmd->rdwrset,  30, 30, size, op);
	sja1105_packing(p, &cmd->errors,   29, 29, size, op);
	sja1105_packing(p, &cmd->valident, 27, 27, size, op);
	/* Hack - see comments above. */
	sja1105_packing(buf, &cmd->index, 29, 20,
			SJA1105ET_SIZE_L2_LOOKUP_ENTRY, op);
पूर्ण

अटल माप_प्रकार sja1105et_dyn_l2_lookup_entry_packing(व्योम *buf, व्योम *entry_ptr,
						    क्रमागत packing_op op)
अणु
	काष्ठा sja1105_l2_lookup_entry *entry = entry_ptr;
	u8 *cmd = buf + SJA1105ET_SIZE_L2_LOOKUP_ENTRY;
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(cmd, &entry->lockeds, 28, 28, size, op);

	वापस sja1105et_l2_lookup_entry_packing(buf, entry_ptr, op);
पूर्ण

अटल व्योम
sja1105et_mgmt_route_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				 क्रमागत packing_op op)
अणु
	u8 *p = buf + SJA1105ET_SIZE_L2_LOOKUP_ENTRY;
	u64 mgmtroute = 1;

	sja1105et_l2_lookup_cmd_packing(buf, cmd, op);
	अगर (op == PACK)
		sja1105_pack(p, &mgmtroute, 26, 26, SJA1105_SIZE_DYN_CMD);
पूर्ण

अटल माप_प्रकार sja1105et_mgmt_route_entry_packing(व्योम *buf, व्योम *entry_ptr,
						 क्रमागत packing_op op)
अणु
	काष्ठा sja1105_mgmt_entry *entry = entry_ptr;
	स्थिर माप_प्रकार size = SJA1105ET_SIZE_L2_LOOKUP_ENTRY;

	/* UM10944: To specअगरy अगर a PTP egress बारtamp shall be captured on
	 * each port upon transmission of the frame, the LSB of VLANID in the
	 * ENTRY field provided by the host must be set.
	 * Bit 1 of VLANID then specअगरies the रेजिस्टर where the बारtamp क्रम
	 * this port is stored in.
	 */
	sja1105_packing(buf, &entry->tsreg,     85, 85, size, op);
	sja1105_packing(buf, &entry->takets,    84, 84, size, op);
	sja1105_packing(buf, &entry->macaddr,   83, 36, size, op);
	sja1105_packing(buf, &entry->destports, 35, 31, size, op);
	sja1105_packing(buf, &entry->enfport,   30, 30, size, op);
	वापस size;
पूर्ण

अटल व्योम
sja1105pqrs_mgmt_route_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				   क्रमागत packing_op op)
अणु
	u8 *p = buf + SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY;
	u64 mgmtroute = 1;

	sja1105pqrs_l2_lookup_cmd_packing(buf, cmd, op);
	अगर (op == PACK)
		sja1105_pack(p, &mgmtroute, 26, 26, SJA1105_SIZE_DYN_CMD);
पूर्ण

अटल माप_प्रकार sja1105pqrs_mgmt_route_entry_packing(व्योम *buf, व्योम *entry_ptr,
						   क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105PQRS_SIZE_L2_LOOKUP_ENTRY;
	काष्ठा sja1105_mgmt_entry *entry = entry_ptr;

	/* In P/Q/R/S, enfport got नामd to mgmtvalid, but its purpose
	 * is the same (driver uses it to confirm that frame was sent).
	 * So just keep the name from E/T.
	 */
	sja1105_packing(buf, &entry->tsreg,     71, 71, size, op);
	sja1105_packing(buf, &entry->takets,    70, 70, size, op);
	sja1105_packing(buf, &entry->macaddr,   69, 22, size, op);
	sja1105_packing(buf, &entry->destports, 21, 17, size, op);
	sja1105_packing(buf, &entry->enfport,   16, 16, size, op);
	वापस size;
पूर्ण

/* In E/T, entry is at addresses 0x27-0x28. There is a 4 byte gap at 0x29,
 * and command is at 0x2a. Similarly in P/Q/R/S there is a 1 रेजिस्टर gap
 * between entry (0x2d, 0x2e) and command (0x30).
 */
अटल व्योम
sja1105_vlan_lookup_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				क्रमागत packing_op op)
अणु
	u8 *p = buf + SJA1105_SIZE_VLAN_LOOKUP_ENTRY + 4;
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(p, &cmd->valid,    31, 31, size, op);
	sja1105_packing(p, &cmd->rdwrset,  30, 30, size, op);
	sja1105_packing(p, &cmd->valident, 27, 27, size, op);
	/* Hack - see comments above, applied क्रम 'vlanid' field of
	 * काष्ठा sja1105_vlan_lookup_entry.
	 */
	sja1105_packing(buf, &cmd->index, 38, 27,
			SJA1105_SIZE_VLAN_LOOKUP_ENTRY, op);
पूर्ण

अटल व्योम
sja1105_l2_क्रमwarding_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				  क्रमागत packing_op op)
अणु
	u8 *p = buf + SJA1105_SIZE_L2_FORWARDING_ENTRY;
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(p, &cmd->valid,   31, 31, size, op);
	sja1105_packing(p, &cmd->errors,  30, 30, size, op);
	sja1105_packing(p, &cmd->rdwrset, 29, 29, size, op);
	sja1105_packing(p, &cmd->index,    4,  0, size, op);
पूर्ण

अटल व्योम
sja1105et_mac_config_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				 क्रमागत packing_op op)
अणु
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;
	/* Yup, user manual definitions are reversed */
	u8 *reg1 = buf + 4;

	sja1105_packing(reg1, &cmd->valid, 31, 31, size, op);
	sja1105_packing(reg1, &cmd->index, 26, 24, size, op);
पूर्ण

अटल माप_प्रकार sja1105et_mac_config_entry_packing(व्योम *buf, व्योम *entry_ptr,
						 क्रमागत packing_op op)
अणु
	स्थिर पूर्णांक size = SJA1105ET_SIZE_MAC_CONFIG_DYN_ENTRY;
	काष्ठा sja1105_mac_config_entry *entry = entry_ptr;
	/* Yup, user manual definitions are reversed */
	u8 *reg1 = buf + 4;
	u8 *reg2 = buf;

	sja1105_packing(reg1, &entry->speed,     30, 29, size, op);
	sja1105_packing(reg1, &entry->drpdtag,   23, 23, size, op);
	sja1105_packing(reg1, &entry->drpuntag,  22, 22, size, op);
	sja1105_packing(reg1, &entry->retag,     21, 21, size, op);
	sja1105_packing(reg1, &entry->dyn_learn, 20, 20, size, op);
	sja1105_packing(reg1, &entry->egress,    19, 19, size, op);
	sja1105_packing(reg1, &entry->ingress,   18, 18, size, op);
	sja1105_packing(reg1, &entry->ing_mirr,  17, 17, size, op);
	sja1105_packing(reg1, &entry->egr_mirr,  16, 16, size, op);
	sja1105_packing(reg1, &entry->vlanprio,  14, 12, size, op);
	sja1105_packing(reg1, &entry->vlanid,    11,  0, size, op);
	sja1105_packing(reg2, &entry->tp_delin,  31, 16, size, op);
	sja1105_packing(reg2, &entry->tp_delout, 15,  0, size, op);
	/* MAC configuration table entries which can't be reconfigured:
	 * top, base, enabled, अगरg, maxage, drpnona664
	 */
	/* Bogus वापस value, not used anywhere */
	वापस 0;
पूर्ण

अटल व्योम
sja1105pqrs_mac_config_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				   क्रमागत packing_op op)
अणु
	स्थिर पूर्णांक size = SJA1105ET_SIZE_MAC_CONFIG_DYN_ENTRY;
	u8 *p = buf + SJA1105PQRS_SIZE_MAC_CONFIG_ENTRY;

	sja1105_packing(p, &cmd->valid,   31, 31, size, op);
	sja1105_packing(p, &cmd->errors,  30, 30, size, op);
	sja1105_packing(p, &cmd->rdwrset, 29, 29, size, op);
	sja1105_packing(p, &cmd->index,    2,  0, size, op);
पूर्ण

अटल व्योम
sja1105et_l2_lookup_params_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				       क्रमागत packing_op op)
अणु
	sja1105_packing(buf, &cmd->valid, 31, 31,
			SJA1105ET_SIZE_L2_LOOKUP_PARAMS_DYN_CMD, op);
पूर्ण

अटल माप_प्रकार
sja1105et_l2_lookup_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
					 क्रमागत packing_op op)
अणु
	काष्ठा sja1105_l2_lookup_params_entry *entry = entry_ptr;

	sja1105_packing(buf, &entry->poly, 7, 0,
			SJA1105ET_SIZE_L2_LOOKUP_PARAMS_DYN_CMD, op);
	/* Bogus वापस value, not used anywhere */
	वापस 0;
पूर्ण

अटल व्योम
sja1105pqrs_l2_lookup_params_cmd_packing(व्योम *buf,
					 काष्ठा sja1105_dyn_cmd *cmd,
					 क्रमागत packing_op op)
अणु
	u8 *p = buf + SJA1105PQRS_SIZE_L2_LOOKUP_PARAMS_ENTRY;
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(p, &cmd->valid,   31, 31, size, op);
	sja1105_packing(p, &cmd->rdwrset, 30, 30, size, op);
पूर्ण

अटल व्योम
sja1105et_general_params_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				     क्रमागत packing_op op)
अणु
	स्थिर पूर्णांक size = SJA1105ET_SIZE_GENERAL_PARAMS_DYN_CMD;

	sja1105_packing(buf, &cmd->valid,  31, 31, size, op);
	sja1105_packing(buf, &cmd->errors, 30, 30, size, op);
पूर्ण

अटल माप_प्रकार
sja1105et_general_params_entry_packing(व्योम *buf, व्योम *entry_ptr,
				       क्रमागत packing_op op)
अणु
	काष्ठा sja1105_general_params_entry *entry = entry_ptr;
	स्थिर पूर्णांक size = SJA1105ET_SIZE_GENERAL_PARAMS_DYN_CMD;

	sja1105_packing(buf, &entry->mirr_port, 2, 0, size, op);
	/* Bogus वापस value, not used anywhere */
	वापस 0;
पूर्ण

अटल व्योम
sja1105pqrs_general_params_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				       क्रमागत packing_op op)
अणु
	u8 *p = buf + SJA1105PQRS_SIZE_GENERAL_PARAMS_ENTRY;
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(p, &cmd->valid,   31, 31, size, op);
	sja1105_packing(p, &cmd->errors,  30, 30, size, op);
	sja1105_packing(p, &cmd->rdwrset, 28, 28, size, op);
पूर्ण

अटल व्योम
sja1105pqrs_avb_params_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				   क्रमागत packing_op op)
अणु
	u8 *p = buf + SJA1105PQRS_SIZE_AVB_PARAMS_ENTRY;
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(p, &cmd->valid,   31, 31, size, op);
	sja1105_packing(p, &cmd->errors,  30, 30, size, op);
	sja1105_packing(p, &cmd->rdwrset, 29, 29, size, op);
पूर्ण

अटल व्योम
sja1105_retagging_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
			      क्रमागत packing_op op)
अणु
	u8 *p = buf + SJA1105_SIZE_RETAGGING_ENTRY;
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(p, &cmd->valid,    31, 31, size, op);
	sja1105_packing(p, &cmd->errors,   30, 30, size, op);
	sja1105_packing(p, &cmd->valident, 29, 29, size, op);
	sja1105_packing(p, &cmd->rdwrset,  28, 28, size, op);
	sja1105_packing(p, &cmd->index,     5,  0, size, op);
पूर्ण

अटल व्योम sja1105et_cbs_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
				      क्रमागत packing_op op)
अणु
	u8 *p = buf + SJA1105ET_SIZE_CBS_ENTRY;
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(p, &cmd->valid, 31, 31, size, op);
	sja1105_packing(p, &cmd->index, 19, 16, size, op);
पूर्ण

अटल माप_प्रकार sja1105et_cbs_entry_packing(व्योम *buf, व्योम *entry_ptr,
					  क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105ET_SIZE_CBS_ENTRY;
	काष्ठा sja1105_cbs_entry *entry = entry_ptr;
	u8 *cmd = buf + size;
	u32 *p = buf;

	sja1105_packing(cmd, &entry->port, 5, 3, SJA1105_SIZE_DYN_CMD, op);
	sja1105_packing(cmd, &entry->prio, 2, 0, SJA1105_SIZE_DYN_CMD, op);
	sja1105_packing(p + 3, &entry->credit_lo,  31, 0, size, op);
	sja1105_packing(p + 2, &entry->credit_hi,  31, 0, size, op);
	sja1105_packing(p + 1, &entry->send_slope, 31, 0, size, op);
	sja1105_packing(p + 0, &entry->idle_slope, 31, 0, size, op);
	वापस size;
पूर्ण

अटल व्योम sja1105pqrs_cbs_cmd_packing(व्योम *buf, काष्ठा sja1105_dyn_cmd *cmd,
					क्रमागत packing_op op)
अणु
	u8 *p = buf + SJA1105PQRS_SIZE_CBS_ENTRY;
	स्थिर पूर्णांक size = SJA1105_SIZE_DYN_CMD;

	sja1105_packing(p, &cmd->valid,   31, 31, size, op);
	sja1105_packing(p, &cmd->rdwrset, 30, 30, size, op);
	sja1105_packing(p, &cmd->errors,  29, 29, size, op);
	sja1105_packing(p, &cmd->index,    3,  0, size, op);
पूर्ण

अटल माप_प्रकार sja1105pqrs_cbs_entry_packing(व्योम *buf, व्योम *entry_ptr,
					    क्रमागत packing_op op)
अणु
	स्थिर माप_प्रकार size = SJA1105PQRS_SIZE_CBS_ENTRY;
	काष्ठा sja1105_cbs_entry *entry = entry_ptr;

	sja1105_packing(buf, &entry->port,      159, 157, size, op);
	sja1105_packing(buf, &entry->prio,      156, 154, size, op);
	sja1105_packing(buf, &entry->credit_lo, 153, 122, size, op);
	sja1105_packing(buf, &entry->credit_hi, 121,  90, size, op);
	sja1105_packing(buf, &entry->send_slope, 89,  58, size, op);
	sja1105_packing(buf, &entry->idle_slope, 57,  26, size, op);
	वापस size;
पूर्ण

#घोषणा OP_READ		BIT(0)
#घोषणा OP_WRITE	BIT(1)
#घोषणा OP_DEL		BIT(2)
#घोषणा OP_SEARCH	BIT(3)

/* SJA1105E/T: First generation */
स्थिर काष्ठा sja1105_dynamic_table_ops sja1105et_dyn_ops[BLK_IDX_MAX_DYN] = अणु
	[BLK_IDX_VL_LOOKUP] = अणु
		.entry_packing = sja1105et_vl_lookup_entry_packing,
		.cmd_packing = sja1105et_vl_lookup_cmd_packing,
		.access = OP_WRITE,
		.max_entry_count = SJA1105_MAX_VL_LOOKUP_COUNT,
		.packed_size = SJA1105ET_SIZE_VL_LOOKUP_DYN_CMD,
		.addr = 0x35,
	पूर्ण,
	[BLK_IDX_L2_LOOKUP] = अणु
		.entry_packing = sja1105et_dyn_l2_lookup_entry_packing,
		.cmd_packing = sja1105et_l2_lookup_cmd_packing,
		.access = (OP_READ | OP_WRITE | OP_DEL),
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_COUNT,
		.packed_size = SJA1105ET_SIZE_L2_LOOKUP_DYN_CMD,
		.addr = 0x20,
	पूर्ण,
	[BLK_IDX_MGMT_ROUTE] = अणु
		.entry_packing = sja1105et_mgmt_route_entry_packing,
		.cmd_packing = sja1105et_mgmt_route_cmd_packing,
		.access = (OP_READ | OP_WRITE),
		.max_entry_count = SJA1105_NUM_PORTS,
		.packed_size = SJA1105ET_SIZE_L2_LOOKUP_DYN_CMD,
		.addr = 0x20,
	पूर्ण,
	[BLK_IDX_VLAN_LOOKUP] = अणु
		.entry_packing = sja1105_vlan_lookup_entry_packing,
		.cmd_packing = sja1105_vlan_lookup_cmd_packing,
		.access = (OP_WRITE | OP_DEL),
		.max_entry_count = SJA1105_MAX_VLAN_LOOKUP_COUNT,
		.packed_size = SJA1105_SIZE_VLAN_LOOKUP_DYN_CMD,
		.addr = 0x27,
	पूर्ण,
	[BLK_IDX_L2_FORWARDING] = अणु
		.entry_packing = sja1105_l2_क्रमwarding_entry_packing,
		.cmd_packing = sja1105_l2_क्रमwarding_cmd_packing,
		.max_entry_count = SJA1105_MAX_L2_FORWARDING_COUNT,
		.access = OP_WRITE,
		.packed_size = SJA1105_SIZE_L2_FORWARDING_DYN_CMD,
		.addr = 0x24,
	पूर्ण,
	[BLK_IDX_MAC_CONFIG] = अणु
		.entry_packing = sja1105et_mac_config_entry_packing,
		.cmd_packing = sja1105et_mac_config_cmd_packing,
		.max_entry_count = SJA1105_MAX_MAC_CONFIG_COUNT,
		.access = OP_WRITE,
		.packed_size = SJA1105ET_SIZE_MAC_CONFIG_DYN_CMD,
		.addr = 0x36,
	पूर्ण,
	[BLK_IDX_L2_LOOKUP_PARAMS] = अणु
		.entry_packing = sja1105et_l2_lookup_params_entry_packing,
		.cmd_packing = sja1105et_l2_lookup_params_cmd_packing,
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_PARAMS_COUNT,
		.access = OP_WRITE,
		.packed_size = SJA1105ET_SIZE_L2_LOOKUP_PARAMS_DYN_CMD,
		.addr = 0x38,
	पूर्ण,
	[BLK_IDX_GENERAL_PARAMS] = अणु
		.entry_packing = sja1105et_general_params_entry_packing,
		.cmd_packing = sja1105et_general_params_cmd_packing,
		.max_entry_count = SJA1105_MAX_GENERAL_PARAMS_COUNT,
		.access = OP_WRITE,
		.packed_size = SJA1105ET_SIZE_GENERAL_PARAMS_DYN_CMD,
		.addr = 0x34,
	पूर्ण,
	[BLK_IDX_RETAGGING] = अणु
		.entry_packing = sja1105_retagging_entry_packing,
		.cmd_packing = sja1105_retagging_cmd_packing,
		.max_entry_count = SJA1105_MAX_RETAGGING_COUNT,
		.access = (OP_WRITE | OP_DEL),
		.packed_size = SJA1105_SIZE_RETAGGING_DYN_CMD,
		.addr = 0x31,
	पूर्ण,
	[BLK_IDX_CBS] = अणु
		.entry_packing = sja1105et_cbs_entry_packing,
		.cmd_packing = sja1105et_cbs_cmd_packing,
		.max_entry_count = SJA1105ET_MAX_CBS_COUNT,
		.access = OP_WRITE,
		.packed_size = SJA1105ET_SIZE_CBS_DYN_CMD,
		.addr = 0x2c,
	पूर्ण,
पूर्ण;

/* SJA1105P/Q/R/S: Second generation */
स्थिर काष्ठा sja1105_dynamic_table_ops sja1105pqrs_dyn_ops[BLK_IDX_MAX_DYN] = अणु
	[BLK_IDX_VL_LOOKUP] = अणु
		.entry_packing = sja1105_vl_lookup_entry_packing,
		.cmd_packing = sja1105pqrs_vl_lookup_cmd_packing,
		.access = (OP_READ | OP_WRITE),
		.max_entry_count = SJA1105_MAX_VL_LOOKUP_COUNT,
		.packed_size = SJA1105PQRS_SIZE_VL_LOOKUP_DYN_CMD,
		.addr = 0x47,
	पूर्ण,
	[BLK_IDX_L2_LOOKUP] = अणु
		.entry_packing = sja1105pqrs_dyn_l2_lookup_entry_packing,
		.cmd_packing = sja1105pqrs_l2_lookup_cmd_packing,
		.access = (OP_READ | OP_WRITE | OP_DEL | OP_SEARCH),
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_COUNT,
		.packed_size = SJA1105PQRS_SIZE_L2_LOOKUP_DYN_CMD,
		.addr = 0x24,
	पूर्ण,
	[BLK_IDX_MGMT_ROUTE] = अणु
		.entry_packing = sja1105pqrs_mgmt_route_entry_packing,
		.cmd_packing = sja1105pqrs_mgmt_route_cmd_packing,
		.access = (OP_READ | OP_WRITE | OP_DEL | OP_SEARCH),
		.max_entry_count = SJA1105_NUM_PORTS,
		.packed_size = SJA1105PQRS_SIZE_L2_LOOKUP_DYN_CMD,
		.addr = 0x24,
	पूर्ण,
	[BLK_IDX_VLAN_LOOKUP] = अणु
		.entry_packing = sja1105_vlan_lookup_entry_packing,
		.cmd_packing = sja1105_vlan_lookup_cmd_packing,
		.access = (OP_READ | OP_WRITE | OP_DEL),
		.max_entry_count = SJA1105_MAX_VLAN_LOOKUP_COUNT,
		.packed_size = SJA1105_SIZE_VLAN_LOOKUP_DYN_CMD,
		.addr = 0x2D,
	पूर्ण,
	[BLK_IDX_L2_FORWARDING] = अणु
		.entry_packing = sja1105_l2_क्रमwarding_entry_packing,
		.cmd_packing = sja1105_l2_क्रमwarding_cmd_packing,
		.max_entry_count = SJA1105_MAX_L2_FORWARDING_COUNT,
		.access = OP_WRITE,
		.packed_size = SJA1105_SIZE_L2_FORWARDING_DYN_CMD,
		.addr = 0x2A,
	पूर्ण,
	[BLK_IDX_MAC_CONFIG] = अणु
		.entry_packing = sja1105pqrs_mac_config_entry_packing,
		.cmd_packing = sja1105pqrs_mac_config_cmd_packing,
		.max_entry_count = SJA1105_MAX_MAC_CONFIG_COUNT,
		.access = (OP_READ | OP_WRITE),
		.packed_size = SJA1105PQRS_SIZE_MAC_CONFIG_DYN_CMD,
		.addr = 0x4B,
	पूर्ण,
	[BLK_IDX_L2_LOOKUP_PARAMS] = अणु
		.entry_packing = sja1105pqrs_l2_lookup_params_entry_packing,
		.cmd_packing = sja1105pqrs_l2_lookup_params_cmd_packing,
		.max_entry_count = SJA1105_MAX_L2_LOOKUP_PARAMS_COUNT,
		.access = (OP_READ | OP_WRITE),
		.packed_size = SJA1105PQRS_SIZE_L2_LOOKUP_PARAMS_DYN_CMD,
		.addr = 0x54,
	पूर्ण,
	[BLK_IDX_AVB_PARAMS] = अणु
		.entry_packing = sja1105pqrs_avb_params_entry_packing,
		.cmd_packing = sja1105pqrs_avb_params_cmd_packing,
		.max_entry_count = SJA1105_MAX_AVB_PARAMS_COUNT,
		.access = (OP_READ | OP_WRITE),
		.packed_size = SJA1105PQRS_SIZE_AVB_PARAMS_DYN_CMD,
		.addr = 0x8003,
	पूर्ण,
	[BLK_IDX_GENERAL_PARAMS] = अणु
		.entry_packing = sja1105pqrs_general_params_entry_packing,
		.cmd_packing = sja1105pqrs_general_params_cmd_packing,
		.max_entry_count = SJA1105_MAX_GENERAL_PARAMS_COUNT,
		.access = (OP_READ | OP_WRITE),
		.packed_size = SJA1105PQRS_SIZE_GENERAL_PARAMS_DYN_CMD,
		.addr = 0x3B,
	पूर्ण,
	[BLK_IDX_RETAGGING] = अणु
		.entry_packing = sja1105_retagging_entry_packing,
		.cmd_packing = sja1105_retagging_cmd_packing,
		.max_entry_count = SJA1105_MAX_RETAGGING_COUNT,
		.access = (OP_READ | OP_WRITE | OP_DEL),
		.packed_size = SJA1105_SIZE_RETAGGING_DYN_CMD,
		.addr = 0x38,
	पूर्ण,
	[BLK_IDX_CBS] = अणु
		.entry_packing = sja1105pqrs_cbs_entry_packing,
		.cmd_packing = sja1105pqrs_cbs_cmd_packing,
		.max_entry_count = SJA1105PQRS_MAX_CBS_COUNT,
		.access = OP_WRITE,
		.packed_size = SJA1105PQRS_SIZE_CBS_DYN_CMD,
		.addr = 0x32,
	पूर्ण,
पूर्ण;

/* Provides पढ़ो access to the settings through the dynamic पूर्णांकerface
 * of the चयन.
 * @blk_idx	is used as key to select from the sja1105_dynamic_table_ops.
 *		The selection is limited by the hardware in respect to which
 *		configuration blocks can be पढ़ो through the dynamic पूर्णांकerface.
 * @index	is used to retrieve a particular table entry. If negative,
 *		(and अगर the @blk_idx supports the searching operation) a search
 *		is perक्रमmed by the @entry parameter.
 * @entry	Type-casted to an unpacked काष्ठाure that holds a table entry
 *		of the type specअगरied in @blk_idx.
 *		Usually an output argument. If @index is negative, then this
 *		argument is used as input/output: it should be pre-populated
 *		with the element to search क्रम. Entries which support the
 *		search operation will have an "index" field (not the @index
 *		argument to this function) and that is where the found index
 *		will be वापसed (or left unmodअगरied - thus negative - अगर not
 *		found).
 */
पूर्णांक sja1105_dynamic_config_पढ़ो(काष्ठा sja1105_निजी *priv,
				क्रमागत sja1105_blk_idx blk_idx,
				पूर्णांक index, व्योम *entry)
अणु
	स्थिर काष्ठा sja1105_dynamic_table_ops *ops;
	काष्ठा sja1105_dyn_cmd cmd = अणु0पूर्ण;
	/* SPI payload buffer */
	u8 packed_buf[SJA1105_MAX_DYN_CMD_SIZE] = अणु0पूर्ण;
	पूर्णांक retries = 3;
	पूर्णांक rc;

	अगर (blk_idx >= BLK_IDX_MAX_DYN)
		वापस -दुस्फल;

	ops = &priv->info->dyn_ops[blk_idx];

	अगर (index >= 0 && index >= ops->max_entry_count)
		वापस -दुस्फल;
	अगर (index < 0 && !(ops->access & OP_SEARCH))
		वापस -EOPNOTSUPP;
	अगर (!(ops->access & OP_READ))
		वापस -EOPNOTSUPP;
	अगर (ops->packed_size > SJA1105_MAX_DYN_CMD_SIZE)
		वापस -दुस्फल;
	अगर (!ops->cmd_packing)
		वापस -EOPNOTSUPP;
	अगर (!ops->entry_packing)
		वापस -EOPNOTSUPP;

	cmd.valid = true; /* Trigger action on table entry */
	cmd.rdwrset = SPI_READ; /* Action is पढ़ो */
	अगर (index < 0) अणु
		/* Aव्योम copying a चिन्हित negative number to an u64 */
		cmd.index = 0;
		cmd.search = true;
	पूर्ण अन्यथा अणु
		cmd.index = index;
		cmd.search = false;
	पूर्ण
	cmd.valident = true;
	ops->cmd_packing(packed_buf, &cmd, PACK);

	अगर (cmd.search)
		ops->entry_packing(packed_buf, entry, PACK);

	/* Send SPI ग_लिखो operation: पढ़ो config table entry */
	rc = sja1105_xfer_buf(priv, SPI_WRITE, ops->addr, packed_buf,
			      ops->packed_size);
	अगर (rc < 0)
		वापस rc;

	/* Loop until we have confirmation that hardware has finished
	 * processing the command and has cleared the VALID field
	 */
	करो अणु
		स_रखो(packed_buf, 0, ops->packed_size);

		/* Retrieve the पढ़ो operation's result */
		rc = sja1105_xfer_buf(priv, SPI_READ, ops->addr, packed_buf,
				      ops->packed_size);
		अगर (rc < 0)
			वापस rc;

		cmd = (काष्ठा sja1105_dyn_cmd) अणु0पूर्ण;
		ops->cmd_packing(packed_buf, &cmd, UNPACK);
		/* UM10944: [valident] will always be found cleared
		 * during a पढ़ो access with MGMTROUTE set.
		 * So करोn't error out in that हाल.
		 */
		अगर (!cmd.valident && blk_idx != BLK_IDX_MGMT_ROUTE)
			वापस -ENOENT;
		cpu_relax();
	पूर्ण जबतक (cmd.valid && --retries);

	अगर (cmd.valid)
		वापस -ETIMEDOUT;

	/* Don't dereference possibly शून्य poपूर्णांकer - maybe caller
	 * only wanted to see whether the entry existed or not.
	 */
	अगर (entry)
		ops->entry_packing(packed_buf, entry, UNPACK);
	वापस 0;
पूर्ण

पूर्णांक sja1105_dynamic_config_ग_लिखो(काष्ठा sja1105_निजी *priv,
				 क्रमागत sja1105_blk_idx blk_idx,
				 पूर्णांक index, व्योम *entry, bool keep)
अणु
	स्थिर काष्ठा sja1105_dynamic_table_ops *ops;
	काष्ठा sja1105_dyn_cmd cmd = अणु0पूर्ण;
	/* SPI payload buffer */
	u8 packed_buf[SJA1105_MAX_DYN_CMD_SIZE] = अणु0पूर्ण;
	पूर्णांक rc;

	अगर (blk_idx >= BLK_IDX_MAX_DYN)
		वापस -दुस्फल;

	ops = &priv->info->dyn_ops[blk_idx];

	अगर (index >= ops->max_entry_count)
		वापस -दुस्फल;
	अगर (index < 0)
		वापस -दुस्फल;
	अगर (!(ops->access & OP_WRITE))
		वापस -EOPNOTSUPP;
	अगर (!keep && !(ops->access & OP_DEL))
		वापस -EOPNOTSUPP;
	अगर (ops->packed_size > SJA1105_MAX_DYN_CMD_SIZE)
		वापस -दुस्फल;

	cmd.valident = keep; /* If false, deletes entry */
	cmd.valid = true; /* Trigger action on table entry */
	cmd.rdwrset = SPI_WRITE; /* Action is ग_लिखो */
	cmd.index = index;

	अगर (!ops->cmd_packing)
		वापस -EOPNOTSUPP;
	ops->cmd_packing(packed_buf, &cmd, PACK);

	अगर (!ops->entry_packing)
		वापस -EOPNOTSUPP;
	/* Don't dereference potentially शून्य poपूर्णांकer अगर just
	 * deleting a table entry is what was requested. For हालs
	 * where 'index' field is physically part of entry काष्ठाure,
	 * and needed here, we deal with that in the cmd_packing callback.
	 */
	अगर (keep)
		ops->entry_packing(packed_buf, entry, PACK);

	/* Send SPI ग_लिखो operation: पढ़ो config table entry */
	rc = sja1105_xfer_buf(priv, SPI_WRITE, ops->addr, packed_buf,
			      ops->packed_size);
	अगर (rc < 0)
		वापस rc;

	cmd = (काष्ठा sja1105_dyn_cmd) अणु0पूर्ण;
	ops->cmd_packing(packed_buf, &cmd, UNPACK);
	अगर (cmd.errors)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल u8 sja1105_crc8_add(u8 crc, u8 byte, u8 poly)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 8; i++) अणु
		अगर ((crc ^ byte) & (1 << 7)) अणु
			crc <<= 1;
			crc ^= poly;
		पूर्ण अन्यथा अणु
			crc <<= 1;
		पूर्ण
		byte <<= 1;
	पूर्ण
	वापस crc;
पूर्ण

/* CRC8 algorithm with non-reversed input, non-reversed output,
 * no input xor and no output xor. Code customized क्रम receiving
 * the SJA1105 E/T FDB keys (vlanid, macaddr) as input. CRC polynomial
 * is also received as argument in the Koopman notation that the चयन
 * hardware stores it in.
 */
u8 sja1105et_fdb_hash(काष्ठा sja1105_निजी *priv, स्थिर u8 *addr, u16 vid)
अणु
	काष्ठा sja1105_l2_lookup_params_entry *l2_lookup_params =
		priv->अटल_config.tables[BLK_IDX_L2_LOOKUP_PARAMS].entries;
	u64 poly_koopman = l2_lookup_params->poly;
	/* Convert polynomial from Koopman to 'normal' notation */
	u8 poly = (u8)(1 + (poly_koopman << 1));
	u64 vlanid = l2_lookup_params->shared_learn ? 0 : vid;
	u64 input = (vlanid << 48) | ether_addr_to_u64(addr);
	u8 crc = 0; /* seed */
	पूर्णांक i;

	/* Mask the eight bytes starting from MSB one at a समय */
	क्रम (i = 56; i >= 0; i -= 8) अणु
		u8 byte = (input & (0xffull << i)) >> i;

		crc = sja1105_crc8_add(crc, byte, poly);
	पूर्ण
	वापस crc;
पूर्ण
