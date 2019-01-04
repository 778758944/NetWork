//
//  DnsController.m
//  Network
//
//  Created by WENTAO XING on 2019/1/3.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#import "DnsController.h"
#import "udp.h"

@interface DnsController ()
@property(nonatomic, strong) UITextField * textField;
@property(nonatomic, strong) UIButton * search;
@end

@implementation DnsController

-(UITextField *) textField
{
    if (!_textField) {
        _textField = [[UITextField alloc] init];
        _textField.translatesAutoresizingMaskIntoConstraints = NO;
        _textField.borderStyle = UITextBorderStyleRoundedRect;
    }
    
    return _textField;
}

-(UIButton *) search
{
    if (!_search) {
        _search = [UIButton buttonWithType: UIButtonTypeCustom];
        _search.translatesAutoresizingMaskIntoConstraints = NO;
        [_search setTitle:@"Search" forState:(UIControlStateNormal)];
        [_search setBackgroundColor:[UIColor blueColor]];
        [_search addTarget:self action:@selector(dnsSearch) forControlEvents:(UIControlEventTouchDown)];
        _search.layer.cornerRadius = 5;
    }
    return _search;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    initUdp();
    self.view.backgroundColor = [UIColor redColor];
    [self.view addSubview:self.textField];
    [self.view addSubview:self.search];
    [self style];
}

-(void) style
{
    [self.textField.topAnchor constraintEqualToAnchor: self.view.safeAreaLayoutGuide.topAnchor constant:80].active = YES;
    [self.textField.leadingAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.leadingAnchor constant:10].active = YES;
    
    [self.textField.trailingAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.trailingAnchor constant:-10].active = YES;
    
    [self.textField.heightAnchor constraintEqualToConstant:44].active = YES;
    
    [self.search.widthAnchor constraintEqualToConstant:150].active = YES;
    [self.search.heightAnchor constraintEqualToConstant:44].active = YES;
    [self.search.topAnchor constraintEqualToAnchor:self.textField.bottomAnchor constant:35].active = YES;
    [self.search.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor].active = YES;
}

-(void) dnsSearch
{
    NSLog(@"Dns search: %@", self.textField.text);
    const char * domain = [self.textField.text UTF8String];
    printf("domain = %s\n", domain);
    sendUdpMsg(domain, strlen(domain), "localhost", "3000");
    char * recvdata = NULL;
    socklen_t addrlen;
    ssize_t t = recvUdpMsg(&recvdata, NULL, &addrlen);
    printf("recv data: %s, %lu\n", recvdata, t);
}



/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
