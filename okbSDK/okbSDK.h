//
//  okbSDK.h
//  okbSDK
//
//  Created by 曾宪杰 on 2019/1/22.
//  Copyright © 2019 zengxianjie. All rights reserved.
//

#import <Foundation/Foundation.h>

//发送消息必须和后台商议，给每条发送的消息加上头部，字段如下，可以自定义扩展（为了解决tcp接收端数据粘包问题）
static NSString * const  kHeadMessageType = @"type";
static NSString * const  kHeadMessageSize = @"size";
//发送的消息类型,根据项目实际需求进行扩展
typedef enum : NSUInteger {
    ZTcpSendMessageText,     //文本
    ZTcpSendMessagePicture,  //图片
}ZTcpSendMessageType;
//回调闭包
typedef void(^ResponseBlock)(NSData * responseData,ZTcpSendMessageType type);
typedef void(^ResponseErrorBlock)(NSError *error);
//tcp连接成功和失败代理
@protocol ZTCPManagerDelegate <NSObject>
@required
-(void)tcpConnectedSuccess; //连接成功
-(void)tcpconnectedFailure; //连接失败
//收到tcp服务器主动发送的消息
-(void)recieveServerActiveReport:(NSData*)reportData MessageType:(ZTcpSendMessageType)type;
@end

@interface okbSDK : NSObject
@property (nonatomic,copy) ResponseErrorBlock errorBlock;
@property (nonatomic,weak) id<ZTCPManagerDelegate> delegate;//代理

+(instancetype)shareInstance;//单例

//连接tcp服务器
-(void)connectTcpServer:(int)port;

//tcp重连接
-(void)reConnectTcpServer:(int)port;

//断开tcp连接
-(void)disConnectTcpServer;

//tcp连接状态
-(BOOL)isTcpConnected;

//发送消息及后台是否回复当前消息,如果发送消息后台没有应答当前消息，请配置isAnser = NO;
-(void)sendData:(NSData*)data MessageType:(ZTcpSendMessageType)messageType  Response:(ResponseBlock)block IsServerAnswer:(BOOL)isAnser;

@end

@interface BlockModel :NSObject<NSCopying>
@property (nonatomic,strong) NSDate * timeStamp;
@property (nonatomic,copy) ResponseBlock block;

@end
