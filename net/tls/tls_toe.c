<शैली गुरु>
/*
 * Copyright (c) 2016-2017, Mellanox Technologies. All rights reserved.
 * Copyright (c) 2016-2017, Dave Watson <davejwatson@fb.com>. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/list.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/spinlock.h>
#समावेश <net/inet_connection_sock.h>
#समावेश <net/tls.h>
#समावेश <net/tls_toe.h>

अटल LIST_HEAD(device_list);
अटल DEFINE_SPINLOCK(device_spinlock);

अटल व्योम tls_toe_sk_deकाष्ठा(काष्ठा sock *sk)
अणु
	काष्ठा inet_connection_sock *icsk = inet_csk(sk);
	काष्ठा tls_context *ctx = tls_get_ctx(sk);

	ctx->sk_deकाष्ठा(sk);
	/* Free ctx */
	rcu_assign_poपूर्णांकer(icsk->icsk_ulp_data, शून्य);
	tls_ctx_मुक्त(sk, ctx);
पूर्ण

पूर्णांक tls_toe_bypass(काष्ठा sock *sk)
अणु
	काष्ठा tls_toe_device *dev;
	काष्ठा tls_context *ctx;
	पूर्णांक rc = 0;

	spin_lock_bh(&device_spinlock);
	list_क्रम_each_entry(dev, &device_list, dev_list) अणु
		अगर (dev->feature && dev->feature(dev)) अणु
			ctx = tls_ctx_create(sk);
			अगर (!ctx)
				जाओ out;

			ctx->sk_deकाष्ठा = sk->sk_deकाष्ठा;
			sk->sk_deकाष्ठा = tls_toe_sk_deकाष्ठा;
			ctx->rx_conf = TLS_HW_RECORD;
			ctx->tx_conf = TLS_HW_RECORD;
			update_sk_prot(sk, ctx);
			rc = 1;
			अवरोध;
		पूर्ण
	पूर्ण
out:
	spin_unlock_bh(&device_spinlock);
	वापस rc;
पूर्ण

व्योम tls_toe_unhash(काष्ठा sock *sk)
अणु
	काष्ठा tls_context *ctx = tls_get_ctx(sk);
	काष्ठा tls_toe_device *dev;

	spin_lock_bh(&device_spinlock);
	list_क्रम_each_entry(dev, &device_list, dev_list) अणु
		अगर (dev->unhash) अणु
			kref_get(&dev->kref);
			spin_unlock_bh(&device_spinlock);
			dev->unhash(dev, sk);
			kref_put(&dev->kref, dev->release);
			spin_lock_bh(&device_spinlock);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&device_spinlock);
	ctx->sk_proto->unhash(sk);
पूर्ण

पूर्णांक tls_toe_hash(काष्ठा sock *sk)
अणु
	काष्ठा tls_context *ctx = tls_get_ctx(sk);
	काष्ठा tls_toe_device *dev;
	पूर्णांक err;

	err = ctx->sk_proto->hash(sk);
	spin_lock_bh(&device_spinlock);
	list_क्रम_each_entry(dev, &device_list, dev_list) अणु
		अगर (dev->hash) अणु
			kref_get(&dev->kref);
			spin_unlock_bh(&device_spinlock);
			err |= dev->hash(dev, sk);
			kref_put(&dev->kref, dev->release);
			spin_lock_bh(&device_spinlock);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&device_spinlock);

	अगर (err)
		tls_toe_unhash(sk);
	वापस err;
पूर्ण

व्योम tls_toe_रेजिस्टर_device(काष्ठा tls_toe_device *device)
अणु
	spin_lock_bh(&device_spinlock);
	list_add_tail(&device->dev_list, &device_list);
	spin_unlock_bh(&device_spinlock);
पूर्ण
EXPORT_SYMBOL(tls_toe_रेजिस्टर_device);

व्योम tls_toe_unरेजिस्टर_device(काष्ठा tls_toe_device *device)
अणु
	spin_lock_bh(&device_spinlock);
	list_del(&device->dev_list);
	spin_unlock_bh(&device_spinlock);
पूर्ण
EXPORT_SYMBOL(tls_toe_unरेजिस्टर_device);
