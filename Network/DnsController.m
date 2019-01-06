//
//  DnsController.m
//  Network
//
//  Created by WENTAO XING on 2019/1/3.
//  Copyright © 2019 WENTAO XING. All rights reserved.
//

#import "DnsController.h"
#import "udp.h"
#import "dns.h"

@interface DnsController ()
@property(nonatomic, strong) UITextField * textField;
@property(nonatomic, strong) UIButton * search;
@property(nonatomic, strong) UILabel * ipLabel;
@property(nonatomic, strong) UILabel * dnsTitle;
@end

@implementation DnsController

-(UILabel *) dnsTitle
{
    if (!_dnsTitle) {
        _dnsTitle = [[UILabel alloc] init];
        _dnsTitle.translatesAutoresizingMaskIntoConstraints = NO;
        NSMutableAttributedString * dns = [[NSMutableAttributedString alloc] initWithString:@"DNS" attributes:@{
                                                                                                                NSFontAttributeName: [UIFont boldSystemFontOfSize:55]
                                                                                                                }];
        NSDictionary * color1 = @{
                                  NSForegroundColorAttributeName: [UIColor colorWithRed:0.27 green:0.53 blue:0.94 alpha:1]
                                  };
        NSDictionary * color2 = @{
                                  NSForegroundColorAttributeName: [UIColor colorWithRed:0.91 green:0.27 blue:0.24 alpha:1]
                                  };
        NSDictionary * color3 = @{
                                  NSForegroundColorAttributeName: [UIColor colorWithRed:0.98 green:0.73 blue:0.18 alpha:1]
                                  };
        [dns addAttributes:color1 range:NSMakeRange(0, 1)];
        [dns addAttributes:color2 range:NSMakeRange(1, 1)];
        [dns addAttributes:color3 range:NSMakeRange(2, 1)];
        _dnsTitle.attributedText = dns;
    }
    
    return _dnsTitle;
}

-(UILabel *) ipLabel
{
    if (!_ipLabel) {
        _ipLabel = [[UILabel alloc] init];
        _ipLabel.translatesAutoresizingMaskIntoConstraints = NO;
    }
    
    return _ipLabel;
}

-(UITextField *) textField
{
    if (!_textField) {
        _textField = [[UITextField alloc] init];
        _textField.translatesAutoresizingMaskIntoConstraints = NO;
        _textField.borderStyle = UITextBorderStyleRoundedRect;
        _textField.autocapitalizationType = UITextAutocapitalizationTypeNone;
        _textField.spellCheckingType = UITextSpellCheckingTypeNo;
        _textField.autocorrectionType = UITextAutocorrectionTypeNo;
        _textField.rightView = self.search;
        _textField.rightViewMode = UITextFieldViewModeAlways;
        _textField.clipsToBounds = YES;
    }
    
    return _textField;
}

-(UIButton *) search
{
    if (!_search) {
        _search = [UIButton buttonWithType: UIButtonTypeCustom];
        [_search setFrame: CGRectMake(0, 0, 50, 44)];
//        NSLog(@"font list: %@", [UIFont familyNames]);
        NSAttributedString * s = [[NSAttributedString alloc] initWithString:@"\U0000E6C8" attributes:@{
                                                                                                       NSFontAttributeName: [UIFont fontWithName:@"iconfont" size:30],
                                                                                                       NSForegroundColorAttributeName: [UIColor whiteColor],
                                                                                                       }];
        [_search setBackgroundColor:[UIColor blueColor]];
        [_search setAttributedTitle:s forState:(UIControlStateNormal)];
        [_search addTarget:self action:@selector(dnsSearch) forControlEvents:(UIControlEventTouchDown)];
        _search.layer.cornerRadius = 5;
    }
    return _search;
}

- (void)viewDidLoad {
    [super viewDidLoad];
    initUdp();
    self.view.backgroundColor = [UIColor whiteColor];
    [self.view addSubview:self.textField];
//    [self.view addSubview:self.search];
    [self.view addSubview:self.ipLabel];
    [self.view addSubview:self.dnsTitle];
    [self style];
}

-(void) style
{
    [self.dnsTitle.topAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.topAnchor constant: 120].active = YES;
    [self.dnsTitle.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor].active = YES;
    [self.textField.topAnchor constraintEqualToAnchor: self.dnsTitle.bottomAnchor constant: 18].active = YES;
    [self.textField.leadingAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.leadingAnchor constant:10].active = YES;
    
    [self.textField.trailingAnchor constraintEqualToAnchor:self.view.safeAreaLayoutGuide.trailingAnchor constant:-10].active = YES;
    
    [self.textField.heightAnchor constraintEqualToConstant:44].active = YES;
    /*
    [self.search.widthAnchor constraintEqualToConstant:150].active = YES;
    [self.search.heightAnchor constraintEqualToConstant:44].active = YES;
    [self.search.topAnchor constraintEqualToAnchor:self.textField.bottomAnchor constant:35].active = YES;
    [self.search.centerXAnchor constraintEqualToAnchor:self.view.centerXAnchor].active = YES;
    */
    [self.ipLabel.leadingAnchor constraintEqualToAnchor:self.textField.leadingAnchor].active = YES;
    
    [self.ipLabel.trailingAnchor constraintEqualToAnchor:self.textField.trailingAnchor].active = YES;
    
    [self.ipLabel.topAnchor constraintEqualToAnchor:self.textField.bottomAnchor constant:50].active = YES;
}

-(void) dnsSearch
{
    const char * domain = [self.textField.text UTF8String];
    char * ip = DnsSearch(domain);
    if (ip) {
        NSString * address = [NSString stringWithCString:ip encoding:(NSUTF8StringEncoding)];
        NSLog(@"address = %@", address);
        self.ipLabel.text = address;
    } else {
        self.ipLabel.text = @"Sorry, we can not resolve the ip address right now";
    }
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
