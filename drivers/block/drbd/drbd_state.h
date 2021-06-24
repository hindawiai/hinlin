<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित DRBD_STATE_H
#घोषणा DRBD_STATE_H

काष्ठा drbd_device;
काष्ठा drbd_connection;

/**
 * DOC: DRBD State macros
 *
 * These macros are used to express state changes in easily पढ़ोable क्रमm.
 *
 * The NS macros expand to a mask and a value, that can be bit ored onto the
 * current state as soon as the spinlock (req_lock) was taken.
 *
 * The _NS macros are used क्रम state functions that get called with the
 * spinlock. These macros expand directly to the new state value.
 *
 * Besides the basic क्रमms NS() and _NS() additional _?NS[23] are defined
 * to express state changes that affect more than one aspect of the state.
 *
 * E.g. NS2(conn, C_CONNECTED, peer, R_SECONDARY)
 * Means that the network connection was established and that the peer
 * is in secondary role.
 */
#घोषणा role_MASK R_MASK
#घोषणा peer_MASK R_MASK
#घोषणा disk_MASK D_MASK
#घोषणा pdsk_MASK D_MASK
#घोषणा conn_MASK C_MASK
#घोषणा susp_MASK 1
#घोषणा user_isp_MASK 1
#घोषणा aftr_isp_MASK 1
#घोषणा susp_nod_MASK 1
#घोषणा susp_fen_MASK 1

#घोषणा NS(T, S) \
	(अणु जोड़ drbd_state mask; mask.i = 0; mask.T = T##_MASK; mask; पूर्ण), \
	(अणु जोड़ drbd_state val; val.i = 0; val.T = (S); val; पूर्ण)
#घोषणा NS2(T1, S1, T2, S2) \
	(अणु जोड़ drbd_state mask; mask.i = 0; mask.T1 = T1##_MASK; \
	  mask.T2 = T2##_MASK; mask; पूर्ण), \
	(अणु जोड़ drbd_state val; val.i = 0; val.T1 = (S1); \
	  val.T2 = (S2); val; पूर्ण)
#घोषणा NS3(T1, S1, T2, S2, T3, S3) \
	(अणु जोड़ drbd_state mask; mask.i = 0; mask.T1 = T1##_MASK; \
	  mask.T2 = T2##_MASK; mask.T3 = T3##_MASK; mask; पूर्ण), \
	(अणु जोड़ drbd_state val;  val.i = 0; val.T1 = (S1); \
	  val.T2 = (S2); val.T3 = (S3); val; पूर्ण)

#घोषणा _NS(D, T, S) \
	D, (अणु जोड़ drbd_state __ns; __ns = drbd_पढ़ो_state(D); __ns.T = (S); __ns; पूर्ण)
#घोषणा _NS2(D, T1, S1, T2, S2) \
	D, (अणु जोड़ drbd_state __ns; __ns = drbd_पढ़ो_state(D); __ns.T1 = (S1); \
	__ns.T2 = (S2); __ns; पूर्ण)
#घोषणा _NS3(D, T1, S1, T2, S2, T3, S3) \
	D, (अणु जोड़ drbd_state __ns; __ns = drbd_पढ़ो_state(D); __ns.T1 = (S1); \
	__ns.T2 = (S2); __ns.T3 = (S3); __ns; पूर्ण)

क्रमागत chg_state_flags अणु
	CS_HARD	         = 1 << 0,
	CS_VERBOSE       = 1 << 1,
	CS_WAIT_COMPLETE = 1 << 2,
	CS_SERIALIZE     = 1 << 3,
	CS_ORDERED       = CS_WAIT_COMPLETE + CS_SERIALIZE,
	CS_LOCAL_ONLY    = 1 << 4, /* Do not consider a device pair wide state change */
	CS_DC_ROLE       = 1 << 5, /* DC = display as connection state change */
	CS_DC_PEER       = 1 << 6,
	CS_DC_CONN       = 1 << 7,
	CS_DC_DISK       = 1 << 8,
	CS_DC_PDSK       = 1 << 9,
	CS_DC_SUSP       = 1 << 10,
	CS_DC_MASK       = CS_DC_ROLE + CS_DC_PEER + CS_DC_CONN + CS_DC_DISK + CS_DC_PDSK,
	CS_IGN_OUTD_FAIL = 1 << 11,

	/* Make sure no meta data IO is in flight, by calling
	 * drbd_md_get_buffer().  Used क्रम graceful detach. */
	CS_INHIBIT_MD_IO = 1 << 12,
पूर्ण;

/* drbd_dev_state and drbd_state are dअगरferent types. This is to stress the
   small dअगरference. There is no suspended flag (.susp), and no suspended
   जबतक fence handler runs flas (susp_fen). */
जोड़ drbd_dev_state अणु
	काष्ठा अणु
#अगर defined(__LITTLE_ENDIAN_BITFIELD)
		अचिन्हित role:2 ;   /* 3/4	 primary/secondary/unknown */
		अचिन्हित peer:2 ;   /* 3/4	 primary/secondary/unknown */
		अचिन्हित conn:5 ;   /* 17/32	 cstates */
		अचिन्हित disk:4 ;   /* 8/16	 from D_DISKLESS to D_UP_TO_DATE */
		अचिन्हित pdsk:4 ;   /* 8/16	 from D_DISKLESS to D_UP_TO_DATE */
		अचिन्हित _unused:1 ;
		अचिन्हित aftr_isp:1 ; /* isp .. imposed sync छोड़ो */
		अचिन्हित peer_isp:1 ;
		अचिन्हित user_isp:1 ;
		अचिन्हित _pad:11;   /* 0	 unused */
#या_अगर defined(__BIG_ENDIAN_BITFIELD)
		अचिन्हित _pad:11;
		अचिन्हित user_isp:1 ;
		अचिन्हित peer_isp:1 ;
		अचिन्हित aftr_isp:1 ; /* isp .. imposed sync छोड़ो */
		अचिन्हित _unused:1 ;
		अचिन्हित pdsk:4 ;   /* 8/16	 from D_DISKLESS to D_UP_TO_DATE */
		अचिन्हित disk:4 ;   /* 8/16	 from D_DISKLESS to D_UP_TO_DATE */
		अचिन्हित conn:5 ;   /* 17/32	 cstates */
		अचिन्हित peer:2 ;   /* 3/4	 primary/secondary/unknown */
		अचिन्हित role:2 ;   /* 3/4	 primary/secondary/unknown */
#अन्यथा
# error "this endianess is not supported"
#पूर्ण_अगर
	पूर्ण;
	अचिन्हित पूर्णांक i;
पूर्ण;

बाह्य क्रमागत drbd_state_rv drbd_change_state(काष्ठा drbd_device *device,
					    क्रमागत chg_state_flags f,
					    जोड़ drbd_state mask,
					    जोड़ drbd_state val);
बाह्य व्योम drbd_क्रमce_state(काष्ठा drbd_device *, जोड़ drbd_state,
			जोड़ drbd_state);
बाह्य क्रमागत drbd_state_rv _drbd_request_state(काष्ठा drbd_device *,
					      जोड़ drbd_state,
					      जोड़ drbd_state,
					      क्रमागत chg_state_flags);

बाह्य क्रमागत drbd_state_rv
_drbd_request_state_holding_state_mutex(काष्ठा drbd_device *, जोड़ drbd_state,
					जोड़ drbd_state, क्रमागत chg_state_flags);

बाह्य क्रमागत drbd_state_rv _drbd_set_state(काष्ठा drbd_device *, जोड़ drbd_state,
					  क्रमागत chg_state_flags,
					  काष्ठा completion *करोne);
बाह्य व्योम prपूर्णांक_st_err(काष्ठा drbd_device *, जोड़ drbd_state,
			जोड़ drbd_state, क्रमागत drbd_state_rv);

क्रमागत drbd_state_rv
_conn_request_state(काष्ठा drbd_connection *connection, जोड़ drbd_state mask, जोड़ drbd_state val,
		    क्रमागत chg_state_flags flags);

क्रमागत drbd_state_rv
conn_request_state(काष्ठा drbd_connection *connection, जोड़ drbd_state mask, जोड़ drbd_state val,
		   क्रमागत chg_state_flags flags);

बाह्य व्योम drbd_resume_al(काष्ठा drbd_device *device);
बाह्य bool conn_all_vols_unconf(काष्ठा drbd_connection *connection);

/**
 * drbd_request_state() - Request a state change
 * @device:	DRBD device.
 * @mask:	mask of state bits to change.
 * @val:	value of new state bits.
 *
 * This is the most graceful way of requesting a state change. It is verbose
 * quite verbose in हाल the state change is not possible, and all those
 * state changes are globally serialized.
 */
अटल अंतरभूत पूर्णांक drbd_request_state(काष्ठा drbd_device *device,
				     जोड़ drbd_state mask,
				     जोड़ drbd_state val)
अणु
	वापस _drbd_request_state(device, mask, val, CS_VERBOSE + CS_ORDERED);
पूर्ण

/* क्रम use in adm_detach() (drbd_adm_detach(), drbd_adm_करोwn()) */
पूर्णांक drbd_request_detach_पूर्णांकerruptible(काष्ठा drbd_device *device);

क्रमागत drbd_role conn_highest_role(काष्ठा drbd_connection *connection);
क्रमागत drbd_role conn_highest_peer(काष्ठा drbd_connection *connection);
क्रमागत drbd_disk_state conn_highest_disk(काष्ठा drbd_connection *connection);
क्रमागत drbd_disk_state conn_lowest_disk(काष्ठा drbd_connection *connection);
क्रमागत drbd_disk_state conn_highest_pdsk(काष्ठा drbd_connection *connection);
क्रमागत drbd_conns conn_lowest_conn(काष्ठा drbd_connection *connection);

#पूर्ण_अगर
