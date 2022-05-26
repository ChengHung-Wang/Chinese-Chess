config.resolve.alias.set("pinia$", "pinia/index.js",);
module.exports = {
    module: {
        rules: [
            // FIX: Can’t import the named export 'XXX' from non EcmaScript module
            {
                test: /\.cjs$/,
                include: /node_modules/,
                type: 'javascript/auto',
            },
            {
                test: /\.mjs$/,
                include: /node_modules/,
                type: 'javascript/auto',
            },
        ]
    },
    pluginOptions :{
        electronBuilder :{
            chainWebpackMainProcess: (config) => {
                config.module.rule('javascript/auto').test(/\.mjs$/)
            }
        }
    }
}
