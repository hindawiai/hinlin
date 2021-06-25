<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Shared Memory Communications over RDMA (SMC-R) and RoCE
 *
 * Connection Data Control (CDC)
 *
 * Copyright IBM Corp. 2016
 *
 * Author(s):  Ursula Braun <ubraun@linux.vnet.ibm.com>
 */

#अगर_अघोषित SMC_CDC_H
#घोषणा SMC_CDC_H

#समावेश <linux/kernel.h> /* max_t */
#समावेश <linux/atomic.h>
#समावेश <linux/in.h>
#समावेश <linux/compiler.h>

#समावेश "smc.h"
#समावेश "smc_core.h"
#समावेश "smc_wr.h"

#घोषणा	SMC_CDC_MSG_TYPE		0xFE

/* in network byte order */
जोड़ smc_cdc_cursor अणु		/* SMC cursor */
	काष्ठा अणु
		__be16	reserved;
		__be16	wrap;
		__be32	count;
	पूर्ण;
#अगर_घोषित KERNEL_HAS_ATOMIC64
	atomic64_t	acurs;		/* क्रम atomic processing */
#अन्यथा
	u64		acurs;		/* क्रम atomic processing */
#पूर्ण_अगर
पूर्ण __aligned(8);

/* in network byte order */
काष्ठा smc_cdc_msg अणु
	काष्ठा smc_wr_rx_hdr		common; /* .type = 0xFE */
	u8				len;	/* 44 */
	__be16				seqno;
	__be32				token;
	जोड़ smc_cdc_cursor		prod;
	जोड़ smc_cdc_cursor		cons;	/* piggy backed "ack" */
	काष्ठा smc_cdc_producer_flags	prod_flags;
	काष्ठा smc_cdc_conn_state_flags	conn_state_flags;
	u8				reserved[18];
पूर्ण;

/* SMC-D cursor क्रमmat */
जोड़ smcd_cdc_cursor अणु
	काष्ठा अणु
		u16	wrap;
		u32	count;
		काष्ठा smc_cdc_producer_flags	prod_flags;
		काष्ठा smc_cdc_conn_state_flags	conn_state_flags;
	पूर्ण __packed;
#अगर_घोषित KERNEL_HAS_ATOMIC64
	atomic64_t		acurs;		/* क्रम atomic processing */
#अन्यथा
	u64			acurs;		/* क्रम atomic processing */
#पूर्ण_अगर
पूर्ण __aligned(8);

/* CDC message क्रम SMC-D */
काष्ठा smcd_cdc_msg अणु
	काष्ठा smc_wr_rx_hdr common;	/* Type = 0xFE */
	u8 res1[7];
	जोड़ smcd_cdc_cursor	prod;
	जोड़ smcd_cdc_cursor	cons;
	u8 res3[8];
पूर्ण __aligned(8);

अटल अंतरभूत bool smc_cdc_rxed_any_बंद(काष्ठा smc_connection *conn)
अणु
	वापस conn->local_rx_ctrl.conn_state_flags.peer_conn_पात ||
	       conn->local_rx_ctrl.conn_state_flags.peer_conn_बंदd;
पूर्ण

अटल अंतरभूत bool smc_cdc_rxed_any_बंद_or_sendकरोne(
	काष्ठा smc_connection *conn)
अणु
	वापस smc_cdc_rxed_any_बंद(conn) ||
	       conn->local_rx_ctrl.conn_state_flags.peer_करोne_writing;
पूर्ण

अटल अंतरभूत व्योम smc_curs_add(पूर्णांक size, जोड़ smc_host_cursor *curs,
				पूर्णांक value)
अणु
	curs->count += value;
	अगर (curs->count >= size) अणु
		curs->wrap++;
		curs->count -= size;
	पूर्ण
पूर्ण

/* Copy cursor src पूर्णांकo tgt */
अटल अंतरभूत व्योम smc_curs_copy(जोड़ smc_host_cursor *tgt,
				 जोड़ smc_host_cursor *src,
				 काष्ठा smc_connection *conn)
अणु
#अगर_अघोषित KERNEL_HAS_ATOMIC64
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&conn->acurs_lock, flags);
	tgt->acurs = src->acurs;
	spin_unlock_irqrestore(&conn->acurs_lock, flags);
#अन्यथा
	atomic64_set(&tgt->acurs, atomic64_पढ़ो(&src->acurs));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम smc_curs_copy_net(जोड़ smc_cdc_cursor *tgt,
				     जोड़ smc_cdc_cursor *src,
				     काष्ठा smc_connection *conn)
अणु
#अगर_अघोषित KERNEL_HAS_ATOMIC64
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&conn->acurs_lock, flags);
	tgt->acurs = src->acurs;
	spin_unlock_irqrestore(&conn->acurs_lock, flags);
#अन्यथा
	atomic64_set(&tgt->acurs, atomic64_पढ़ो(&src->acurs));
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम smcd_curs_copy(जोड़ smcd_cdc_cursor *tgt,
				  जोड़ smcd_cdc_cursor *src,
				  काष्ठा smc_connection *conn)
अणु
#अगर_अघोषित KERNEL_HAS_ATOMIC64
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&conn->acurs_lock, flags);
	tgt->acurs = src->acurs;
	spin_unlock_irqrestore(&conn->acurs_lock, flags);
#अन्यथा
	atomic64_set(&tgt->acurs, atomic64_पढ़ो(&src->acurs));
#पूर्ण_अगर
पूर्ण

/* calculate cursor dअगरference between old and new, where old <= new and
 * dअगरference cannot exceed size
 */
अटल अंतरभूत पूर्णांक smc_curs_dअगरf(अचिन्हित पूर्णांक size,
				जोड़ smc_host_cursor *old,
				जोड़ smc_host_cursor *new)
अणु
	अगर (old->wrap != new->wrap)
		वापस max_t(पूर्णांक, 0,
			     ((size - old->count) + new->count));

	वापस max_t(पूर्णांक, 0, (new->count - old->count));
पूर्ण

/* calculate cursor dअगरference between old and new - वापसs negative
 * value in हाल old > new
 */
अटल अंतरभूत पूर्णांक smc_curs_comp(अचिन्हित पूर्णांक size,
				जोड़ smc_host_cursor *old,
				जोड़ smc_host_cursor *new)
अणु
	अगर (old->wrap > new->wrap ||
	    (old->wrap == new->wrap && old->count > new->count))
		वापस -smc_curs_dअगरf(size, new, old);
	वापस smc_curs_dअगरf(size, old, new);
पूर्ण

/* calculate cursor dअगरference between old and new, where old <= new and
 * dअगरference may exceed size
 */
अटल अंतरभूत पूर्णांक smc_curs_dअगरf_large(अचिन्हित पूर्णांक size,
				      जोड़ smc_host_cursor *old,
				      जोड़ smc_host_cursor *new)
अणु
	अगर (old->wrap < new->wrap)
		वापस min_t(पूर्णांक,
			     (size - old->count) + new->count +
			     (new->wrap - old->wrap - 1) * size,
			     size);

	अगर (old->wrap > new->wrap) /* wrap has चयनed from 0xffff to 0x0000 */
		वापस min_t(पूर्णांक,
			     (size - old->count) + new->count +
			     (new->wrap + 0xffff - old->wrap) * size,
			     size);

	वापस max_t(पूर्णांक, 0, (new->count - old->count));
पूर्ण

अटल अंतरभूत व्योम smc_host_cursor_to_cdc(जोड़ smc_cdc_cursor *peer,
					  जोड़ smc_host_cursor *local,
					  जोड़ smc_host_cursor *save,
					  काष्ठा smc_connection *conn)
अणु
	smc_curs_copy(save, local, conn);
	peer->count = htonl(save->count);
	peer->wrap = htons(save->wrap);
	/* peer->reserved = htons(0); must be ensured by caller */
पूर्ण

अटल अंतरभूत व्योम smc_host_msg_to_cdc(काष्ठा smc_cdc_msg *peer,
				       काष्ठा smc_connection *conn,
				       जोड़ smc_host_cursor *save)
अणु
	काष्ठा smc_host_cdc_msg *local = &conn->local_tx_ctrl;

	peer->common.type = local->common.type;
	peer->len = local->len;
	peer->seqno = htons(local->seqno);
	peer->token = htonl(local->token);
	smc_host_cursor_to_cdc(&peer->prod, &local->prod, save, conn);
	smc_host_cursor_to_cdc(&peer->cons, &local->cons, save, conn);
	peer->prod_flags = local->prod_flags;
	peer->conn_state_flags = local->conn_state_flags;
पूर्ण

अटल अंतरभूत व्योम smc_cdc_cursor_to_host(जोड़ smc_host_cursor *local,
					  जोड़ smc_cdc_cursor *peer,
					  काष्ठा smc_connection *conn)
अणु
	जोड़ smc_host_cursor temp, old;
	जोड़ smc_cdc_cursor net;

	smc_curs_copy(&old, local, conn);
	smc_curs_copy_net(&net, peer, conn);
	temp.count = ntohl(net.count);
	temp.wrap = ntohs(net.wrap);
	अगर ((old.wrap > temp.wrap) && temp.wrap)
		वापस;
	अगर ((old.wrap == temp.wrap) &&
	    (old.count > temp.count))
		वापस;
	smc_curs_copy(local, &temp, conn);
पूर्ण

अटल अंतरभूत व्योम smcr_cdc_msg_to_host(काष्ठा smc_host_cdc_msg *local,
					काष्ठा smc_cdc_msg *peer,
					काष्ठा smc_connection *conn)
अणु
	local->common.type = peer->common.type;
	local->len = peer->len;
	local->seqno = ntohs(peer->seqno);
	local->token = ntohl(peer->token);
	smc_cdc_cursor_to_host(&local->prod, &peer->prod, conn);
	smc_cdc_cursor_to_host(&local->cons, &peer->cons, conn);
	local->prod_flags = peer->prod_flags;
	local->conn_state_flags = peer->conn_state_flags;
पूर्ण

अटल अंतरभूत व्योम smcd_cdc_msg_to_host(काष्ठा smc_host_cdc_msg *local,
					काष्ठा smcd_cdc_msg *peer,
					काष्ठा smc_connection *conn)
अणु
	जोड़ smc_host_cursor temp;

	temp.wrap = peer->prod.wrap;
	temp.count = peer->prod.count;
	smc_curs_copy(&local->prod, &temp, conn);

	temp.wrap = peer->cons.wrap;
	temp.count = peer->cons.count;
	smc_curs_copy(&local->cons, &temp, conn);
	local->prod_flags = peer->cons.prod_flags;
	local->conn_state_flags = peer->cons.conn_state_flags;
पूर्ण

अटल अंतरभूत व्योम smc_cdc_msg_to_host(काष्ठा smc_host_cdc_msg *local,
				       काष्ठा smc_cdc_msg *peer,
				       काष्ठा smc_connection *conn)
अणु
	अगर (conn->lgr->is_smcd)
		smcd_cdc_msg_to_host(local, (काष्ठा smcd_cdc_msg *)peer, conn);
	अन्यथा
		smcr_cdc_msg_to_host(local, peer, conn);
पूर्ण

काष्ठा smc_cdc_tx_pend अणु
	काष्ठा smc_connection	*conn;		/* socket connection */
	जोड़ smc_host_cursor	cursor;		/* tx sndbuf cursor sent */
	जोड़ smc_host_cursor	p_cursor;	/* rx RMBE cursor produced */
	u16			ctrl_seq;	/* conn. tx sequence # */
पूर्ण;

पूर्णांक smc_cdc_get_मुक्त_slot(काष्ठा smc_connection *conn,
			  काष्ठा smc_link *link,
			  काष्ठा smc_wr_buf **wr_buf,
			  काष्ठा smc_rdma_wr **wr_rdma_buf,
			  काष्ठा smc_cdc_tx_pend **pend);
व्योम smc_cdc_tx_dismiss_slots(काष्ठा smc_connection *conn);
पूर्णांक smc_cdc_msg_send(काष्ठा smc_connection *conn, काष्ठा smc_wr_buf *wr_buf,
		     काष्ठा smc_cdc_tx_pend *pend);
पूर्णांक smc_cdc_get_slot_and_msg_send(काष्ठा smc_connection *conn);
पूर्णांक smcd_cdc_msg_send(काष्ठा smc_connection *conn);
पूर्णांक smcr_cdc_msg_send_validation(काष्ठा smc_connection *conn,
				 काष्ठा smc_cdc_tx_pend *pend,
				 काष्ठा smc_wr_buf *wr_buf);
पूर्णांक smc_cdc_init(व्योम) __init;
व्योम smcd_cdc_rx_init(काष्ठा smc_connection *conn);

#पूर्ण_अगर /* SMC_CDC_H */
